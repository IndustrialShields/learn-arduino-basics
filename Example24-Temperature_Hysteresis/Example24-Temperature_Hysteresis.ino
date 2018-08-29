const int sensorPin = A0;
const float baselineTemp = 20.0;
int state = 0;

void setup() {
  Serial.begin(9600);
  for (int pinNumber = 4; pinNumber < 7; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;

  if ((temperature < baselineTemp) || ((state == 1) && (temperature < baselineTemp + 1))) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    state = 0;
  }
  else if (((state == 0) && (temperature >= baselineTemp + 2)) || ((state == 2) && (temperature < baselineTemp + 3))) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    state = 1;
  }
  else if (((state == 1) && (temperature >= baselineTemp + 4)) || ((state == 3) && (temperature < baselineTemp + 5))) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    state = 2;
  }
  else if (temperature >= baselineTemp + 6) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    state = 3;
  }
  else {

  }
  delay(1);

  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'c' || c == 'C') {
      Serial.print("Sensor Value: ");
      Serial.print(sensorVal);
      Serial.print(", Volts: ");
      Serial.print(voltage);
      Serial.print(", degrees C: ");
      Serial.println(temperature);
    }
    else if (c == 'f' || c == 'F') {
      Serial.print("Sensor Value: ");
      Serial.print(sensorVal);
      Serial.print(", Volts: ");
      Serial.print(voltage);
      Serial.print(", degrees F: ");
      Serial.println(temperature * 1.8 + 32.0);
    }
    else Serial.println("Invalid character... c or C for Celsius and f or F for Fahrenheit");
  }

  //Para imprimir por Serial Plotter
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(state);
}
