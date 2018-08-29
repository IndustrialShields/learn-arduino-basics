int analogPinArray[] = {A0, A1, A2};
int pinArray[] = {4, 5, 6};
int AnalogData[3];
int DigitalData[3];

unsigned long tiempo = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(pinArray[i], INPUT);
  }
  tiempo = millis();
}

void loop() {
  for (int i = 0; i < 3; i++) {
    AnalogData[i] = analogRead(analogPinArray[i]);
    DigitalData[i] = digitalRead(pinArray[i]);
  }
  if ((millis() -  tiempo) > 5000) {
    tiempo = millis();  //inicio contador
    Serial.println("Analog inputs:");
    for (int i = 0; i < 3; i++) {
      Serial.println ("Pin " + String(analogPinArray[i]) + " ---> " + String(AnalogData[i]));
    }
    Serial.println("Digital inputs:");
    for (int i = 0; i < 3; i++) {
      Serial.println ("Pin " + String(pinArray[i]) + " ---> " + String(DigitalData[i]));
    }
  }
}
