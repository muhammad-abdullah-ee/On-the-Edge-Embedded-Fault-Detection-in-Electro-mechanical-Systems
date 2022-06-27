#include <Wire.h>
#include <MPU6050.h>
#include <dht.h>
#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 7);

String str;
dht DHT;

#define DHT11_PIN 6
const int currentPin = A0;
int sensitivity = 185;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;
double volt = 0;

MPU6050 mpu;

void setup() 
{
  Serial.begin(115200);
  espSerial.begin(115200);
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // If you want, you can set gyroscope offsets
  // mpu.setGyroOffsetX(155);
  // mpu.setGyroOffsetY(15);
  // mpu.setGyroOffsetZ(15);
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  // mpu.setThreshold(3);
  
 
}


void loop()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  volt = adcVoltage/500;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  currentValue = abs(currentValue) * 10;
int chk = DHT.read11(DHT11_PIN);

 // Serial.print(" Xnorm = ");
 /* Serial.print(normGyro.XAxis);
 Serial.print(",");
  Serial.print(normGyro.YAxis);
 Serial.print(",");
  Serial.print(normGyro.ZAxis);
   Serial.print(",");
  //Serial.print(volt,5);
  
 
  //Serial.print(",");
  Serial.print(currentValue);
  
  Serial.print(",");
  Serial.println(DHT.temperature);*/
  str =String(normGyro.XAxis)+String(",")+String(normGyro.YAxis)+String(",")+String(normGyro.ZAxis)+String(",")+String(volt)+String(",")+String(currentValue)+String(",")+String(DHT.temperature);
espSerial.println(str);
Serial.println(str);
  delay(250);
}
