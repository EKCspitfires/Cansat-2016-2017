int VaneValue;// raw analog value from wind vane 
int Direction;// translated 0 - 360 direction 
int CalDirection;// converted value with offset applied 
int LastValue; 

#define Offset 0; 

void setup() { 
LastValue = 1; 
Serial.begin(9600); 
Serial.println("Vane Value\tDirection\tHeading"); 
} 

voidloop() { 
VaneValue = analogRead(A4); 
Direction = map(VaneValue, 0, 1023, 0, 360); 
CalDirection = Direction + Offset; 

if(CalDirection > 360) 
CalDirection = CalDirection - 360; 

if(CalDirection < 0) 
CalDirection = CalDirection + 360; 

// Only update the display if change greater than 2 degrees. 
if(abs(CalDirection - LastValue) > 5) 
{ 
Serial.print(VaneValue); Serial.print("\t\t"); 
Serial.print(CalDirection); Serial.print("\t\t"); 
getHeading(CalDirection); 
LastValue = CalDirection; 
} 
} 

// Converts compass direction to heading 
void getHeading(int direction) { 
if(direction < 22) 
Serial.println("N"); 
else if (direction < 67) 
Serial.println("NE"); 
else if (direction < 112) 
Serial.println("E"); 
else if (direction < 157) 
Serial.println("SE"); 
else if (direction < 212) 
Serial.println("S"); 
else if (direction < 247) 
Serial.println("SW"); 
else if (direction < 292) 
Serial.println("W"); 
else if (direction < 337) 
Serial.println("NW"); 
else 
Serial.println("N"); 
}
