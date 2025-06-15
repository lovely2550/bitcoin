// rpcmeditation.cpp — เส้นทางสู่การขุดเหรียญด้วยสมาธิ (Proof of Meditation)

#include <univalue.h> #include "rpc/server.h" #include "validation.h" #include "consensus/validation.h" #include "wallet/wallet.h"

UniValue claimmeditationreward(const JSONRPCRequest& request) { if (request.fHelp || request.params.size() < 1) { throw std::runtime_error( "claimmeditationreward "mantra"\n" "รับรางวัลจากการภาวนาด้วยบทบริกรรม (mantra)\n" "เช่น: claimmeditationreward "พุทโธ"" ); }

std::string mantra = request.params[0].get_str();

if (mantra.length() < 2) {
    throw JSONRPCError(RPC_INVALID_PARAMETER, "mantra สั้นเกินไป");
}

// สมมุติว่ามีค่าคงที่ของรางวัลต่อ mantra (ท่านสามารถปรับให้ dynamic ตาม merit ได้)
CAmount meditationReward = 0.0001 * COIN;

// สมมุติว่ายังไม่มีระบบ merit เต็มรูปแบบ จึงให้รางวัลคงที่
CWallet* const pwallet = GetWalletForJSONRPCRequest(request);
if (!pwallet) {
    throw JSONRPCError(RPC_WALLET_NOT_FOUND, "ไม่พบ wallet");
}

EnsureWalletIsUnlocked(pwallet);

// สร้างธุรกรรมส่ง reward เข้ากระเป๋าตัวเอง
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

static const CRPCCommand commands[] = { // category        name                    actor                    argNames { "meditation", "claimmeditationreward", &claimmeditationreward, {"mantra"} }, };

void RegisterMeditationRPCCommands(CRPCTable &t) { for (unsigned int vcidx = 0; vcidx < sizeof(commands)/sizeof(commands[0]); ++vcidx) { t.appendCommand(commands[vcidx].name, &commands[vcidx]); } }

