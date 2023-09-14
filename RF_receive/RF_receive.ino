jk0[=#include <SPI.h>  
#include "RF24.h" 


const int ENA = 5;
const int ENB = 9;=
const int leftForward = 2;
const int leftBackward = 4;
const int rightForward = 6;
const int rightBackward = 10;

RF24 myRadio (7, 8); 
byte addresses[][6] = {"0"};

struct package
{
  byte X;
  byte Y;
  byte Z;
};

typedef struct package Package;
Package data;q 

void setup() 
{
	
	// // Turn off motors - Initial state
	// digitalWrite(IN1, LOW);
	// digitalWrite(IN2, LOW);
	// digitalWrite(IN3, LOW);
	// digitalWrite(IN4, LOW);
  
  // 	// Set all the motor control pins to outputs
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);               
  pinMode(rightBackward , OUTPUT);

  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}
void recvData()
{
  // analogWrite(ENA, 255);
	// analogWrite(ENB, 255);
  if ( myRadio.available() ) {
    myRadio.read(&data, sizeof(data));


    if (data.Y < 80) { //Reverse
  //RUN BACKWARD
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , HIGH);
  analogWrite(ENA, 255 - data.Y);
	analogWrite(ENB, 255 - data.Y);

    }

    if (data.Y > 145) {//forward

  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);
  analogWrite(ENA, data.Y);
	analogWrite(ENB, data.Y);

    }

    if (data.X > 155) {//left turn
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);
  analogWrite(ENA, data.X);
	analogWrite(ENB, data.X);
    }

    if (data.X < 80) {//RIGHT
  // digitalWrite(leftForward , LOW);
  // digitalWrite(leftBackward , HIGH);
  // digitalWrite(rightForward , HIGH);
  // digitalWrite(rightBackward , LOW);
    digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , HIGH);
  analogWrite(ENA,255 - data.X);
	analogWrite(ENB,255 - data.X);
    }

    if (data.X > 100 && data.X < 170 && data.Y > 80 && data.Y < 130) { //stop car
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , LOW);
    }
  }
}


void loop()  
{
  recvData();
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(data.Z);
  delay(500);
  

}
