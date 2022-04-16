#include <freecitygame.hpp>
#include "blend.cpp"
#include "on_notify.cpp"
#include "configuration.cpp"
#include "stake.cpp"

ACTION freecitygame::rmuser(name wallet) {
    require_auth(_self);
    auto user_itr = users.require_find(wallet.value, ERR_WALLET_NOT_FOUND);
    users.erase(user_itr);
}

ACTION freecitygame::wthtoken(name wallet, asset quantity) {
    require_auth(wallet);
    remove_token(wallet, quantity);

    action({_self, name("active")}, TOKEN_ACCOUNT, name("transfer"), make_tuple(_self, wallet, quantity, WITHDRAW_TOKEN_MEMO))
            .send();
}