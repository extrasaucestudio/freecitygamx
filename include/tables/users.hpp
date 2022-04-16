#pragma once

struct [[eosio::table, eosio::contract(CONTRACT_NAME)]] user_s
{
    eosio::name wallet;
    vector<asset> balances = {};
    uint64_t total_vote;
    time_point_sec last_vote_stake;
    time_point_sec last_claim;
    asset next_reward;
    name affiliate_wallet;
    uint64_t primary_key() const { return wallet.value; }
    uint64_t by_total_vote() const { return total_vote; }
};

typedef eosio::multi_index<"users"_n, user_s,
eosio::indexed_by<name("bytotalvote"), eosio::const_mem_fun<user_s, uint64_t, &user_s::by_total_vote>>
> user_t;