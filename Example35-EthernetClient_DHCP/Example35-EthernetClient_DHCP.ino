#include <Ethernet2.h>
#include <SPI.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x22
};

byte google[] = { 64, 233, 187, 99 };
char url[] = "www.industrialshields.com";

EthernetClient client;
String webString = "";

void setup()
{
  Serial.begin(9600);
  String command = "";
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP address " + Ethernet.localIP());
  }

  delay(1000);
  Serial.println("MENU");
  Serial.println("1 - google");
  Serial.println("2 - industrialshields");
  while (Serial.available() == 0) {
    //nada
  }
  do {
    char c = Serial.read();
    command += c;
    delay(5);
  }  while (Serial.available() > 0);

  int option = command.toInt();
  switch (option) {
    case 1:
      if (client.connect(google, 80)) {
        Serial.println("connected");
        client.println("GET / HTTP/1.0");
        client.println();
      }
      else {
        Serial.println("connection failed");
      }

      break;
    case 2:
      if (client.connect(url, 80)) {
        Serial.println("connected");
        client.println("GET / HTTP/1.1");
        client.println("Host: www.industrialshields.com");
        client.println("Connection: close");
        client.println();
      }
      else {
        Serial.println("connection failed");
      }
      break;
    default:
      Serial.println("Invalid option");
      break;
  }
}

void loop()
{
  if (client.available()) {
    char c = client.read();
    webString += c;
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for (;;)
      ;
  }
}

