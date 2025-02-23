/*
 * ==============================================
 *  RFID Starter & Mesin Control dengan LCD I2C
 * ==============================================
 *  
 *  📌 Deskripsi:
 *  - Sistem menggunakan RFID RC522 untuk menyalakan mesin.
 *  - Saat kartu ditempelkan, starter akan menyala selama 2 detik.
 *  - Setelah starter mati, mesin utama akan menyala.
 *  - Mesin otomatis mati setelah timeout 5 detik.
 *  - LCD I2C digunakan untuk menampilkan status sistem.
 *  
 *  🛠 Hardware yang digunakan:
 *  - Arduino Uno R3
 *  - RFID RC522
 *  - LCD 16x2 I2C (Alamat: 0x26)
 *  - Relay 4 Channel Active Low
 *  
 *  🔌 Wiring:
 *  ----------------------------------------------
 *  | Komponen    | Pin Arduino | Keterangan     |
 *  ----------------------------------------------
 *  | RFID RC522  |            |                |
 *  | ----------- | ---------- | -------------- |
 *  | SDA (SS)    | 10         | (Bisa diganti RQ) |
 *  | SCK         | 13         | SPI Clock      |
 *  | MOSI        | 11         | SPI MOSI       |
 *  | MISO        | 12         | SPI MISO       |
 *  | RST         | 9          | Reset RFID     |
 *  | GND         | GND        | Ground         |
 *  | 3.3V        | 3.3V       | Power RFID     |
 *  ----------------------------------------------
 *  | LCD I2C     |            |                |
 *  | ----------- | ---------- | -------------- |
 *  | SDA         | A4         | I2C Data       |
 *  | SCL         | A5         | I2C Clock      |
 *  | GND         | GND        | Ground         |
 *  | VCC         | 5V         | Power LCD      |
 *  ----------------------------------------------
 *  | Relay       |            |                |
 *  | ----------- | ---------- | -------------- |
 *  | Starter     | 7          | Relay Starter  |
 *  | Mesin       | 8          | Relay Mesin    |
 *  | GND         | GND        | Ground         |
 *  | VCC         | 5V         | Power Relay    |
 *  ----------------------------------------------
 *  
 *  📝 Catatan:
 *  - Pastikan alamat I2C LCD benar dengan scanner I2C.
 *  - Gunakan power supply yang cukup untuk relay dan RFID.
 *  
 *  🚀 Dibuat oleh: [Nama Anda]
 *  📅 Tanggal: 23 Februari 2025
 *  
 */



#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>

// **Konfigurasi Pin**
#define SDA_PIN 10        // Pin SS untuk RFID
#define RST_PIN 9         // Pin RST untuk RFID
#define RELAY_MESIN 8     // Relay utama mesin
#define RELAY_STARTER 7   // Relay untuk starter
#define TIMEOUT 5000      // Timeout mesin mati (5 detik)

LiquidCrystal_I2C lcd(0x26, 16, 2); // Pastikan alamat I2C benar
MFRC522 rfid(SDA_PIN, RST_PIN);

unsigned long lastTagTime = 0;
bool mesinNyala = false;
bool starterSiap = false; // Menandakan apakah mesin siap distarter

void setup() {
    pinMode(RELAY_MESIN, OUTPUT);
    pinMode(RELAY_STARTER, OUTPUT);
    digitalWrite(RELAY_MESIN, HIGH);   // Mesin OFF (Active LOW)
    digitalWrite(RELAY_STARTER, HIGH); // Starter OFF (Active LOW)

    SPI.begin();
    rfid.PCD_Init();
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);

    // **Animasi Loading**
    for (int i = 0; i < 16; i++) {
        lcd.clear();
        lcd.setCursor(i, 0);
        lcd.print("Loading...");
        lcd.setCursor(0, 1);
        lcd.print("Tunggu sebentar");
        delay(150);
    }
    delay(1000);
    lcd.clear();
    lcd.print("Tempelkan Kartu");
}

void loop() {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        Serial.print("Kartu Terbaca, UID: ");
        for (byte i = 0; i < rfid.uid.size; i++) {
            Serial.print(rfid.uid.uidByte[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        if (!mesinNyala) { 
            // **1️⃣ Jika Mesin Belum Nyala, Nyalakan Mesin**
            digitalWrite(RELAY_MESIN, LOW);  // Mesin ON
            mesinNyala = true;
            starterSiap = true;  // Setelah mesin nyala, starter bisa digunakan
            lastTagTime = millis();

            lcd.clear();
            lcd.print("Mesin Nyala");
            delay(1000);

        } else if (starterSiap) {
            // **2️⃣ Jika Mesin Sudah Nyala, Nyalakan Starter**
            lcd.clear();
            lcd.print("Starter Aktif...");
            digitalWrite(RELAY_STARTER, LOW);  // Starter ON
            delay(2000);  // Starter nyala selama 2 detik
            digitalWrite(RELAY_STARTER, HIGH); // Starter OFF

            lcd.clear();
            lcd.print("Starter Selesai");
            delay(1000);
            starterSiap = false; // Starter hanya bisa dipakai sekali

        } else {
            // **3️⃣ Jika Starter Sudah Dipakai, Tampilkan Notifikasi**
            lcd.clear();
            lcd.print("Mesin Sudah Nyala");
            delay(1000);
        }

        // **Halt Kartu Agar Tidak Terbaca Terus-Menerus**
        rfid.PICC_HaltA();
    }

    // **4️⃣ Timeout untuk Mematikan Mesin**
    if (mesinNyala && millis() - lastTagTime > TIMEOUT) {
        digitalWrite(RELAY_MESIN, HIGH); // Mesin OFF
        mesinNyala = false;
        starterSiap = false;

        lcd.clear();
        lcd.print("Mesin Mati");
        delay(2000);

        lcd.clear();
        lcd.print("Tempelkan Kartu");
    }
}
