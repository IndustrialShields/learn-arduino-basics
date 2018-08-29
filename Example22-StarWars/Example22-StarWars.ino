const float c = 261.63;   // Do
const float d = 293.66;   // Re
const float e = 329.63;   // Mi
const float f = 349.23;   // Fa
const float g = 392.00;   // Sol
const float gS = 415.30;  // Sol#
const float a = 440.00;   // La
const float b = 466.16;   // La#
const float cH = 523.25;  // Do
const float cSH = 554.37; // Do#
const float dH = 587.33;  // Re
const float dSH = 622.25; // Re#
const float eH = 659.26;  // Mi
const float fH = 698.46;  // Fa
const float fSH = 739.99; // Fa#
const float gH = 783.99;  // Sol
const float gSH = 830.61; // Sol#
const float aH = 880.00;  // La

const int speakerPin = 2;
const int output1Pin = 5;
const int output2Pin = 6;

int contador = 0;

void setup()
{
  pinMode(speakerPin, OUTPUT);
  pinMode(output1Pin, OUTPUT);
  pinMode(output2Pin, OUTPUT);
}

void loop()
{
  intro();

  chorus();

  myTone(f, 250);
  myTone(gS, 500);
  myTone(f, 350);
  myTone(a, 125);
  myTone(cH, 500);
  myTone(a, 375);
  myTone(cH, 125);
  myTone(eH, 650);

  delay(500);

  chorus();

  myTone(f, 250);
  myTone(gS, 500);
  myTone(f, 375);
  myTone(cH, 125);
  myTone(a, 500);
  myTone(f, 375);
  myTone(cH, 125);
  myTone(a, 650);

  delay(650);
}

void myTone(int freq, int duration)
{
  tone(speakerPin, freq, duration);

  if(contador % 2 == 0)
  {
    digitalWrite(output1Pin, HIGH);
    delay(duration);
    digitalWrite(output1Pin, LOW);
  }
  else
  {
    digitalWrite(output2Pin, HIGH);
    delay(duration);
    digitalWrite(output2Pin, LOW);
  }

  noTone(speakerPin);

  delay(50);

  contador++;
}

void intro()
{
  myTone(a, 500);
  myTone(a, 500);
  myTone(a, 500);
  myTone(f, 350);
  myTone(cH, 150);
  myTone(a, 500);
  myTone(f, 350);
  myTone(cH, 150);
  myTone(a, 650);

  delay(500);

  myTone(eH, 500);
  myTone(eH, 500);
  myTone(eH, 500);
  myTone(fH, 350);
  myTone(cH, 150);
  myTone(gS, 500);
  myTone(f, 350);
  myTone(cH, 150);
  myTone(a, 650);

  delay(500);
}

// Función de la segunda sección
void chorus()
{
  myTone(aH, 500);
  myTone(a, 300);
  myTone(a, 150);
  myTone(aH, 500);
  myTone(gSH, 325);
  myTone(gH, 175);
  myTone(fSH, 125);
  myTone(fH, 125);
  myTone(fSH, 250);

  delay(325);

  myTone(a, 250);
  myTone(dSH, 500);
  myTone(dH, 325);
  myTone(cSH, 175);
  myTone(cH, 125);
  myTone(b, 125);
  myTone(cH, 250);

  delay(350);
}
