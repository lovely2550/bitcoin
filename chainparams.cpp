// chainparams.cpp — ฉบับธรรมะใหม่ (พุทธโธเชน)

#include "chainparams.h" #include "consensus/merkle.h" #include "util.h" #include "utilstrencodings.h" #include <assert.h>

#include <boost/algorithm/string/classification.hpp> #include <boost/algorithm/string/split.hpp>

static CBlock CreateGenesisBlock( const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward) { CMutableTransaction txNew; txNew.nVersion = 1; txNew.vin.resize(1); txNew.vout.resize(1); txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp)); txNew.vout[0].nValue = genesisReward; txNew.vout[0].scriptPubKey = genesisOutputScript;

CBlock genesis;
genesis.nTime    = nTime;
genesis.nBits    = nBits;
genesis.nNonce   = nNonce;
genesis.nVersion = nVersion;
genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
genesis.hashPrevBlock.SetNull();
genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
return genesis;

}

/**

พารามิเตอร์ของเครือข่ายหลัก */ class CMainParams : public CChainParams { public: CMainParams() { strNetworkID = "main"; consensus.nSubsidyHalvingInterval = 210000; consensus.BIP34Height = 0; consensus.BIP34Hash = uint256(); consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // สองสัปดาห์ consensus.nPowTargetSpacing = 10 * 60; // 10 นาที consensus.fPowAllowMinDifficultyBlocks = false; consensus.fPowNoRetargeting = false; consensus.nRuleChangeActivationThreshold = 1916; // 95% ของ 2016 consensus.nMinerConfirmationWindow = 2016;

// block แรกแห่งพุทธโธเชน
 const char* pszTimestamp = "ธรรมะในใจคือสิ่งแท้จริง พุทธโธเชน 2025-06-15";
 CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
 genesis = CreateGenesisBlock(pszTimestamp, genesisOutputScript, 1718400000, 2083236893, 0x1d00ffff, 1, 50 * COIN);

 consensus.hashGenesisBlock = genesis.GetHash();
 assert(consensus.hashGenesisBlock == uint256S("0x000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"));
 assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));

 vSeeds.emplace_back("seed1.buddhochain.net");
 vSeeds.emplace_back("seed2.buddhochain.net");

 base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0);
 base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
 base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);

 fDefaultConsistencyChecks = false;
 fRequireStandard = true;
 fMineBlocksOnDemand = false;

} };


static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() { assert(globalChainParams); return *globalChainParams; }

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain) { if (chain == "main") return std::make_unique<CMainParams>(); throw std::runtime_error("Unknown chain " + chain); }

void SelectParams(const std::string& network) { globalChainParams = CreateChainParams(network); }

