ACTION freecitygame::setconfig(asset vote_to_token_ratio, uint32_t stake_duration, vector<int32_t> allow_stake_template_ids) {
    require_auth(_self);

    check(vote_to_token_ratio.symbol == TOKEN_SYMBOL, ERR_TOKEN_NOT_SUPPORTED);

    auto config_stored = configs.get_or_create(_self, configs_s{});
    config_stored.vote_to_token_ratio = vote_to_token_ratio;
    config_stored.stake_duration = stake_duration;
    config_stored.allow_stake_template_ids = allow_stake_template_ids;
   
   configs.set(config_stored, _self);
}

ACTION freecitygame::clearconfig() {
    require_auth(_self);
    if (configs.exists()) {
        configs.remove();
    }
}