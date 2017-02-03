#include <TinyGPS++.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <BMP180.h>
#include <qbcan.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

 int16_t ax, ay, az;
int16_t gx, gy, gz;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

#define LED_PIN 13
bool blinkState = false;
//Create software serial object to communicate with GPS
SoftwareSerial gps( 9 , 8 );



void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
//Serial.begin(9600);
  //while(!Serial);
  Serial1.begin(9600);
  while(!Serial1);
  
  Serial1.println("Setup Complete!");
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
   //Being serial communication witj Arduino and GPS Module //Important rate must be 9600
  gps.begin(9600);
  delay(1000);
   
     Serial1.println("Initializing I2C devices...");
    accelgyro.initialize();

  
    Serial1.println("Testing device connections...");
    Serial1.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


    // use the code below to change accel/gyro offset values
    /*
    Serial.println("Updating internal sensor offsets...");
    // -76  -2359 1688  0 0 0
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    accelgyro.setXGyroOffset(220);
    accelgyro.setYGyroOffset(76);
    accelgyro.setZGyroOffset(-85);
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    */

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

 
void loop() {
  //Read SIM800 output (if available) and print it in Arduino IDE Serial Monitor
  if(gps.available()){
    
    Serial1.write(gps.read());

     #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
         Serial1.print("a/g:\t");
        Serial1.print(ax); Serial1.print("\t");
        Serial1.print(ay); Serial1.print("\t");
        Serial1.print(az); Serial1.print("\t");
        Serial1.print(gx); Serial1.print("\t");
        Serial1.print(gy); Serial1.print("\t");
        Serial1.println(gz);
        #endif
        
       #ifdef OUTPUT_BINARY_ACCELGYRO
          Serial1.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial1.write((uint8_t)(ay >> 8)); Serial1.write((uint8_t)(ay & 0xFF));
        Serial1.write((uint8_t)(az >> 8)); Serial1.write((uint8_t)(az & 0xFF));
        Serial1.write((uint8_t)(gx >> 8)); Serial1.write((uint8_t)(gx & 0xFF));
        Serial1.write((uint8_t)(gy >> 8)); Serial1.write((uint8_t)(gy & 0xFF));
        Serial1.write((uint8_t)(gz >> 8)); Serial1.write((uint8_t)(gz & 0xFF));
        #endif

        // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800
  
  if(Serial1.available()){    
  gps.write(Serial1.read());
  delay(500);
 }
  }
