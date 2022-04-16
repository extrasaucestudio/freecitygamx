static const char* ERR_INSUFFICIENT_TOKEN_BALANCE = "Insufficient token balance";
static const char* ERR_WALLET_NOT_FOUND = "Wallet not found";
static const char* ERR_REQUIRE_TEMPLATE_IDS = "Require template ids must greater than 1";
static const char* ERR_BLEND_CONFIG_NOT_FOUND = "Blend config not found";
static const char* ERR_QUANTITY_MUST_GREATER_THAN_ZERO = "Quantity must be greater than 0";
static const char* ERR_TEMPLATE_NOT_FOUND = "Template not found";
static const char* ERR_INSUFFICIENT_MATERIAL = "Insufficient material";
static const char* ERR_CANT_CLAIM_STAKING = "Cant claim staking";
static const char* ERR_STAKING_NOT_FOUND = "Staking nft not found";
static const char* ERR_CANT_STAKE_YET = "You can't stake nft now";
static const char* ERR_CANT_CLAIM_YET = "One claim per 24h please come back";
static const char* ERR_TOKEN_NOT_SUPPORTED = "This token is not supported";
static const char* ERR_NO_VOTE_VALUE = "Nft dont have vote value";
static const char* ERR_NEED_STAKE_BEFORE_CLAIM = "You need to stake NFT before claim play.remixworlds.com";
static const char* ERR_NEED_STAKE_BEFORE_UNSTAKE = "You need to stake NFT before unstake play.remixworlds.com";
static const char* ERR_CANT_UNSTAKE_YET = "You can't unstake NFT yet";

static const char* ERR_ASSET_ID_NOT_FOUND(uint64_t asset_id) {
    return ("Asset (ID: " + to_string(asset_id) + ") not found").c_str();
}

static const char* ERR_ASSET_ID_IS_STAKING(uint64_t asset_id) {
    return ("Asset (ID: " + to_string(asset_id) + ") is staking").c_str();
}

static const char* ERR_ASSET_ID_IS_INVALID(uint64_t asset_id) {
    return ("Asset (ID: " + to_string(asset_id) + ") is invalid").c_str();
}