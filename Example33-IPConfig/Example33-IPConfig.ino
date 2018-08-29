#include <Ethernet2.h>
#include <SPI.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x21};
byte ip[] = {192, 168, 1, 250};
byte DNS[] = {8, 8, 8, 8};
byte gateway[] = {192, 168, 1, 1};
byte subnet[] = {255, 255, 255, 0};

/* Or
    IPAddress ip(192, 168, 1, 250);
    IPAddress dnServer(8, 8, 8, 8);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
*/

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, DNS, gateway, subnet);
  Serial.println("IP address " + Ethernet.localIP());
}

void loop() {
  Serial.print("'ping " + Ethernet.localIP() + "' to check it works");

  for (;;)
    ;
}
