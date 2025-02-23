#include <Wire.h>

void setup() {
  Serial.begin(9600);  // Mulai komunikasi serial
  Wire.begin();        // Inisialisasi komunikasi I2C
  Serial.println("Scanning I2C devices...");

  // Pindai alamat dari 8 hingga 127
  for (byte address = 8; address < 120; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
    }
  }
  
  Serial.println("Scan complete!");
}

void loop() {
  // Tidak ada proses di loop
}
