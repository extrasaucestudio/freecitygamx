ACTION freecitygame::claimstake(name wallet) {
    require_auth(wallet);
    auto user_itr = users.require_find(wallet.value, ERR_NEED_STAKE_BEFORE_CLAIM);
    check(user_itr->total_vote > 0, ERR_NEED_STAKE_BEFORE_CLAIM);
    auto current_configs = configs.get();
    check(user_itr->last_claim + current_configs.stake_duration <= current_time_point(), ERR_CANT_CLAIM_YET);
    
    // add_token(wallet, current_configs.vote_to_token_ratio * user_itr->total_vote);
    users.modify(user_itr, _self, [&](auto& _item){
        _item.last_claim = current_time_point();
    });


    auto reward_asset = current_configs.vote_to_token_ratio * user_itr->total_vote;
    auto balances = freecitytoken::get_balance(_self);
    auto balances_itr = balances.find(TOKEN_SYMBOL.code().raw());
    if(balances_itr != balances.end() && balances_itr->balance.amount > 0) {
        auto transfer_amount = balances_itr->balance >= reward_asset ? reward_asset : balances_itr->balance;
        reward_asset -= transfer_amount;
        action(
            {_self, name("active")}, TOKEN_ACCOUNT, name("transfer"),
            make_tuple(_self, wallet, transfer_amount, CLAIM_VOTE_TRANSFER))
            .send();
    }

    if (reward_asset.amount > 0){
        action(
                {_self, name("active")}, TOKEN_ACCOUNT, name("issue"),
                make_tuple(wallet, reward_asset, CLAIM_VOTE_ISSUE_MEMO))
                .send();
    }
    

    
    
    

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
    auto staking_itr = userstakings.require_find(asset_id, ERR_NEED_STAKE_BEFORE_UNSTAKE);
    action(
            {_self, name("active")}, ATOMICASSETS_ACCOUNT, name("transfer"),
            make_tuple(_self, staking_itr->wallet, vector<uint64_t> { asset_id }, WITHDRAW_NFT_MEMO))
            .send();
    userstakings.erase(staking_itr);
}

ACTION freecitygame::unstknft(name wallet) {
    require_auth(wallet);
    auto user_itr = users.require_find(wallet.value, ERR_NEED_STAKE_BEFORE_UNSTAKE);
    check(user_itr->total_vote > 0, ERR_NEED_STAKE_BEFORE_UNSTAKE);
    auto current_configs = configs.get();
    check(user_itr->last_claim + current_configs.stake_duration <= current_time_point(), ERR_CANT_UNSTAKE_YET);
    auto user_staking_idx = userstakings.get_index<name("bywallet")>();
    auto itr = user_staking_idx.lower_bound(wallet.value);
    vector<uint64_t> asset_ids = {};
    while(itr != user_staking_idx.end() && itr->wallet == wallet) {
        asset_ids.push_back(itr->asset_id);
        itr = user_staking_idx.erase(itr);
    }

    users.modify(user_itr, _self, [&](auto& _item) {
        _item.last_vote_stake = time_point_sec::min();
        _item.last_claim = time_point_sec::min();
        _item.next_reward = asset(0, TOKEN_SYMBOL);
        _item.total_vote = 0;
    });
    
    check(asset_ids.size() > 0, ERR_NEED_STAKE_BEFORE_UNSTAKE);
    action(
            {_self, name("active")}, ATOMICASSETS_ACCOUNT, name("transfer"),
            make_tuple(_self, wallet, asset_ids, WITHDRAW_NFT_MEMO))
            .send();
}