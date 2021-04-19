#include <SoftwareSerial.h>
#include <Servo.h>      // servo class

char data;              // coming bluetooth data
char data2 = '0';       // while-in data
byte speet = 0;         // speed (0-100%)
int pwm = 6;            // dc motor pwm pin
int signal1 = 2;        // dc motor directions pins
int signal2 = 7;        // dc motor directions pins
byte ledf = 8;          // front lights pin
byte ledr = 4;          // rear lights pin
byte spin = 3;          // servomech pin
Servo servo;            // create servo object     
int wheelsleft = 0;     // servo left
int wheelsright = 180;  // servo right
int neutral = 90;       // servo centre

void setup() 
{
  Serial.begin(9600);         // set serial port rate, pins as output
  pinMode(pwm, OUTPUT);
  pinMode(signal1, OUTPUT);
  pinMode(signal2, OUTPUT);
  pinMode(ledf, OUTPUT);
  pinMode(ledr, OUTPUT);
  servo.attach(spin);         // set pin 3 as servo
}

void loop() 
{
  if (Serial.available() > 0)         // if connection available
    data = Serial.read();

    switch(data){                     // car speed control 
      case '0': speet = 0; break;
      case '1': speet = 25; break;
      case '2': speet = 50; break;
      case '3': speet = 75; break;
      case '4': speet = 100; break;
      case '5': speet = 125; break;
      case '6': speet = 150; break;
      case '7': speet = 175; break;
      case '8': speet = 200; break;
      case '9': speet = 225; break;
      case 'q': speet = 250; break;
      default: break;
    }
    
    if(data == 'W')frontOn();                   // front lights on
    if(data == 'w')frontOff();                  // front lights off 
    if(data == 'U')rearOn();                    // rear lights on
    if(data == 'u')rearOff();                   // rear lights off
    if(data == 'X')                             // X - start blinking
     while(data2 != 'x')                        // x - stop blinking
      {
        blinkingOn(); 
        data2 = Serial.read();
      }           
    if(data == 'L')turnLeft();                  // wheels left
    if(data == 'R')turnRight();                 // wheels right
    if(data == 'F')forward(speet);              // go forward       //if(data != 'L' and data != 'R')servo.write(neutral);   stopp fction do this
    if(data == 'B')back(speet);                 // go backward
    if(data == 'G')
    {
      turnLeft();
      forward(speet);
    }
    if(data == 'I')
    {
      turnRight();
      forward(speet);
    }
    if(data == 'H')
    {
      turnLeft();
      back(speet);
    }
    if(data == 'J')
    {
      turnRight();
      back(speet);
    }
    if(data == 'S')stopp();
    
    data2 = '0';
}
////////////////////////////////////////////////////////////////

void frontOn()
{
  digitalWrite(ledf, HIGH); // 1 front lights pin
}

void frontOff()
{
  digitalWrite(ledf, LOW);  // 0 front lights pin
}

void rearOn()
{
  digitalWrite(ledr, HIGH); // 1 rear lights pin
}

void rearOff()
{
  digitalWrite(ledr, LOW);  // 0 rear lights pin
}

void blinkingOn()
{
  digitalWrite(ledr,HIGH);
  digitalWrite(ledf,HIGH);
  delay(250);
  digitalWrite(ledr,LOW);
  digitalWrite(ledf,LOW);
  delay(500);
}

void turnLeft()
{
  servo.write(wheelsleft);  // set servo position to left
}

void turnRight()
{
  servo.write(wheelsright); // set servo position to right
}

void forward(byte speet)
{
  digitalWrite (signal1, LOW);    // go forward
  digitalWrite (signal2, HIGH);
  analogWrite (pwm, speet);       // set pwm signal to motor
}

void back(byte speet)
{
  digitalWrite (signal1, HIGH);   // go backward
  digitalWrite (signal2, LOW);
  analogWrite(pwm, speet);        // set pwm signal to motor
}

void stopp()                      // set everything to neutral/stop all
{
  digitalWrite (signal1, LOW);
  digitalWrite (signal2, LOW);
  servo.write(neutral);
}
