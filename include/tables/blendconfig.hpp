#pragma once

struct [[eosio::table, eosio::contract(CONTRACT_NAME)]] blendconfig_s
{
    int32_t template_id;
    std::string name;
    vector<int32_t> require_template_ids;
    uint64_t primary_key() const { return (uint64_t)template_id; }
};

typedef eosio::multi_index<"blendconfigs"_n, blendconfig_s> blendconfig_t;