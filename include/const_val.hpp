// static const uint32_t token_add_amount = 1;
// static constexpr symbol FIGHTANIUM_TOKEN_SYMBOL = symbol("FLF", 4);
// static constexpr symbol FIGHTKRED_TOKEN_SYMBOL = symbol("FLK", 4);
// static constexpr symbol FIGHTGRADE_TOKEN_SYMBOL = symbol("FLG", 4);
// static constexpr symbol COMBAT_TOKEN_SYMBOL = symbol("FLCB", 4);

// static constexpr name TOKEN_CONTRACT_NAME = name("testfighttkn");
// static constexpr name COLLECTION_NAME = name("testfight123");
// const string WITHDRAW_MESSAGE = "Withdraw from Fightland";
// const string BLEND_MEMO = "Blend";
const string STAKE_MEMO = "stake";
const string WITHDRAW_NFT_MEMO = "claim stake - return nft";


#ifdef TESTNET
static constexpr name COLLECTION_NAME = name("mytestcol121");
static constexpr symbol TOKEN_SYMBOL = symbol("RMW", 4);
#endif

#ifdef MAINNET
static constexpr name COLLECTION_NAME = name("freecitygame");
static constexpr symbol TOKEN_SYMBOL = symbol("RMX", 8);
#endif