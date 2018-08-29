#define IN1  2
#define IN2  3
#define IN3  5
#define IN4  6

int Paso [ 8 ][ 4 ] =
{ {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

int steps_left = 4095;
boolean Direction = true;
int Steps = 0;

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  while (steps_left > 0)
  {
    stepper();
    steps_left--;
    delay (1);
  }
  delay(300);
  Direction = ! Direction;
  steps_left = 4095;
}

void stepper()
{
  digitalWrite( IN1, Paso[Steps][ 0] );
  digitalWrite( IN2, Paso[Steps][ 1] );
  digitalWrite( IN3, Paso[Steps][ 2] );
  digitalWrite( IN4, Paso[Steps][ 3] );

  SetDirection();
}

void SetDirection()
{
  if (Direction)
    Steps++;
  else
    Steps--;

  Steps = ( Steps + 8 ) % 8 ;
}
