#include <BMP180.h>
#include <qbcan.h>
#include <RFM69.h>
#include <RFM69registers.h>


/**********************************************************
 Bosch Pressure Sensor BMP085 / BMP180 readout routine
 for the Arduino platform.
 
 Compiled by Leo Nutz
 www.ALTDuino.de              
**********************************************************/

#include <Wire.h>

#define ADDRESS_SENSOR 0x77                 // Sensor address

int16_t  ac1, ac2, ac3, b1, b2, mb, mc, md; // Store sensor PROM values from BMP180
uint16_t ac4, ac5, ac6;                     // Store sensor PROM values from BMP180
// Ultra Low Power       OSS = 0, OSD =  5ms
// Standard              OSS = 1, OSD =  8ms
// High                  OSS = 2, OSD = 14ms
// Ultra High Resolution OSS = 3, OSD = 26ms
const uint8_t oss = 3;                      // Set oversampling setting
const uint8_t osd = 26;                     // with corresponding oversampling delay

float T, P;                                 // Set global variables for temperature and pressure

void setup()
{
 Wire.begin();                             // Activate I2C
 
 Serial1.begin(9600);                       // Set up Serial1 port

 init_SENSOR();                            // Initialize baro sensor variables
 delay(100);
}

void loop()
{
 int32_t b5;

 b5 = temperature();                       // Read and calculate temperature (T)

 Serial1.print("Temperature: ");
 Serial1.print(T, 2);
 Serial1.print(" C, ");
 Serial1.print(1.8 * T + 32.0, 2);
 Serial1.println(" F");

 P = pressure(b5);                         // Read and calculate pressure (P)

 Serial1.print("Pressure: ");
 Serial1.print(P, 2);
 Serial1.print(" mbar, ");
 Serial1.print(P * 0.0295299830714, 2);
 Serial1.println(" inHg");
 Serial1.println("");

 delay(500);                               // Delay between each readout
 
}

/**********************************************
 Initialize sensor variables
**********************************************/
void init_SENSOR()
{
 ac1 = read_2_bytes(0xAA);
 ac2 = read_2_bytes(0xAC);
 ac3 = read_2_bytes(0xAE);
 ac4 = read_2_bytes(0xB0);
 ac5 = read_2_bytes(0xB2);
 ac6 = read_2_bytes(0xB4);
 b1  = read_2_bytes(0xB6);
 b2  = read_2_bytes(0xB8);
 mb  = read_2_bytes(0xBA);
 mc  = read_2_bytes(0xBC);
 md  = read_2_bytes(0xBE);

 Serial1.println("");
 Serial1.println("Sensor calibration data:");
 Serial1.print(F("AC1 = ")); Serial1.println(ac1);
 Serial1.print(F("AC2 = ")); Serial1.println(ac2);
 Serial1.print(F("AC3 = ")); Serial1.println(ac3);
 Serial1.print(F("AC4 = ")); Serial1.println(ac4);
 Serial1.print(F("AC5 = ")); Serial1.println(ac5);
 Serial1.print(F("AC6 = ")); Serial1.println(ac6);
 Serial1.print(F("B1 = "));  Serial1.println(b1);
 Serial1.print(F("B2 = "));  Serial1.println(b2);
 Serial1.print(F("MB = "));  Serial1.println(mb);
 Serial1.print(F("MC = "));  Serial1.println(mc);
 Serial1.print(F("MD = "));  Serial1.println(md);
 Serial1.println("");
}

