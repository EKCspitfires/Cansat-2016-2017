
#include <MPU6050.h>
#include <BMP180.h>
#include <qbcan.h>
#include <RFM69.h>
#include <RFM69registers.h>
#include <qbcan.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <I2Cdev.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#define Author "R.Stewart" 
//Radio 
#define NODEID 2
#define NETWORKID 10
#define GATEWAYID 1 
#define ENCRYPTKEY "IhaveCreatedOverAThousandBlades" //UNLIMITED BLADE WORKS!
char payload[50];

#define OUTPUTMPU

RFM69 radio;
TinyGPSPlus gps;
SoftwareSerial ss( 9, 8 );  
BMP180 bmp; 
MPU6050 mpu (0x68); 
float N; 
float V;
float A;
int buffersize=1000;    
int acel_deadzone=8;      
int giro_deadzone=1;
int16_t ax, ay, az, gx, gy, gz;
void setup() 
{ 
 #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
delay(5000); 
pinMode (A4,INPUT);
pinMode (A5,INPUT);  
Serial.begin(9600); //Board 
Serial1.begin(115200);//Radio/Openlog 
ss.begin(9600);//GPS 
  
mpu.initialize();
 Serial.println("Testing device connections...");
    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
bmp.begin();
  {
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.setHighPower(); //To use the high power capabilities of the RFM69HW
  radio.encrypt(ENCRYPTKEY);
  Serial.println("Transmitting at 433 Mhz");
  }
    Serial.print(mpu.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(mpu.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(mpu.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(mpu.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(mpu.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(mpu.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    mpu.setXGyroOffset(-5);
    mpu.setYGyroOffset(4);
    mpu.setZGyroOffset(10);
    Serial.print(mpu.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(mpu.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(mpu.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(mpu.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(mpu.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(mpu.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    
}
void loop()
{
  int sensorV = analogRead(A4);
  float V = sensorV *(5.0/1023.0);

  double T,P;
  bmp.getData(T,P);
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  while (ss.available() > 0)
  if (gps.encode(ss.read()))

    {
  
  Serial1.print(T); 
  Serial1.print(","); 
  Serial1.print(P); 
  Serial1.print(",");
  
  Serial.print(T); 
  Serial.print(","); 
  Serial.print(P); 
  Serial.print(",");
      {
        delay(200);
        if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(F(","));
    Serial.print(gps.course.deg());
    Serial.print(F(","));
    Serial.print(gps.time.centisecond(), 6); 
    delay(50);
    Serial1.print(gps.location.lat(), 6);
    Serial1.print(F(","));
    Serial1.print(gps.location.lng(), 6);
    Serial1.print(F(","));
    Serial1.print(gps.course.deg());
    Serial1.print(F(","));
    Serial1.print(gps.time.centisecond(), 6); 
  }
  else
  {
    Serial.print(F("N/A"));
    Serial1.print(F("N/A"));
  } 
      
  Serial.print(","); 
  Serial.print(V);  
  Serial.print(",");
  Serial1.print(","); 
  Serial1.print(V);  
  Serial1.print(","); 
  }
  #ifdef OUTPUTMPU
     
        Serial.print(ax);
        Serial.print(",");
        Serial.print(ay);
        Serial.print(",");
        Serial.print(az);
        Serial.print(",");
        Serial.print(gx);
        Serial.print(",");
        Serial.print(gy);
        Serial.print(",");
        Serial.println(gz);
        delay(50);
        Serial1.print(ax);
        Serial1.print(",");
        Serial1.print(ay);
        Serial1.print(",");
        Serial1.print(az);
        Serial1.print(",");
        Serial1.print(gx);
        Serial1.print(",");
        Serial1.print(gy);
        Serial1.print(",");
        Serial1.print(gz);
    #endif
    /*
     #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial1.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial1.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial1.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
        Serial1.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
        Serial1.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
        Serial1.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif
    */
  float Lng, Lat, Deg, Tim;
  Lng = gps.location.lat();
  Lat = gps.location.lng();
  Deg = gps.course.deg();
  Tim = gps.time.centisecond();
  delay(100);
  {
  Serial.println();
  Serial1.println("Outputing RF");
  Serial1.println();
      sprintf(payload,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",(int)ax,(int)ay,(int)az,(int)gx,(int)gy,(int)gz,(int)Lng,(int)Lat,(int)Deg,(int)Tim,(int)T,(int)P,(int)V);
  Serial1.println(payload);
  radio.send(GATEWAYID, payload, 50);
  Serial1.println("Send complete");

  
  delay(100);
  }
 }
}

