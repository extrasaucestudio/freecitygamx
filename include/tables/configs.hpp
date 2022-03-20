#pragma once

struct [[eosio::table, eosio::contract(CONTRACT_NAME)]] configs_s
{
    asset vote_to_token_ratio;
    uint32_t stake_duration;
    vector<int32_t> allow_stake_template_ids;
};

typedef eosio::singleton<"configs"_n, configs_s> configs_t;
    // https://github.com/EOSIO/eosio.cdt/issues/280
typedef eosio::multi_index <"configs"_n, configs_s> configs_t_for_abi;