#include <Ethernet2.h>
#include <SPI.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x20
};

void setup() {
  Serial.begin(9600);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP DHCP address: ");
    Serial.println(Ethernet.localIP());
  }
}

void loop() {
  Serial.print("'ping " + Ethernet.localIP() + "' to check it works");

  for (;;)
    ;
}
