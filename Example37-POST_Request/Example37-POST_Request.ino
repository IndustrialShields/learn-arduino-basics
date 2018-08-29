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

  String post_string = "arduino=" + Num_Arduino + "&mensaje=" + Mensaje;

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("POST /POST_Request.php  HTTP/1.1");
    client.println("Host: www.industrialshields.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(post_string.length());
    client.println("");
    client.println(post_string);
    client.println("");
    Serial.println("Peticion enviada---->");
    Serial.println("POST /POST_Request.php  HTTP/1.1");
    Serial.println("Host: www.industrialshields.com");
    Serial.println("Content-Type: application/x-www-form-urlencoded");
    Serial.println("Connection: close");
    Serial.print("Content-Length: ");
    Serial.println(post_string.length());
    Serial.println("");
    Serial.println(post_string);
    Serial.println("");
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
