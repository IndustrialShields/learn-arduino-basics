String readText = "";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Type some text: ");
  while (Serial.available() == 0) {
    // wait for some text
  }

  do {
    char c;
    delay(5);
    c = Serial.read();
    readText += c;
  }  while (Serial.available() > 0);

  Serial.println("Read text: \"" + readText + "\"");
}

void loop() {
  // Nothing to do
}

