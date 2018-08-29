#include <Ethernet2.h>
#include <SPI.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x23
};

byte server[] = { 192, 168, 1, 2};

EthernetClient client;
String num = "";
String message = "";

void setup()
{
  Serial.begin(9600);

  // start the Ethernet connection
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP address " + Ethernet.localIP());
  }

  getData();
  sendRequest();
}

void loop()
{
  getData();
  sendRequest();
}

void getData () {
  num = "";
  message = "";

  Serial.println("----------------------\r\nType a number");
  while (Serial.available() == 0) {
  }
  do {
    char c = Serial.read();
    if ((c > '0') && (c <  'z'))
      num += c;
    delay(5);
  }  while (Serial.available() > 0);

  Serial.println("Type a message");
  while (Serial.available() == 0) {
  }
  do {
    char c = Serial.read();
    if ((c > '0') && (c <  'z'))
      message += c;
    delay(5);
  }  while (Serial.available() > 0);

  Serial.println("num: " + num + "\r\nmessage: " + message);
}

void sendRequest() {
  String webString = "";

  Serial.println("connecting to server...");
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET /GET_Request.php?arduino=");
    client.print(num);
    client.print("&message=");
    client.print(message);
    client.println(" HTTP/1.1");
    client.println("Host: www.industrialshields.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("connection failed");
  }

  while (client.available() == 0) {
  }

  if (client.available()) {
    Serial.println("Response:");
    while (client.available()) {
      char c = client.read();
      webString += c;
    }
    Serial.println(webString);

    client.stop();
  }
}
