const string STAKE_MEMO = "stake";
const string WITHDRAW_NFT_MEMO = "claim stake - return nft";
const string WITHDRAW_TOKEN_MEMO = "withdraw";
const string CLAIM_VOTE_ISSUE_MEMO = "Claim RMX";
const string CLAIM_VOTE_TRANSFER = "Claim RMX - transfer";


#ifdef TESTNET
static constexpr name COLLECTION_NAME = name("mytestcol121");
static constexpr symbol TOKEN_SYMBOL = symbol("RMW", 4);
static constexpr name TOKEN_ACCOUNT = name("freecitytkn1");
#endif

#ifdef MAINNET
static constexpr name COLLECTION_NAME = name("freecitygame");
static constexpr symbol TOKEN_SYMBOL = symbol("RMX", 8);
static constexpr name TOKEN_ACCOUNT = name("remixgamingx");
#endif