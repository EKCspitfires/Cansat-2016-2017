#include <TinyGPS++.h>
    #include <SoftwareSerial.h>
    #include "SD.h"

    //input for the light detecting sensor (LDR)
    int LDR = A3;   

    //inputs and triggers for GPS
    TinyGPSPlus gps;
    SoftwareSerial ss (7, 8); // TX=7, RX=8 

    // digital pin 4 for the SD cs line
    const int chipSelect = 4;
    File logfile;// the logging file

    //data logger timing and other 
    #define LOG_INTERVAL  1000 // mills between entries
    #define SYNC_INTERVAL 1000 // mills between calls to flush() - to write data to the card
    uint32_t syncTime = 0; // time of last sync()
    #define ECHO_TO_SERIAL   1 // echo data to serial port
    #define WAIT_TO_START    0 // Wait for serial input in setup()    

    void setup() {
      Serial.begin(9600);
      ss.begin(9600);
      Serial.println();

      #if WAIT_TO_START
        Serial.println("Type any character to start");
        while (!Serial.available());
      #endif //WAIT_TO_START

      // initialize the SD card
      Serial.print("Initializing SD card...");

      pinMode(10, OUTPUT);

      // see if the card is present and can be initialized:
      if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        return;
      }
      Serial.println("card initialized.");

      // create a new file
      char filename[] = "LOGGER00.CSV";
      for (uint8_t i = 0; i < 100; i++) {
        filename[6] = i/10 + '0';
        filename[7] = i%10 + '0';
        if (! SD.exists(filename)) {
          // only open a new file if it doesn't exist
          logfile = SD.open(filename, FILE_WRITE); 
          break;  // leave the loop!
        }
      }

      Serial.print("Logging to: ");
      Serial.println(filename);

      logfile.println("date,time,lat,long,light");

      #if ECHO_TO_SERIAL
        Serial.println("lat,log,date,time,altitude,light");
      #endif// attempt to write out the header to the file
    }

void loop(void) {  

   // delay for the amount of time we want between readings
   delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));

   //here is GPS data (if I got it right)
   while (ss.available() > 0)
   gps.encode(ss.read());
   logfile.print(gps.date.value());
   logfile.print(", ");
   logfile.print(gps.time.value());
   logfile.print(", ");
   logfile.print(gps.location.lat(), 6);
   logfile.print(", ");
   logfile.print(gps.location.lng(), 6);
   logfile.print(", ");
   #if ECHO_TO_SERIAL
      Serial.print(gps.date.value());
      Serial.print(", ");  
      Serial.print(gps.time.value());
      Serial.print(", ");  
      Serial.print(gps.location.lat(), 6);
      Serial.print(", ");  
      Serial.print(gps.location.lng(), 6);
      Serial.print(", ");  
   #endif

   //Read light intensity
   float lux = 500/(10.72/(5-(photocellReading * 0.00488759))*(photocellReading * 0.00488759));
   logfile.println(lux);
   #if ECHO_TO_SERIAL
      Serial.println(lux);
   #endif //ECHO_TO_SERIAL

   //write data to disk
   if ((millis() - syncTime) < SYNC_INTERVAL) return;
   syncTime = millis();
   logfile.flush();
