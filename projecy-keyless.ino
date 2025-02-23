#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>

#define RQ_PIN 10       // Pin RQ sebagai pengganti SS untuk RFID
#define RST_PIN 9       // Pin RST untuk RFID
#define RELAY_PIN 8     // Relay untuk mesin
#define TIMEOUT 5000    // Waktu timeout sebelum mesin mati (5 detik)

LiquidCrystal_I2C lcd(0x26, 16, 2); // Pastikan alamat LCD benar
MFRC522 rfid(RQ_PIN, RST_PIN);

unsigned long lastTagTime = 0;
bool mesinNyala = false;

void setup() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);  // Relay dalam kondisi OFF (Active LOW)

    // Inisialisasi SPI dan RFID
    SPI.begin();
    rfid.PCD_Init();
    
    // Inisialisasi LCD I2C
    lcd.init();
    lcd.backlight();
    
    Serial.begin(9600);
    Serial.println("Inisialisasi Sistem...");

    // Animasi Loading
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
    if (rfid.PICC_IsNewCardPresent()) {
        if (rfid.PICC_ReadCardSerial()) {
            // Debugging UID Kartu RFID
            Serial.print("UID Kartu: ");
            for (byte i = 0; i < rfid.uid.size; i++) {
                Serial.print(rfid.uid.uidByte[i], HEX);
                Serial.print(" ");
            }
            Serial.println();

            // Nyalakan mesin
            digitalWrite(RELAY_PIN, LOW);  // Mesin menyala (Active LOW)
            mesinNyala = true;
            lastTagTime = millis();

            // Tampilkan pesan di LCD
            lcd.clear();
            lcd.print("Mesin Telah");
            lcd.setCursor(0, 1);
            lcd.print("Dihidupkan");

            delay(1000); // Biarkan teks tampil sebentar
            rfid.PICC_HaltA();  // Matikan komunikasi RFID
        }
    }

    if (mesinNyala && millis() - lastTagTime > TIMEOUT) {
        digitalWrite(RELAY_PIN, HIGH);  // Mesin mati (Active LOW)
        mesinNyala = false;

        lcd.clear();
        lcd.print("Mesin telah");
        lcd.setCursor(0, 1);
        lcd.print("Mati");
        delay(2000); // Biarkan pesan tampil sebentar

        lcd.clear();
        lcd.print("Tempelkan Kartu");
    }
}
