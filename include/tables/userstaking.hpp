#pragma once

struct [[eosio::table, eosio::contract(CONTRACT_NAME)]] userstaking_s
{
    uint64_t asset_id;
    eosio::name wallet;
    uint64_t vote;
    // time_point_sec claim_time;
    // asset reward_token;
    uint64_t primary_key() const { return asset_id; }
    uint64_t by_wallet() const { return wallet.value; }
};

typedef eosio::multi_index<"userstaking"_n, userstaking_s,
    eosio::indexed_by<name("bywallet"), eosio::const_mem_fun<userstaking_s, uint64_t, &userstaking_s::by_wallet>>> userstaking_t;