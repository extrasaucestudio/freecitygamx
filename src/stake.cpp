ACTION freecitygame::claimstake(name wallet) {
    require_auth(wallet);
    auto user_itr = users.require_find(wallet.value, ERR_WALLET_NOT_FOUND);
    check(user_itr->total_vote > 0, ERR_STAKING_NOT_FOUND);
    auto current_configs = configs.get();
    check(user_itr->last_claim + current_configs.stake_duration <= current_time_point(), ERR_CANT_CLAIM_YET);
    
    add_token(wallet, current_configs.vote_to_token_ratio * user_itr->total_vote);
    users.modify(user_itr, _self, [&](auto& _item){
        _item.last_claim = current_time_point();
    });
    // auto staking_itr = userstakings.require_find(asset_id, ERR_STAKING_NOT_FOUND);
    // check(staking_itr->claim_time <= current_time_point(), ERR_CANT_CLAIM_YET);
    // check(staking_itr->wallet == wallet, ERR_CANT_CLAIM_STAKING);
    // add_token(wallet, staking_itr->reward_token);

    // action(
    //         {_self, name("active")}, ATOMICASSETS_ACCOUNT, name("transfer"),
    //         make_tuple(_self, wallet, vector<uint64_t> { asset_id }, WITHDRAW_NFT_MEMO))
    //         .send();

    // userstakings.erase(staking_itr);
}

ACTION freecitygame::rmnftstake(uint64_t asset_id) {
    require_auth(_self);
    auto staking_itr = userstakings.require_find(asset_id, ERR_STAKING_NOT_FOUND);
    action(
            {_self, name("active")}, ATOMICASSETS_ACCOUNT, name("transfer"),
            make_tuple(_self, staking_itr->wallet, vector<uint64_t> { asset_id }, WITHDRAW_NFT_MEMO))
            .send();
    userstakings.erase(staking_itr);
}