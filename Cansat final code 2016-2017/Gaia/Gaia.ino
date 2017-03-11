//Include the required libraries
#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>
#include <BMP180.h>

//Radio Parameters
#define NODEID        1    
#define NETWORKID     10 
#define ENCRYPTKEY    "IhaveCreatedOverAThousandBlades" 
BMP180 bmp;
//Radio object
RFM69 radio;
bool promiscuousMode = false; 

void setup()
{
 
  Serial.begin(9600);
  Serial.println("REBOOT");

  bmp.begin();
  
  delay(1000);

  //Initialize radio
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.setHighPower(); 
  radio.encrypt(ENCRYPTKEY);
  radio.promiscuous(promiscuousMode);
  Serial.println("Listening at 433 Mhz");

}


byte ackCount=0;
uint32_t packetCount = 0;
void loop()
{
 double T,P;
 bmp.getData(T,P);
  if (radio.receiveDone())
  {
    Serial.print("#[");
    Serial.print(++packetCount);
    Serial.print(']');
    Serial.print('[');Serial.print(radio.SENDERID, DEC);Serial.print("] ");
    if (promiscuousMode)
    {
      Serial.print("to [");Serial.print(radio.TARGETID, DEC);Serial.print("] ");
    }
    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");Serial.print(radio.RSSI);Serial.print("]");
    
    if (radio.ACKRequested())
    {
      byte theNodeID = radio.SENDERID;
      radio.sendACK();
      Serial.print(" - ACK sent.");

      // When a node requests an ACK, respond to the ACK
      // and also send a packet requesting an ACK (every 3rd one only)
      // This way both TX/RX NODE functions are tested on 1 end at the GATEWAY
      if (ackCount++%3==0)
      {
        Serial.print(" Pinging node ");
        Serial.print(theNodeID);
        Serial.print(" - ACK...");
        delay(3); 
        if (radio.sendWithRetry(theNodeID, "ACK TEST", 8, 0))  // 0 = only 1 attempt, no retries
          Serial.print("ok!");
        else Serial.print("nothing");
      }
    }
    Serial.println();
  }
delay(100);
Serial.print("GP:"),Serial.print(P);
Serial.print(",");
Serial.print("GT:"), Serial.print(T);
Serial.println();
}



