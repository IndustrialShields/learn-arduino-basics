const int analogPin = A0;       // pin that the sensor is attached to
const int outputPin = 5;        // pin that the LED is attached to
int threshold;
const int threshold_base = 400;
const int hysteresis = 50;      // Hysteresis value
boolean alarm;				          // true = ALARM, false = NO ALARM

void setup() {
  // initialize the LED pin as an output:
  pinMode(outputPin, OUTPUT);

  // initialize serial communications:
  Serial.begin(9600);

  // initialize the alarm value
  int analogValue = analogRead(analogPin);
  if (analogValue > threshold_base) {
    alarm = true;
    threshold = threshold_base - hysteresis;
    digitalWrite(outputPin, HIGH);
  }
  else {
    alarm = false;
    threshold = threshold_base + hysteresis;
    digitalWrite(outputPin, LOW);
  }
}

void loop() {
  // read the value of the potentiometer:
  int analogValue = analogRead(analogPin);

  // if the analog value is high enough, turn on the LED:
  if (analogValue > threshold) {
    if (alarm == false) {
      digitalWrite(outputPin, HIGH);
      Serial.println("Alarm active");
      alarm = true;
      threshold = threshold_base - hysteresis;
    }
  } else {
    if (alarm == true) {
      digitalWrite(outputPin, LOW);
      Serial.println("Alarm inactive");
      alarm = false;
      threshold = threshold_base + hysteresis;
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
