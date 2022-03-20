#pragma once

struct [[eosio::table, eosio::contract(CONTRACT_NAME)]] user_s
{
    eosio::name wallet;
    vector<asset> balances = {};
    uint64_t total_vote;
    time_point_sec last_claim;
    uint64_t primary_key() const { return wallet.value; }
};

typedef eosio::multi_index<"users"_n, user_s> user_t;