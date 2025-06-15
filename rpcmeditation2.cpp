// rpcmeditation.cpp — ศูนย์กลางแห่งการขุดด้วยสมาธิ (Proof of Meditation)

#include <univalue.h> #include "rpc/server.h" #include "validation.h" #include "consensus/validation.h" #include "wallet/wallet.h" #include "miner.h" #include "shutdown.h" #include "sync.h" #include "txmempool.h" #include "util/system.h" #include "script/standard.h" #include "wallet/coincontrol.h" #include "wallet/fees.h"

// ฟังก์ชัน RPC: claimmeditationreward "mantra" UniValue claimmeditationreward(const JSONRPCRequest& request) { if (request.fHelp || request.params.size() < 1) { throw std::runtime_error( "claimmeditationreward "mantra"\n" "รับรางวัลจากการภาวนาด้วยบทบริกรรม (mantra)\n" "เช่น: claimmeditationreward "พุทโธ"" ); }

std::string mantra = request.params[0].get_str();

if (mantra.length() < 2) {
    throw JSONRPCError(RPC_INVALID_PARAMETER, "mantra สั้นเกินไป");
}

CAmount meditationReward = 0.0001 * COIN;

CWallet* const pwallet = GetWalletForJSONRPCRequest(request);
if (!pwallet) {
    throw JSONRPCError(RPC_WALLET_NOT_FOUND, "ไม่พบ wallet");
}

EnsureWalletIsUnlocked(pwallet);

CRecipient recipient = {GetScriptForDestination(pwallet->GetPrimaryDestination()), meditationReward, false};

CTransactionRef tx;
CReserveKey reservekey(pwallet);
CWalletTx wtx;
std::string strError;

if (!pwallet->CreateTransaction({recipient}, wtx, reservekey, strError)) {
    throw JSONRPCError(RPC_WALLET_ERROR, strError);
}

if (!pwallet->CommitTransaction(wtx, {}, {})) {
    throw JSONRPCError(RPC_WALLET_ERROR, "ไม่สามารถ commit ธุรกรรมได้");
}

UniValue result(UniValue::VOBJ);
result.pushKV("mantra", mantra);
result.pushKV("txid", wtx.GetHash().GetHex());
result.pushKV("reward", FormatMoney(meditationReward));
return result;

}

// เรียกใช้ background meditation miner void StartMeditationMining(CWallet* pwallet) { LogPrintf("[BuddhoChain] เริ่มต้นขุดด้วยพลังสมาธิ...\n");

if (!pwallet) return;

std::string mantra = "พุทโธ";
CAmount meditationReward = 0.00005 * COIN;

CRecipient recipient = {GetScriptForDestination(pwallet->GetPrimaryDestination()), meditationReward, false};

CTransactionRef tx;
CReserveKey reservekey(pwallet);
CWalletTx wtx;
std::string strError;

if (pwallet->CreateTransaction({recipient}, wtx, reservekey, strError)) {
    if (pwallet->CommitTransaction(wtx, {}, {})) {
        LogPrintf("[BuddhoChain] meditation tx committed: %s\n", wtx.GetHash().ToString());
    }
}

}

// Register RPC static const CRPCCommand commands[] = { { "meditation", "claimmeditationreward", &claimmeditationreward, {"mantra"} }, };

void RegisterMeditationRPCCommands(CRPCTable &t) { for (unsigned int vcidx = 0; vcidx < sizeof(commands)/sizeof(commands[0]); ++vcidx) { t.appendCommand(commands[vcidx].name, &commands[vcidx]); } }

// เรียกจาก init.cpp เพื่อเริ่มระบบขุดสมาธิ void StartBuddhoChain(CWallet* pwallet) { LogPrintf("[BuddhoChain] เริ่มระบบพุทธโธเชน\n"); RegisterMeditationRPCCommands(*g_rpc_table); StartMeditationMining(pwallet); }

// สิ้นสุดแห่งไฟล์เดียวครบทุกธรรม

