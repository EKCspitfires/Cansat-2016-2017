/*
Pin Configuration
Rain Drop      A0
Soil Humidity  A1
SDA            A4
SCL            A5
DHT11 Data     D2
*/

int result [5];           //Sensor result array
#include <Wire.h>         //Including wire library
#include <SFE_BMP180.h>   //Including BMP180 library
#define ALTITUDE 3        //Altitude where I live (change this to your altitude)
SFE_BMP180 pressure;      //Creating an object
#include <DHT.h>          //Including DHT11 library
#define DHTPIN 2          //Define DHT11 digital pin
#define DHTTYPE DHT11     //Define DHT TYPE which is DHT11
DHT dht(DHTPIN, DHTTYPE); //Execute DHT11 library

void setup() {
Serial.begin(115200);       //Starting serial communication
Serial.println("Program started");
//Analog setup
pinMode(A0, INPUT);       //Soil
pinMode(A1, INPUT);       //Rain
//BMP180 Setup
if (pressure.begin())     //If initialization was successful, continue
 {Serial.println("BMP180 init success");
 Serial.print("AWS :");
 Serial.print("\t");
 Serial.print("Rain Drop\t");
 Serial.print("Soil Hum\t");
 Serial.print("Pressure \t");
 Serial.print("Air Hum\t");
 Serial.print("\t");
 Serial.println("Temp \t");}
else                       //Else, stop code forever
  {
    Serial.println("BMP180 init fail");
    while (1);
  }
  
//DHT11 setup
dht.begin(); 
}

void loop() {
//analog setup
int A_Rain = analogRead(A0);
int A_Soil = analogRead(A1); 
A_Rain = map(A_Rain, 800, 1023, 100, 0);
A_Soil = map(A_Soil, 400, 1023, 100, 0);
result[0]=A_Soil;
result[1]=A_Rain;
//bmp180 setup
char status;
double T, P, p0; 
status = pressure.startTemperature();
if (status != 0) {
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0) {
    status = pressure.startPressure(3);
      if (status != 0) {
        delay(status);
        status = pressure.getPressure(P, T);
        if (status != 0) {
          p0 = pressure.sealevel(P, ALTITUDE);
          result[2]=p0;
        }}}}
result[3] = dht.readHumidity();
result[4] = dht.readTemperature();
Serial.print("AWS : ");
Serial.print(" \t");
Serial.print(result[0]);
Serial.print(" %\t");
Serial.print("\t");
Serial.print(result[1]);
Serial.print(" %\t");
Serial.print("\t");
Serial.print(result[2]);
Serial.print(" hPa \t");
Serial.print(result[3]);
Serial.print(" %\t");
Serial.print("\t");
Serial.print(result[4]);
Serial.println("C \t");
delay(500);
}
