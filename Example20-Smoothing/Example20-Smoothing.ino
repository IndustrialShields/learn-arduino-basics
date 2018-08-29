#define PRINT_TIME 0
#define PRINT_EDGES 0

#if PRINT_TIME
unsigned long tiempo = 0;
#endif

// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int ledPin = 9;   //use a 220 ohms resitance

int inputPin = A0;

int lastOutputValue = 0;

void setup()
{
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;
}

void loop() {
#if PRINT_TIME
  Serial.println("------loop------");
  Serial.println(millis() - tiempo);
  tiempo = millis();
#endif
  // subtract the last reading:
  total = total - readings[index];
  // read from the sensor:
  readings[index] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[index];

  // calculate the average:
  average = total / numReadings;
  delay(1);        // delay in between reads for stability
  
  int outputValue = map(average, 0, 1023, 0, 255);

#if !PRINT_EDGES
  analogWrite(ledPin, outputValue);
  // send it to the computer as ASCII digits
  Serial.print("Reading: ");
  Serial.print(readings[index]);
  Serial.print("\tAverage: ");
  Serial.print(average);
  Serial.print("\toutputValue: ");
  Serial.println(outputValue);
#endif

#if PRINT_EDGES
  if (outputValue > lastOutputValue) {
    // fade in from min to max in increments of 5 points:
    for (int fadeValue = lastOutputValue ; fadeValue <= outputValue; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      Serial.print("Reading: ");
      Serial.print(readings[index]);
      Serial.print("\tAverage: ");
      Serial.print(average);
      Serial.print("\tfadeValue: ");
      Serial.println(fadeValue*4);  //multiplied by 4 to see the effect in Serial Plotter
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
    }
  }
  else if (outputValue < lastOutputValue) {
    for (int fadeValue = lastOutputValue ; fadeValue >= outputValue; fadeValue -= 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      Serial.print("Reading: ");
      Serial.print(readings[index]);
      Serial.print("\tAverage: ");
      Serial.print(average);
      Serial.print("\tfadeValue: ");
      Serial.println(fadeValue*4);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
    }
  }
  else {
    Serial.print("Reading: ");
    Serial.print(readings[index]);
    Serial.print("\tAverage: ");
    Serial.print(average);
    Serial.print("\toutputValue: ");
    Serial.println(outputValue*4);
  }
  lastOutputValue = outputValue;
#endif

  // advance to the next position in the array:
  index = index + 1;

  // if we're at the end of the array...
  if (index >= numReadings)
    // ...wrap around to the beginning:
    index = 0;

  delay(50);    //wait 50ms for delay effect
}
