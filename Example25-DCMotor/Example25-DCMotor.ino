int pin2 = 5; // L293D pin 2
int pin7 = 6; // L293D pin 7
int analogInputPin = A1;

int analogValue;
int pwm1;
int pwm2;

void setup()
{
  pinMode(pin2, OUTPUT);
  pinMode(pin7, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  // get analog input value
  analogValue = analogRead(analogInputPin);

  // map inputs from 0-1023 (10 bits ADC input) to 0-255 (8 bits PWM)
  pwm1 = map(analogValue, 0, 1023, 0, 255);
  pwm2 = map(analogValue, 0, 1023, 255, 0);

  // set PWM outputs
  analogWrite(pin2, pwm1);
  analogWrite(pin7, pwm2);

  // to serial plotter
  Serial.print(analogValue);
  Serial.print(" ");
  Serial.print(pwm1);
  Serial.print(" ");
  Serial.println(pwm2);

}
