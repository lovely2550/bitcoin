// init.cpp — เริ่มระบบหลัก พร้อมระบบภาวนาแห่งพุทธโธเชน

#include "init.h" #include "wallet/wallet.h" #include "util/system.h" #include "rpc/server.h" #include "rpcmeditation.cpp" // เชื่อมระบบภาวนา

bool AppInitMain() { LogPrintf("[Init] เริ่มระบบหลักของพุทธโธเชน\n");

// โหลด Wallet
CWallet* pwalletMain = nullptr;
pwalletMain = GetWallet("default"); // สมมุติชื่อ wallet เป็น default

if (!pwalletMain) {
    LogPrintf("[Init] ไม่พบ wallet\n");
    return false;
}

// เรียกใช้ระบบภาวนา
StartBuddhoChain(pwalletMain);

LogPrintf("[Init] ระบบพร้อมรับคำภาวนาและแจกเหรียญ\n");
return true;

}

void Shutdown() { LogPrintf("[Shutdown] กำลังปิดระบบพุทธโธเชน...\n"); // เพิ่มคำสั่ง shutdown ต่าง ๆ ที่จำเป็น }

