#include <SPI.h>
#include <MFRC522.h>

#define RQ_PIN 10  // Sesuai dengan wiring Anda
#define RST_PIN 9  // Reset pin

MFRC522 rfid(RQ_PIN, RST_PIN);

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();

    Serial.println("Cek RFID...");
    
    byte version = rfid.PCD_ReadRegister(MFRC522::VersionReg);
    if (version == 0x00 || version == 0xFF) {
        Serial.println("GAGAL! RFID tidak terdeteksi.");
    } else {
        Serial.print("RFID terdeteksi! Versi: ");
        Serial.println(version, HEX);
    }
}

void loop() {
}
