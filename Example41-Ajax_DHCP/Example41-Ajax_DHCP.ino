//----------------------- LIBRARIES ------------------------//
#include <SPI.h>
#include <Ethernet2.h>

//----------------------- CONSTANTS ------------------------//
#define DEBUG 1

const int outputPin = 5;

//----------------------- VARIABLES RED ------------------------//
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x28};
EthernetServer server = EthernetServer(80);

//----------------------- VARIABLES ------------------------//
boolean outputValue = 0; //0 = OFF, 1 = ON
boolean manual = 0;  // 1 = manual connected
int threshold = 1000;

//----------------------- SETUP ----------------------------//
void setup()
{
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }

  // print your local IP address:
  Serial.println("IP address " + Ethernet.localIP());

  server.begin();
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, outputValue);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

//----------------------- LOOP -----------------------------//
void loop()
{
  //Lectura datos
  int read_A0 =  analogRead(A0);
  int read_A1 =  analogRead(A1);
  int read_A2 =  analogRead(A2);

  if (((read_A1) > threshold) && !outputValue && !manual) //Solo regulo si no está en manual
  {
    outputValue = HIGH;
    digitalWrite(outputPin, outputValue);
    Serial.println("Turn on output");
  }
  if (((read_A1) < (threshold + 10)) && ouputValue && !manual) //hiteresis = 10
  {
    outputValue = LOW;
    digitalWrite(outputPin, outputValue);
    Serial.println("Turn off output");
  }

  //WEB
  EthernetClient client = server.available(); //Cliente conectado al servidor
  if (client) {
    String request = "";
    while (client.available()) {
      char c = client.read();
      if (c == '\n') break;   //No es necsario vaciar buffer, se hace con el client.stop().
      else request += c;
    }
#if DEBUG
    Serial.print(F("------------------------>  "));
    Serial.println(request);
#endif
    if (request.startsWith("GET / HTTP")) sendIndexResponse(client);
    else if (request.startsWith("GET /ajax HTTP")) sendAjaxResponse(client);
    else if (request.startsWith("GET /boton/")) sendManualResponse(client, request.substring(11, request.indexOf(" HTTP/1.1")));
    else if (request.startsWith("GET /threshold/")) sendThresholdResponse(client, request.substring(12, request.indexOf(" HTTP/1.1")));
    else {
      //NO MUESTRO NADA
      client.println(F("HTTP/1.1 200 OK"));
      client.println(F("Content-Type: text/html\r\n"));
      client.println();
      client.println(F("Request not registered"));
#if DEBUG
      Serial.println(F("Request not registered"));
#endif
      client.stop();
    }
  }
}

//--------------------- FUNCTIONS --------------------------//

