void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  String title = "Interactive menu";
  for (int i = 0; i < title.length(); i++) {
    Serial.print("-");
  }
  Serial.print("\n" + title + "\n");
  for (int i = 0; i < title.length(); i++) {
    Serial.print("-");
  }
  Serial.println();
}

void loop() {
  int response;
  do {
    response = menu();
    switch (response) {
      case 1:
        Serial.println("-------> HIGH");
        digitalWrite(5, HIGH);
        break;
      case 2:
        Serial.println("-------> LOW");
        digitalWrite(5, LOW);
        break;
      case 3:
        seconds();
        break;
      case 4:
        Serial.println("-------> BYE");
        while (true) {
        }
        break;
      default:
        Serial.println("Invalid option");
        break;
    }
    // Uncomment when using a terminal app (i.e. putty)
    //clean();
  } while ((response < 1) || (response > 4));
}

int menu() {
  String readText = "";

  Serial.println("Type an option:");
  Serial.println("1 - Turn on an output");
  Serial.println("2 - Turn off an output");
  Serial.println("3 - Count seconds");
  Serial.println("4 - Finish");

  while (Serial.available() == 0) {
  }

  do {
    char c;
    c = Serial.read();
    readText += c;
    delay(5);
  }  while (Serial.available() > 0);

  if (readText.toInt() != 0)
    return readText.toInt();
  else return 0;

}

void seconds() {
  int spent = 0;

  while (Serial.available() == 0) {
    Serial.println("-------> Spent " + (String)spent + " seconds");
    delay(1000);
    spent++;
  }

  do {
    Serial.read();
    delay(5);
  }  while (Serial.available() > 0);
}

void clean() {
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");     // cursor to home command
}
