// validation.cpp – กำหนดให้ reward ทุก block ไปยังกระเป๋ากลาง

#include <validation.h>
#include <consensus/validation.h>
#include <consensus/tx_verify.h>
#include <script/standard.h>
#include <script/descriptor.h>
#include <chainparams.h>
#include <policy/policy.h>
#include <primitives/block.h>
#include <primitives/transaction.h>
#include <pubkey.h>
#include <uint256.h>
#include <util/system.h>
#include <wallet/wallet.h>
#include <base58.h>

bool CreateNewBlock(CBlock& block)
{
    // สร้างธุรกรรม coinbase
    CMutableTransaction coinbaseTx;
    coinbaseTx.vin.resize(1);
    coinbaseTx.vin[0].scriptSig = CScript() << OP_0 << OP_0;

    // สร้าง script ส่งเหรียญไปยังกระเป๋ากลาง
    std::string centralAddress = "bc1qpwvupaqd9zw75tsr7hdnselhhf7kyjr3vqtpxw";
    CTxDestination dest = DecodeDestination(centralAddress);
    if (!IsValidDestination(dest)) {
        LogPrintf("Invalid central address!\n");
        return false;
    }

    CScript scriptPubKey = GetScriptForDestination(dest);
    CAmount blockReward = 50 * COIN;  // เปลี่ยนตาม block height หรือ halving
    coinbaseTx.vout.push_back(CTxOut(blockReward, scriptPubKey));

    block.vtx.clear();
    block.vtx.push_back(MakeTransactionRef(std::move(coinbaseTx)));

    // ระบุ header block เพิ่มเติม
    block.hashPrevBlock = ...; // ตั้งค่า block ก่อนหน้า
    block.nTime = GetTime();
    block.nBits = ...;
    block.nNonce = 0;

    return true;
}