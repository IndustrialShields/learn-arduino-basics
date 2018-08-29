int pin4 = 4;
int pin5 = 5;
int pin6 = 6;
int timer = 100;

void setup(){
  Serial.begin(9600);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
}

void loop() {
   digitalWrite(pin4, HIGH);
   Serial.println("Enciendo primer led");
   delay(timer);
   digitalWrite(pin4, LOW);
   delay(timer);

   digitalWrite(pin5, HIGH);
   Serial.println("Enciendo segundo led");
   delay(timer);
   digitalWrite(pin5, LOW);
   delay(timer);

   digitalWrite(pin6, HIGH);
   Serial.println("Enciendo tercer led");
   delay(timer);
   digitalWrite(pin6, LOW);
   delay(timer);

   digitalWrite(pin5, HIGH);
   Serial.println("Enciendo segundo led");
   delay(timer);
   digitalWrite(pin5, LOW);
   delay(timer);

   digitalWrite(pin4, HIGH);
   Serial.println("Enciendo primer led");
   delay(timer);
   digitalWrite(pin4, LOW);
   delay(timer);
}
