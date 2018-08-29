//Data Acquisition (DAQ) a tarjeta SD

#include <SPI.h>
#include <SD.h>
#include <MsTimer2.h>

const int chipSelect = 53;
const int temperatura_pin = A0;

String dataString;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  MsTimer2::set(5000, saveData); // 5 sec period
  MsTimer2::start();

  Serial.println("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  if (!SD.exists("temp_log.csv")) {
    File dataFile = SD.open("temp_log.csv", FILE_WRITE);
    dataFile.println("Time(sec),Temperature");
    Serial.println("Creo nuevo fichero");
    dataFile.close();
  }
  else Serial.println("file already exists");

  Serial.println("MENU");
  Serial.println("1 - Print last SD line");
  Serial.println("2 - Print SD card data");
  Serial.println("3 - Delete SD card data");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '1') {
      Serial.println("Last line: \"" + dataString + "\"");
    }
    else if (c == '2') {
      printData();
    }
    else if (c == '3') {
      deleteData();
    }
    else Serial.println("Invalid option...");
    //Muestra menú
    Serial.println("------------------------");
    Serial.println("MENU");
    Serial.println("1 - Print last SD line");
    Serial.println("2 - Print SD card data");
    Serial.println("3 - Delete SD card data");
    Serial.println("------------------------");
  }
  while (Serial.available() > 0) {
    Serial.read();
    delay(5);
  }
}

void saveData()
{
  //read temperature
  int sensorVal = analogRead(temperatura_pin);
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;

  // make a string for assembling the data to log:
  dataString = String(millis() / 1000) + ",";

  dataString = dataString + (String)temperature ;

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("temp_log.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    //Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening temp_log.csv");
  }
}

void printData() {
  File dataFile = SD.open("temp_log.csv");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening temp_log.csv");
  }
}

void deleteData() {
  if (SD.remove("temp_log.csv")) {
    File dataFile = SD.open("temp_log.csv", FILE_WRITE);
    dataFile.println("Time(sec),Temperature");
    Serial.println("File deleted");
    dataFile.close();
  }
  else Serial.println("error deleting file");
}

