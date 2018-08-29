// this constant won't change:
const int buttonPin = 2;     // the pin that the pushbutton is attached to
const int outputPin = 5;     // the pin that the output is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize the output as an output:
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW); //Inicialmente apagado
  // initialize serial communication:
  Serial.begin(9600);
  lastButtonState = digitalRead(buttonPin); //inicializo el estado del pulsador
}

void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == LOW) {
      buttonPushCounter++;
      Serial.println("Falling edge");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
      if (buttonPushCounter % 4 == 0) {
        int outputValue = digitalRead(outputPin);
        digitalWrite(outputPin, !outputValue);
        !outputValue ? Serial.println("output HIGH") : Serial.println("output LOW");
      }
    }
    else {
      Serial.println("Rising edge");
    }
  }
  // save the current state as the last state,
  // for next time through the loop
  lastButtonState = buttonState;
}
