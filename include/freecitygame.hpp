#pragma once 
#define CONTRACT_NAME "freecitygame"
// #define TESTNET
#define MAINNET


#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/symbol.hpp>
#include <eosio/singleton.hpp>
// #include <eosio/transaction.hpp>
// #include <eosio/crypto.hpp>
// #include <vector>
// #include <string>
// #include <cmath>
using namespace eosio;
using namespace std;

// #include <atomichub/atomicdata.hpp>
// using namespace atomicdata;
#include <atomichub/atomicassets-interface.hpp>

#include <const_val.hpp>
#include <error_message.hpp>
#include <utils.hpp>

#include <freecitytoken-token-interface.hpp>

using namespace utils;

#include <tables/blendconfig.hpp>
#include <tables/configs.hpp>
#include <tables/users.hpp>
#include <tables/userstaking.hpp>

using namespace atomicassets;
using namespace freecitytoken;

CONTRACT freecitygame : public contract
{
public:
   using contract::contract;

   ACTION setblendcfg(int32_t template_id, string name, vector<int32_t> require_template_ids);
   ACTION rmblendcfg(int32_t template_id);
   [[eosio::on_notify("atomicassets::transfer")]] 
   void receive_nfttransfer(name from, name to, vector<uint64_t> asset_ids, string memo);

   ACTION setconfig(asset vote_to_token_ratio, uint32_t stake_duration, vector<int32_t> allow_stake_template_ids);
   ACTION clearconfig();

   ACTION claimstake(name wallet);
   ACTION rmuser(name wallet);
   ACTION rmnftstake(uint64_t asset_id);
   ACTION wthtoken(name wallet, asset quantity);
   ACTION unstknft(name wallet);
   ACTION adduseraff(name wallet, name affiliate_wallet);
   
private:
   
   blendconfig_t blendconfigs = blendconfig_t(_self, _self.value);
   configs_t       configs        = configs_t(_self, _self.value);
   userstaking_t userstakings = userstaking_t(_self, _self.value);
   user_t users = user_t(_self, _self.value);

   // void send_token(name from, name to, asset quantity, string memo);
   void mint_new_nft(name asset_owner, int32_t template_id, uint32_t quantity) {
      check(quantity > 0, ERR_QUANTITY_MUST_GREATER_THAN_ZERO);
      auto templates     = get_templates(COLLECTION_NAME);
      auto template_info = templates.require_find((uint64_t)template_id, ERR_TEMPLATE_NOT_FOUND);
      while (quantity > 0) {
         action(
               permission_level{_self, name("active")}, ATOMICASSETS_ACCOUNT, name("mintasset"),
               make_tuple(
                  _self, COLLECTION_NAME, template_info->schema_name, template_id, asset_owner, std::map<std::string, ATOMIC_ATTRIBUTE>{},
                  std::map<std::string, ATOMIC_ATTRIBUTE>{}, vector<asset>{}))
               .send();
         quantity--;
      }
   }

   void blend_nft(name wallet, int32_t template_id, vector<uint64_t> asset_ids){
      auto blend_cfg = blendconfigs.require_find((uint64_t)template_id, ERR_BLEND_CONFIG_NOT_FOUND);
      auto      assets         = get_assets(_self);
      vector<int32_t> material_template_ids = {};
      for(const uint64_t& asset_id: asset_ids){
         auto asset = assets.require_find(asset_id, ERR_ASSET_ID_NOT_FOUND(asset_id));
         material_template_ids.push_back(asset->template_id);
         action({_self, name("active")}, ATOMICASSETS_ACCOUNT, name("burnasset"), make_tuple(_self, asset_id)).send();
      }

      sort(material_template_ids.begin(), material_template_ids.end());
      check(blend_cfg->require_template_ids == material_template_ids, ERR_INSUFFICIENT_MATERIAL);

      mint_new_nft(wallet, template_id, 1);
   }

   /**
   * Add specific amount of token to user balance
   */
   void add_token(name wallet, asset asset_amount) {
       auto user_itr = users.find(wallet.value);
       if(user_itr == users.end()){
          users.emplace(_self, [&](auto&_item) {
             _item.wallet = wallet;
            _item.balances = { asset_amount };
         });
       }
       else{
          auto user_balances = user_itr->balances;
         auto balance_itr = std::find_if(user_balances.begin(), user_balances.end(), 
                  [&](asset& i){ return i.symbol == asset_amount.symbol; });
         if(balance_itr != user_balances.end()){
               user_balances[balance_itr - user_balances.begin()] += asset_amount;
         }
         else{
               user_balances.push_back(asset_amount);
         }
         
         users.modify(user_itr, _self, [&](auto&_item) { 
               _item.balances = user_balances;
         });
       }
   }

   /**
   * Remove specific amount of token from player balance
   */
    void remove_token(name wallet, asset asset_amount) {

        auto user_itr      = users.require_find(wallet.value, ERR_INSUFFICIENT_TOKEN_BALANCE);
        auto user_balances = user_itr->balances;
        auto balance_itr = std::find_if(
                user_balances.begin(), user_balances.end(), [&](asset& i) { return i.symbol == asset_amount.symbol && i >= asset_amount; });
            check(balance_itr != user_balances.end(), ERR_INSUFFICIENT_TOKEN_BALANCE);
            user_balances[balance_itr - user_balances.begin()] -= asset_amount;

        users.modify(user_itr, _self, [&](auto& _item) { _item.balances = user_balances; });
    }

   /**
   * stake array of asset ids to users table deposit_nfts field
   */
   void stake_nfts(name wallet, vector<uint64_t> asset_ids) {
      auto      assets         = get_assets(_self);
      auto user_itr = users.find(wallet.value);
      if(user_itr == users.end()){
          user_itr = users.emplace(_self, [&](auto&_item) {
             _item.wallet = wallet;
         });
       }
       
      auto current_configs = configs.get();
      uint64_t total_vote = 0;
      for(const uint64_t& asset_id: asset_ids){
         auto asset_info = assets.require_find(asset_id, ERR_ASSET_ID_NOT_FOUND(asset_id));
         schemas_t   collection_schemas   = get_schemas(COLLECTION_NAME);
         auto        schema_itr           = collection_schemas.find(asset_info->schema_name.value);
         templates_t collection_templates = get_templates(COLLECTION_NAME);
         auto template_itr = collection_templates.find(asset_info->template_id);
         check(is_exists(current_configs.allow_stake_template_ids, asset_info->template_id), ERR_ASSET_ID_IS_INVALID(asset_id));
         auto immutable_data = deserialize(template_itr->immutable_serialized_data, schema_itr->format);

         uint64_t vote_weight = get_nft_attribute_value<uint64_t>(immutable_data, "vote");
         check(vote_weight > 0, ERR_NO_VOTE_VALUE);

         userstakings.emplace(_self, [&](auto& _item) {
            _item.asset_id   = asset_id;
            _item.wallet = wallet;
            _item.vote = vote_weight;
            
         });
         total_vote += vote_weight;
      }

      users.modify(user_itr, _self, [&](auto& _item) {
         _item.total_vote += total_vote;
         _item.next_reward = _item.total_vote * current_configs.vote_to_token_ratio;
         _item.last_vote_stake = current_time_point();
      });
   }
};