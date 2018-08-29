String readText = "";
int readNumber;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Type an integer:");
  while (Serial.available() == 0) {
    // wait some text
  }

  do {
    char c;
    c = Serial.read();
    readText += c;
    delay(5);
  } while (Serial.available() > 0);

  Serial.println("Read text: \"" + readText + "\"");

  readNumber = readText.toInt();
  Serial.println(readNumber);

  if ((readNumber != 0) || (readText == "0")) {
    Serial.print("The double of your number is: ");
    Serial.println(readNumber * 2);
  }
  else Serial.println("It was not a valid number");
}

void loop() {
  // Nothing to do
}

