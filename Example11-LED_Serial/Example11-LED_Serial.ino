String readText = "";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Type some text:");

  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    // clear read text before reading it again
    readText = "";
    do {
      char c;
      delay(5);
      c = Serial.read();
      readText += c;
    }  while (Serial.available() > 0);

    Serial.println("Read text: \"" + readText + "\"");

    if (readText.startsWith("HIGH"))
      digitalWrite(5, HIGH);

    if (readText.startsWith("LOW"))
      digitalWrite(5, LOW);

    Serial.println("Type some text:");
  }
}

