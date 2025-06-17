// chainparams.cpp

#include <string>

const std::string strGenesisDeclaration = 
    "ข้าพเจ้า กีรติ ชูเพ็ชร ขออ้างสิทธิ์ในช่องว่างบิทคอยน์นี้ "
    "เพื่อสร้างระบบพุทธโธเชนแห่งความดี ณ วันที่ 2025 "
    "เจตจำนงนี้ถูกฝังถาวรในบล็อกเชนและในโปรเจกต์นี้";

struct CChainParams {
    // โค้ดอื่น ๆ ของ chainparams

    std::string genesisDeclaration;

    CChainParams() {
        genesisDeclaration = strGenesisDeclaration;
    }

    // โค้ดอื่น ๆ ตามระบบ
};