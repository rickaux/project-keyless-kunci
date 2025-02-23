#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>

#define SDA_PIN 10       // Pin SS (atau RQ) untuk RFID
#define RST_PIN 9        // Pin RST untuk RFID
#define RELAY_STARTER 7  // Relay Starter (untuk menyalakan mesin)
#define RELAY_MESIN 8    // Relay Mesin (utama)
#define TIMEOUT 5000     // Waktu timeout sebelum mesin mati (5 detik)

LiquidCrystal_I2C lcd(0x26, 16, 2);
MFRC522 rfid(SDA_PIN, RST_PIN);

unsigned long lastTagTime = 0;
bool mesinNyala = false;

void setup() {
    pinMode(RELAY_STARTER, OUTPUT);
    pinMode(RELAY_MESIN, OUTPUT);
    digitalWrite(RELAY_STARTER, HIGH); // Active LOW (mati awalnya)
    digitalWrite(RELAY_MESIN, HIGH);

    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();

    lcd.init();
    lcd.backlight();

    Serial.println("=== Sistem Siap ===");

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
        Serial.print("✅ UID Kartu: ");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Kartu Terbaca:");

        for (byte i = 0; i < rfid.uid.size; i++) {
            Serial.print(rfid.uid.uidByte[i], HEX);
            Serial.print(" ");
            lcd.setCursor(i * 3, 1);
            lcd.print(rfid.uid.uidByte[i], HEX);
        }
        Serial.println();

        // **1. Nyalakan Starter (Relay 1)**
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menstarter Mesin");
        digitalWrite(RELAY_STARTER, LOW);  // Starter ON
        delay(2000);                       // Tunggu 2 detik
        digitalWrite(RELAY_STARTER, HIGH); // Starter OFF

        // **2. Nyalakan Mesin (Relay 2) setelah Starter mati**
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mesin Menyala");
        digitalWrite(RELAY_MESIN, LOW);  // Mesin ON
        mesinNyala = true;
        lastTagTime = millis();

        delay(1000);
        rfid.PICC_HaltA(); // Matikan komunikasi RFID
    }

    // **Matikan Mesin jika timeout**
    if (mesinNyala && millis() - lastTagTime > TIMEOUT) {
        digitalWrite(RELAY_MESIN, HIGH);  // Mesin OFF
        mesinNyala = false;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mesin Dimatikan");
        delay(2000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tempelkan Kartu");
    }
}
