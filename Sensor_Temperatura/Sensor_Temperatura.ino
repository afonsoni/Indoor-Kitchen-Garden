//Librarias
#include <OneWire.h> 
#include <DallasTemperature.h>

//Ligado ao pino 2
#define ONE_WIRE_BUS 2 

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs)    
OneWire oneWire(ONE_WIRE_BUS); 

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void) 
{
 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 
 sensors.begin(); 
} 
void loop(void) 
{ 
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE"); 
/********************************************************************/
 Serial.print("Temperature is: "); 
 Serial.print(sensors.getTempCByIndex(0)); // Porquê "byIndex"?  
   // Pode haver mais do que um DS18B20
   // 0 representa o primeiro sensor
   delay(1000); 
} 