/**********************************************
 Calcualte pressure readings
**********************************************/
float pressure(int32_t b5)
{
 int32_t x1, x2, x3, b3, b6, p, UP;
 uint32_t b4, b7;

 UP = read_pressure();                         // Read raw pressure

 b6 = b5 - 4000;
 x1 = (b2 * (b6 * b6 >> 12)) >> 11;
 x2 = ac2 * b6 >> 11;
 x3 = x1 + x2;
 b3 = (((ac1 * 4 + x3) << oss) + 2) >> 2;
 x1 = ac3 * b6 >> 13;
 x2 = (b1 * (b6 * b6 >> 12)) >> 16;
 x3 = ((x1 + x2) + 2) >> 2;
 b4 = (ac4 * (uint32_t)(x3 + 32768)) >> 15;
 b7 = ((uint32_t)UP - b3) * (50000 >> oss);
 if(b7 < 0x80000000) { p = (b7 << 1) / b4; } else { p = (b7 / b4) << 1; } // or p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
 x1 = (p >> 8) * (p >> 8);
 x1 = (x1 * 3038) >> 16;
 x2 = (-7357 * p) >> 16;
 return (p + ((x1 + x2 + 3791) >> 4)) / 100.0f; // Return pressure in mbar
}

/**********************************************
 Read uncompensated temperature
**********************************************/
int32_t temperature()
{
 int32_t x1, x2, b5, UT;

 Wire.beginTransmission(ADDRESS_SENSOR); // Start transmission to device
 Wire.write(0xf4);                       // Sends register address
 Wire.write(0x2e);                       // Write data
 Wire.endTransmission();                 // End transmission
 delay(5);                               // Datasheet suggests 4.5 ms
 
 UT = read_2_bytes(0xf6);                // Read uncompensated TEMPERATURE value

 // Calculate true temperature
 x1 = (UT - (int32_t)ac6) * (int32_t)ac5 >> 15;
 x2 = ((int32_t)mc << 11) / (x1 + (int32_t)md);
 b5 = x1 + x2;
 T  = (b5 + 8) >> 4;
 T = T / 10.0;                           // Temperature in celsius
 return b5;  
}

/**********************************************
 Read uncompensated pressure value
**********************************************/
int32_t read_pressure()
{
 int32_t value;
 Wire.beginTransmission(ADDRESS_SENSOR);   // Start transmission to device
 Wire.write(0xf4);                         // Sends register address to read from
 Wire.write(0x34 + (oss << 6));            // Write data
 Wire.endTransmission();                   // SEd transmission
 delay(osd);                               // Oversampling setting delay
 Wire.beginTransmission(ADDRESS_SENSOR);
 Wire.write(0xf6);                         // Register to read
 Wire.endTransmission();
 Wire.requestFrom(ADDRESS_SENSOR, 3);      // Request three bytes
 if(Wire.available() >= 3)
 {
   value = (((int32_t)Wire.read() << 16) | ((int32_t)Wire.read() << 8) | ((int32_t)Wire.read())) >> (8 - oss);
 }
 return value;                             // Return value
}

/**********************************************
 Read 1 byte from the BMP sensor
**********************************************/
uint8_t read_1_byte(uint8_t code)
{
 uint8_t value;
 Wire.beginTransmission(ADDRESS_SENSOR);         // Start transmission to device
 Wire.write(code);                               // Sends register address to read from
 Wire.endTransmission();                         // End transmission
 Wire.requestFrom(ADDRESS_SENSOR, 1);            // Request data for 1 byte to be read
 if(Wire.available() >= 1)
 {
   value = Wire.read();                          // Get 1 byte of data
 }
 return value;                                   // Return value
}

/**********************************************
 Read 2 bytes from the BMP sensor
**********************************************/
uint16_t read_2_bytes(uint8_t code)
{
 uint16_t value;
 Wire.beginTransmission(ADDRESS_SENSOR);         // Start transmission to device
 Wire.write(code);                               // Sends register address to read from
 Wire.endTransmission();                         // End transmission
 Wire.requestFrom(ADDRESS_SENSOR, 2);            // Request 2 bytes from device
 if(Wire.available() >= 2)
 {
   value = (Wire.read() << 8) | Wire.read();     // Get 2 bytes of data
 }
 return value;                                   // Return value
}

