// #pragma once

namespace freecitytoken {

    TABLE account_s {
         asset    balance;

         uint64_t primary_key()const { return balance.symbol.code().raw(); }
      };
    typedef eosio::multi_index<"accounts"_n, account_s> account_t;
    
    account_t get_balance(name wallet) {
        return account_t(TOKEN_ACCOUNT, wallet.value);
    }
}