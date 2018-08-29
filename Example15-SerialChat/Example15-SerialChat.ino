#include <SoftwareSerial.h>

// Only available for Ardbox Analog HF and Ardbox Relay HF
// configured as HW RS-485 and SW RS-232
SoftwareSerial mySerial(8, 4); // RS-232 RX pin: 8, RS-232 TX pin: 4

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Starting Chat Program...");
  mySerial.begin (4800);
  delay(1000);
  mySerial.println("Hello chat program!");
}

void loop() {
  if (mySerial.available()) {
    Serial.print((char)mySerial.read());
  }
  if (Serial.available()) {
    mySerial.print((char)Serial.read());
  }
}
