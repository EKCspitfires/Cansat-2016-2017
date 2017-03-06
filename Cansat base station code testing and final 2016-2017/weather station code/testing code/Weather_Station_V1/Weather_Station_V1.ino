//Libraries and declarations
int result [5];           
#include <Wire.h>         
#include <SFE_BMP180.h>   
#define ALTITUDE 9        
SFE_BMP180 pressure;      
#include <DHT.h>          
#define DHTPIN 2          
#define DHTTYPE DHT22     
DHT dht(DHTPIN, DHTTYPE); 

// Wind senor values
const uint8_t windSpeedHalfRevolutionsThreshold = 5;
const float windSpeedMultFactor = 0.0117439155;
const uint16_t windDirectionLevels[] = {930, 830, 735, 390, 75, 135, 235, 560};
const uint16_t windDirectionTolerance = 50;
volatile uint16_t windSpeedHalfRevolutions = 0;
uint16_t windSpeedStartTime = 0;
uint8_t lastWindDirection = 0;

void setup()
{
  Serial.begin(115200);

  // Configure interrupt for wind speed sensor
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, windSpeedTrigger, FALLING);

  windSpeedStartTime = millis();

Serial.println("Program started");
//BMP180 & DHT22 Setup
if (pressure.begin())     
 {delay(500);
 Serial.println("Program Initialisation Success");
 Serial.println("");
 Serial.print("Weather Station :");
 Serial.print("\t");
 Serial.print("Pressure\t");
 Serial.print("Air Hum\t");
 Serial.print("\t");
 Serial.print("Temp \t");
 Serial.println("");}
else                       
  {
    Serial.println("Program Initialisation Fail");
    while (1);
  }
  

dht.begin(); 
}

void loop()
{
  // Wind sensor loop
  while(Serial.available())
  {
    char c = Serial.read();
    if(c == 'D')
    {
      Serial.print("Weather Station : Wind Direction : ");
      Serial.print(lastWindDirection);
      Serial.println(" ");
    }
  }
  

  if(windSpeedHalfRevolutions > windSpeedHalfRevolutionsThreshold)
  {
    uint16_t deltaT = millis() - windSpeedStartTime;
    float windSpeedRPM = 30000.0 / ((deltaT / (float)windSpeedHalfRevolutionsThreshold));
    windSpeedStartTime = millis();
    windSpeedHalfRevolutions = 0;
    float windSpeedMPH = windSpeedRPM * windSpeedMultFactor;

    Serial.print("Weather Station : Wind Speed : ");
    Serial.print(windSpeedMPH);
    Serial.println(" ");
  }

  uint16_t windDirectionReading = analogRead(0);

  int8_t windDirection = -1;
  for(int i = 0; i < 8; i++)
  {
    uint16_t rangeMin = windDirectionLevels[i] - windDirectionTolerance;
    uint16_t rangeMax = windDirectionLevels[i] + windDirectionTolerance;

    // If the current reading is in the range
    if(rangeMin < windDirectionReading && rangeMax > windDirectionReading)
    {
      windDirection = i;
      break;
    }
  }
  if(lastWindDirection != windDirection && windDirection != -1)
  {
    lastWindDirection = windDirection;

    Serial.print("Weather Station : Wind Direction : ");
    Serial.print(windDirection);
    Serial.println(" ");
    delay(1000);
  }



// BMP180 & DHT22 loop
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
Serial.print("Weather Station : ");
Serial.print(" \t");
Serial.print(result[2]);
Serial.print(" hPa \t");
Serial.print(result[3]);
Serial.print(" %\t");
Serial.print("\t");
Serial.print(result[4]);
Serial.println("C \t");
delay(1000);
}

// Defining the wind speed trigger
void windSpeedTrigger()
{
  windSpeedHalfRevolutions++;
}






