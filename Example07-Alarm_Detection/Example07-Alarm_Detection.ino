const int analogPin = A0;   // pin that the sensor is attached to
const int outputPin = 5;       // pin that the LED is attached to
const int threshold = 400;  // an arbitrary threshold level that's in the range of the analog input
boolean alarm;				      // true = ALARM, false = NO ALARM

void setup() {
  // initialize the output pin as an output:
  pinMode(outputPin, OUTPUT);

  // initialize serial communications:
  Serial.begin(9600);

  // initialize the alarm value
  int analogValue = analogRead(analogPin);
  if (analogValue > threshold) {
    alarm = true;
  }
  else alarm = false;
}

void loop() {
  // read the value of the potentiometer:
  int analogValue = analogRead(analogPin);

  // if the analog value is high enough, turn the output on:
  if (analogValue > threshold) {
    if (alarm == false) {
      digitalWrite(outputPin, HIGH);
      Serial.println("Alarm active");
      alarm = true;
    }
  } else {
    if (alarm == true) {
      digitalWrite(outputPin, LOW);
      Serial.println("Alarm inactive");
      alarm = false;
    }
  }

  // print values
  Serial.print(analogValue);
  Serial.print(" ");
  Serial.print(threshold);
  Serial.print(" ");
  Serial.println(alarm);
  delay(50);
}
