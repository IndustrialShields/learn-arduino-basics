#include <SPI.h>
#include <Ethernet2.h>

// the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x26 };

// WEB defaults to port 80
EthernetServer server = EthernetServer(80);

void setup()
{
  Serial.begin(9600);

  // initialize the ethernet device
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP address " + Ethernet.localIP());
  }

  // start listening for clients
  server.begin();
}

void loop()
{
  // if an incoming client connects, there will be bytes available to read:
  EthernetClient client = server.available();
  if (client > 0) {
    client.println("HTTP/1.0 200K");
    client.println();
    // read bytes from the incoming client and write them back
    // to any clients connected to the server:
    while (client.available() > 0) {
      char inChar = client.read();
      client.write(inChar);
      Serial.print(inChar);
    }

    client.print("Response an analog value");
    client.println(analogRead(A0));
    client.println();
    client.stop();
  }
}
