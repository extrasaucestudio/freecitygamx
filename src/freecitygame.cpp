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