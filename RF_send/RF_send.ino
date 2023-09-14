
#include <SPI.h>  
#include "RF24.h"
#include "Wire.h"      
#include "I2Cdev.h"    
#include "MPU6050.h"

//Define variables for Gyroscope and Accelerometer data
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

struct package
{
  byte X;
  byte Y;
  byte Z;
};


typedef struct package Package;
Package data;


void setup()
{
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{

 mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255); 
  data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  delay(50);

  myRadio.write(&data, sizeof(data)); 
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
