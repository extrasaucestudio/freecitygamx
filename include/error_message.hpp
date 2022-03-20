// static const char* ERR_PLAYER_NOT_FOUND = "Player not found";
// static const char* ERR_INSUFFICIENT_TOKEN_BALANCE = "Insufficient token balance";
// static const char* ERR_ASSET_ID_MUST_BE_UNIQUE = "Asset id must be unique";
// static const char* ERR_EXCHANGE_CONFIG_NOT_FOUND = "Exchange config not found";
// static const char* ERR_WALLET_NOT_ALLOW_TO_CALL_ACTION = "Wallet not allow to call this action";
// static const char* ERR_WALLET_EXISTS = "Wallet already exists";
// static const char* ERR_NO_AUTH = "No auth";
static const char* ERR_WALLET_NOT_FOUND = "Wallet not found";
static const char* ERR_REQUIRE_TEMPLATE_IDS = "Require template ids must greater than 1";
static const char* ERR_BLEND_CONFIG_NOT_FOUND = "Blend config not found";
// static const char* ERR_EARLY_ACCESS_CONFIG_NOT_FOUND = "Early access config not found";
static const char* ERR_QUANTITY_MUST_GREATER_THAN_ZERO = "Quantity must be greater than 0";
static const char* ERR_TEMPLATE_NOT_FOUND = "Template not found";
static const char* ERR_INSUFFICIENT_MATERIAL = "Insufficient material";
static const char* ERR_CANT_CLAIM_STAKING = "Cant claim staking";
static const char* ERR_STAKING_NOT_FOUND = "Staking nft not found";
static const char* ERR_CANT_STAKE_YET = "You can't stake nft now";
static const char* ERR_CANT_CLAIM_YET = "Cant claim yet";
static const char* ERR_TOKEN_NOT_SUPPORTED = "This token is not supported";
static const char* ERR_NO_VOTE_VALUE = "Nft dont have vote value";
// static const char* ERR_RECRUITMENT_NOT_FOUND = "Recruitment not found";
// static const char* ERR_WAIT_PERIOD_IS_NOT_UP = "Wait period is not up or recruit is already claimed";
// static const char* ERR_RECRUITMENT_INPROGRESS = "Recruitment is in progress";
// static const char* ERR_TOKEN_NOT_SUPPORTED = "This token is not supported";

// static const char* ERR_USER_DOESNT_OWN_ASSET(uint64_t asset_id) {
//     return ("User doesn't own the provided assets (ID: " + to_string(asset_id) + ")").c_str();
// }

static const char* ERR_ASSET_ID_NOT_FOUND(uint64_t asset_id) {
    return ("Asset (ID: " + to_string(asset_id) + ") not found").c_str();
}

static const char* ERR_ASSET_ID_IS_STAKING(uint64_t asset_id) {
    return ("Asset (ID: " + to_string(asset_id) + ") is staking").c_str();
}

static const char* ERR_ASSET_ID_IS_INVALID(uint64_t asset_id) {
    return ("Asset (ID: " + to_string(asset_id) + ") is invalid").c_str();
}