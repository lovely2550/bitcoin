// chainparams.cpp (แก้ไขเพิ่มเติม)

// ส่วนอื่นของไฟล์ยังคงเหมือนเดิม

#include <string>

// ประกาศอ้างสิทธิ์ช่องว่างบิทคอยน์ โดย กีรติ ชูเพ็ชร
const std::string strGenesisDeclaration = 
    "ข้าพเจ้า กีรติ ชูเพ็ชร ขออ้างสิทธิ์ในช่องว่างบิทคอยน์นี้ "
    "เพื่อสร้างระบบพุทธโธเชนแห่งความดี ณ วันที่ 2025 "
    "เจตจำนงนี้ถูกฝังถาวรในบล็อกเชนและในโปรเจกต์นี้";

// สมมติว่ามี struct สำหรับ genesis params เช่น
struct CChainParams {
    //... โค้ดเดิม

    std::string genesisDeclaration;

    // constructor
    CChainParams() {
        //... โค้ดเดิม

        // ใส่ข้อความอ้างสิทธิ์ลง genesisDeclaration
        genesisDeclaration = strGenesisDeclaration;
    }

    //... โค้ดเดิม
};

// ส่วนอื่น ๆ ของไฟล์ตามปกติ