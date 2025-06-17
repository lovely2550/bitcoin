// chainparams.cpp (cleaned version)

#include <string>

// ข้อความประกาศอ้างสิทธิ์ช่องว่างบิทคอยน์
const std::string strGenesisDeclaration = 
    "ข้าพเจ้า กีรติ ชูเพ็ชร ขออ้างสิทธิ์ในช่องว่างบิทคอยน์นี้ "
    "เพื่อสร้างระบบพุทธโธเชนแห่งความดี ณ วันที่ 2025 "
    "เจตจำนงนี้ถูกฝังถาวรในบล็อกเชนและในโปรเจกต์นี้";

struct CChainParams {
    //... โค้ดที่จำเป็นอื่น ๆ

    std::string genesisDeclaration;

    CChainParams() {
        genesisDeclaration = strGenesisDeclaration;
    }

    //... โค้ดอื่น ๆ
};