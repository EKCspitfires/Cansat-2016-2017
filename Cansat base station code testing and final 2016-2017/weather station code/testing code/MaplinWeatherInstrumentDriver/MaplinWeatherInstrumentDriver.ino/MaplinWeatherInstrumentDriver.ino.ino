/**
 * Maplin Weather Instrument Driver
 */

// Speed for serial connection
#define SERIAL_BAUD 9600

// Number of half revolutions taken by wind speed sensor to calculate RPM
const uint8_t windSpeedHalfRevolutionsThreshold = 5;
// For conversion from RPM to MPH
const float windSpeedMultFactor = 0.0117439155;
// Approximate analog values for centre of each direction reading
const uint16_t windDirectionLevels[] = {930, 830, 735, 390, 75, 135, 235, 560};
// Tolerance/width of each wind direction reading
const uint16_t windDirectionTolerance = 50;
// Amount light level must have changed to be reported to serial port
//const uint16_t lightLevelThreshold = 10;

volatile bool rainFlag = false;
volatile uint16_t windSpeedHalfRevolutions = 0;
uint16_t windSpeedStartTime = 0;
uint8_t lastWindDirection = 0;
//int16_t lastLightLevel = 0;

/**
 * Setup code to configure the Arduino.
 */
void setup()
{
  // Open serial connection
  Serial.begin(SERIAL_BAUD);

  // Configure interrupt for rainfall sensor
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, rainTrigger, FALLING);

  // Configure interrupt for wind speed sensor
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, windSpeedTrigger, FALLING);

  windSpeedStartTime = millis();
}

/**
 * Main code that is called repeatedly whilst the Arduino is running.
 */
void loop()
{
  // If the client wants some data, then send the current readings
  while(Serial.available())
  {
    char c = Serial.read();
    if(c == 'D')
    {
      // Send last wind direction
      Serial.print("WIND_DIRECTION:ARB:");
      Serial.print(lastWindDirection);
      Serial.println(";");

      // Send last light level
      //Serial.print("LIGHT_LEVEL:ARB:");
      //Serial.print(lastLightLevel);
      //Serial.println(";");
    }
  }

  // If the rain sensor has been triggered
  //if(rainFlag)
  {
    // Send the serial message
    //Serial.println("RAIN_DETECT;");

    // Reset the flag for the next time it will be triggered
    rainFlag = false;
  }

  // If we have enough half revolutions to calculate the RPM
  if(windSpeedHalfRevolutions > windSpeedHalfRevolutionsThreshold)
  {
    // Calculate time taken for the half revolutions
    uint16_t deltaT = millis() - windSpeedStartTime;
    // Calculate RPM
    float windSpeedRPM = 30000.0 / ((deltaT / (float)windSpeedHalfRevolutionsThreshold));
    // Reset timer and half revolution counter
    windSpeedStartTime = millis();
    windSpeedHalfRevolutions = 0;
    float windSpeedMPH = windSpeedRPM * windSpeedMultFactor;

    // Send the serial message
    Serial.print("WIND_SPEED:MPH:");
    Serial.print(windSpeedMPH);
    Serial.println(";");
  }

  // Take a reading from the wind direction sensor
  uint16_t windDirectionReading = analogRead(0);

  // Loop through the known direction reading ranges
  int8_t windDirection = -1;
  for(int i = 0; i < 8; i++)
  {
    // Calculate the upper and lower bounds for the current measurement range
    uint16_t rangeMin = windDirectionLevels[i] - windDirectionTolerance;
    uint16_t rangeMax = windDirectionLevels[i] + windDirectionTolerance;

    // If the current reading is in the range
    if(rangeMin < windDirectionReading && rangeMax > windDirectionReading)
    {
      windDirection = i;
      break;
    }
  }

  // If the direction has changed and the new direction is known
  if(lastWindDirection != windDirection && windDirection != -1)
  {
    // Record the new direction
    lastWindDirection = windDirection;

    // Send the serial message
    Serial.print("WIND_DIRECTION:ARB:");
    Serial.print(windDirection);
    Serial.println(";");
    delay(1000);
  }

  //int16_t currentLightLevel = analogRead(1);
  //if(abs(currentLightLevel - lastLightLevel) > lightLevelThreshold)
  {
    // Record the new light level
    //lastLightLevel = currentLightLevel;

    // Send the serial message
    //Serial.print("LIGHT_LEVEL:ARB:");
    //Serial.print(currentLightLevel);
    //Serial.println(";");
  }
}

/**
 * Handler for the rainflall sensor interrupt.
 */
void rainTrigger()
{
  rainFlag = true;
}

/**
 * Handler for the wind speed sensor interrupt.
 */
void windSpeedTrigger()
{
  windSpeedHalfRevolutions++;
}
