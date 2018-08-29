#include <SPI.h>
#include <Ethernet2.h>

const int outputPin = 5;

//Configuración Ethernet
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x26
};

EthernetServer server = EthernetServer(80);

boolean outputState = LOW;

void setup()
{
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP address " + Ethernet.localIP());
  }

  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);
  outputState = LOW;

  // Listen for clients
  server.begin();
}

void loop()
{
  String request = ""; //Buffer

  EthernetClient client = server.available();
  if (client) {
    while (client.available()) {
      request += char(client.read());
    }
    Serial.println("Request: ");
    Serial.println(request);

    if (request.startsWith("GET / HTTP/1.1")) {
      sendResponse(client);
    }
    else if (request.startsWith("POST / HTTP/1.1")) {
      outputState = !outputState;
      digitalWrite(outputPin, outputState);
      sendResponse(client);
    }
    else {
      client.println("HTTP/1.0 200K");
      client.println();
      client.println();
      client.stop();
      client.flush();
    }
  }
}

void sendResponse(EthernetClient client) {
  client.println("HTTP/1.0 200K");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<body>");
  if (outputState == HIGH) client.println("<p>OUTPUT HIGH</p>");
  else client.println("<p>OUTPUT LOW</p>");
  client.println("<form action=\"\" method=\"post\">");
  if (outputState == HIGH) client.println("<input type=\"submit\" value=\"To LOW\" />");
  else client.println("<input type=\"submit\" value=\"To HIGH\" />");
  client.println("</form>");
  client.println("</body>");
  client.println("</html>");
  client.println();
  client.stop();
  client.flush();
}