void sendIndexResponse(EthernetClient client_web) {
  Serial.println(F("Send default response"));
  client_web.println(F("HTTP/1.1 200 OK"));
  client_web.println(F("Content-Type: text/html"));
  client_web.println();
  client_web.print("<!DOCTYPE html>");
  client_web.print(F("<html><head><title>AJAX Arduino example</title>"));
  client_web.print(F("<style type=\"text/css\">body {color: black;background-color: #D7DBDA;}"));
  client_web.print(F("div {background-color: #006666; color: white; border: 1px solid black; padding: 5px; margin: 5px; height: auto;"));
  client_web.print(F("width: 100px; border-radius: 10px; text-align: center; float: left; font-weight:bold;} .cabecera {clear: left;}"));
  client_web.print(F(".formulario {background-color: #004F00; width: auto;}.oculto{background-color: #004F00; border: none;}"));
  client_web.print(F(".OFF {background-color: #006666;} .ON {background-color: red;}"));
  client_web.print(F("input, #boton {width: 80px; border-radius: 5px; font-weight:bold;text-align: center;}#boton:hover{border: 3px solid black;}"));
  client_web.print(F("#boton:hover{border: 3px solid black;} #principal {background-color: #000F00;}"));
  client_web.print(F("</style>"));
  client_web.print(F("<script type=\"text/javascript\">function update(){var xhttp;xhttp=new XMLHttpRequest();xhttp.onreadystatechange=function(){"));
  client_web.print(F("if (xhttp.readyState == 4 && xhttp.status == 200) {var json = JSON.parse(xhttp.responseText);"));
  client_web.print(F("document.getElementById(\"A0\").innerHTML = json.arduino.A0;"));
  client_web.print(F("document.getElementById(\"A1\").innerHTML = json.arduino.A1;"));
  client_web.print(F("document.getElementById(\"A2\").innerHTML = json.arduino.A2;"));
  client_web.print(F("document.getElementById(\"D13\").innerHTML = json.arduino.outputValue;"));
  client_web.print(F("document.getElementById(\"D13\").className = json.arduino.outputValue;"));
  client_web.print(F("document.getElementById(\"boton\").innerHTML = json.arduino.manual;"));
  client_web.print(F("document.getElementById(\"boton\").className = json.arduino.manual;"));
  client_web.print(F("document.getElementById(\"dato_input\").value = json.arduino.threshold;}};"));
  client_web.print(F("xhttp.open(\"GET\", \"http://")); //Imprimo la IP del propio arduino
  client_web.print(Ethernet.localIP());
  client_web.print(F("/ajax\", true);xhttp.send();}"));
  client_web.print(F("function boton_manual(){var xhttp;xhttp = new XMLHttpRequest();var boton = document.getElementById(\"boton\").innerHTML;"));
  client_web.print(F("if (boton == \"ON\" ){boton = \"OFF\";document.getElementById(\"boton\").className = 'OFF';}"));
  client_web.print(F("else {boton = \"ON\";document.getElementById(\"boton\").className = 'ON';}document.getElementById(\"boton\").innerHTML = boton;var url = \"http://"));
  client_web.print(Ethernet.localIP());
  client_web.print(F("/boton/\" + boton; xhttp.open(\"GET\", url, true); xhttp.send();update();}"));
  client_web.print(F("function cambia_threshold(){var xhttp; xhttp = new XMLHttpRequest();var value= document.getElementById(\"dato_input\").value; var url = \"http://"));
  client_web.print(Ethernet.localIP());
  client_web.print(F("/threshold/\" + value; xhttp.open(\"GET\", url, true); xhttp.send();setTimeout(function(){update()},500);}"));
  client_web.print(F("function cambiaIntervalo(tiempo){if (tiempo==0) clearInterval(id_interval);else id_interval = setInterval('update()',tiempo);}"));
  client_web.print(F("var id_interval = setInterval('update()',5000);"));
  client_web.print(F("</script></head><body>"));
  client_web.print(F("<div id = \"principal\" class=\"formulario\"><h2>AJAX example on Arduino</h2><div id=\"datos\" class=\"formulario\">"));
  client_web.print(F("<p>DATA</p><div class=\"cabecera\">Input A0</div><div id=\"A0\">"));
  client_web.print("N/A");
  client_web.print(F("</div><div class=\"cabecera\">Input A1</div><div id=\"A1\">"));
  client_web.print("N/A");
  client_web.print(F("</div><div class=\"cabecera\">Input A2</div><div id=\"A2\">"));
  client_web.print("N/A");
  client_web.print(F("</div><div class=\"cabecera\">Output</div><div id=\"D13\" "));
  outputValue ? client_web.print(F("class=\"ON\">ON")) : client_web.print(F("class=\"OFF\">OFF"));
  client_web.print(F("</div></div><div class=\"formulario\"><p>CONFIGURATION</p><div class=\"cabecera\">Input A1 threshold</div>"));
  client_web.print(F("<div id=\"threshold\" class=\"oculto\"><input id=\"dato_input\" type=\"number\" onchange=\"cambia_threshold()\" value=\""));
  client_web.print(threshold);
  client_web.print(F("\" onmouseover=\"cambiaIntervalo(0)\" onmouseout=\"cambiaIntervalo(5000)\">"));
  client_web.print(F("</div><div class=\"cabecera\">Manual button</div><div id=\"boton\" onmouseover=\"cambiaIntervalo(0)\" onmouseout=\"cambiaIntervalo(5000)\""));
  client_web.print(F("onclick=\"boton_manual()\" "));
  manual ? client_web.print(F("class=\"ON\">ON")) : client_web.print(F("class=\"OFF\">OFF"));
  client_web.println(F("</div></div></div></body></html>"));
  client_web.stop(); 
}

void sendAjaxResponse(EthernetClient client_ajax) {
#if DEBUG
  Serial.println(F("Send AJAX response"));
#endif
  client_ajax.println(F("HTTP/1.1 200 OK"));
  client_ajax.println(F("Content-Type: application/json; charset=utf-8"));
  client_ajax.println();
  client_ajax.print(F("{\"arduino\":{\"A0\":\""));
  client_ajax.print(analogRead(A0));
  client_ajax.print(F("\",\"A1\":\""));
  client_ajax.print(analogRead(A1));
  client_ajax.print(F("\",\"A2\":\""));
  client_ajax.print(analogRead(A2));
  client_ajax.print(F("\",\"outputValue\":\""));
  outputValue ? client_ajax.print(F("ON")) : client_ajax.print(F("OFF"));
  client_ajax.print(F("\",\"manual\":\""));
  manual ? client_ajax.print(F("ON")) : client_ajax.print(F("OFF"));
  client_ajax.print(F("\",\"threshold\":\""));
  client_ajax.print(threshold);
  client_ajax.println(F("\"}}"));
  client_ajax.stop();  //Cierro el cliente
}

void sendManualResponse(EthernetClient client_ajax, String value) {
  boolean result = 1;
#if DEBUG
  Serial.println(value);
#endif
  if (value == "ON") {
    manual = 1;
    outputValue = 1;
    digitalWrite(outputPin, outputValue);
    Serial.println("Turn on output");
  }
  else if (value == "OFF") {
    manual = 0;
    Serial.println("Auto mode");
  }
  else result = 0;
  client_ajax.println(F("HTTP/1.1 200 OK"));
  client_ajax.println(F("Content-Type: text/html\r\n"));
  client_ajax.println();
  result ? client_ajax.println(F("OK")) : client_ajax.println(F("KO"));
  client_ajax.stop();
}

void sendThresholdResponse(EthernetClient client_ajax, String value) {
  boolean result = 1;
#if DEBUG
  Serial.println(value);
#endif
  if ((value.toInt() > 1023) || (value.toInt() < 0)) result = 0;
  else threshold = value.toInt();
  client_ajax.println(F("HTTP/1.1 200 OK"));
  client_ajax.println(F("Content-Type: text/html\r\n"));
  client_ajax.println();
  result ? client_ajax.println(F("OK")) : client_ajax.println(F("KO"));
  client_ajax.stop();
}
