#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  Serial.println("Scanning for I2C devices...");

  for (byte i = 8; i < 120; i++) { // Rentang alamat I2C dari 8 hingga 119
    Wire.beginTransmission(i);
    byte error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(i, HEX);
    }
  }
  
  Serial.println("Scan complete!");
}

void loop() {
  // Tidak ada proses dalam loop
}
