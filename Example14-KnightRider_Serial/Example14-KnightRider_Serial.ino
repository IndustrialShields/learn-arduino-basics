int pinArray[] = {4, 5, 6};
int count = 0;
int timer = 100;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Type the timer value (10 to 500ms):");

  for (count = 0; count < 3; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
}

void loop() {
  for (count = 0; count < 3; count++) {
    if (Serial.available()) timer = read_timer();
    digitalWrite(pinArray[count], HIGH);
    delay(timer);
    digitalWrite(pinArray[count], LOW);
    delay(timer);
  }
  for (count = 2; count >= 0; count--) {
    if (Serial.available()) timer = read_timer();
    digitalWrite(pinArray[count], HIGH);
    delay(timer);
    digitalWrite(pinArray[count], LOW);
    delay(timer);
  }
}

int read_timer() {
  String readText = "";
  do {
    char c = Serial.read();
    readText += c;
    delay(5);
  }  while (Serial.available() > 0);

  int readNumber = readText.toInt();

  if (readNumber >= 10 && readNumber <= 500) {
    Serial.println("New timer value " + (String)readNumber + " ms");
    return readNumber;
  }
  else {
    Serial.println("Invalid timer value");
    return timer;
  }
  Serial.println("Type the timer value (10 to 500ms):");
}

