/*
 
    
 */

#include <SD.h>

#include <DHT.h>
#include <SD.h>                      //Libraries we need
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
#include <SPI.h>

RTC_DS1307 RTC;                      // Define the Real Time Clock object
#define DHTPIN 2                     // what digital pin we're connected to
#define DHTTYPE DHT11                // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//const int chipSelect = 8;            //CS pin of your shield
File Logfile;                        //Name of the file


// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;

File dataFile;

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(SS, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1) ;
  }
  Serial.println("card initialized.");
      Serial.begin(9600); 
  Serial.println("DHTxx test!");
//SD.begin(chipSelect); 
RTC.begin();
Wire.begin();
dht.begin();

Logfile=SD.open("Logfile.csv",FILE_WRITE);                //Will open and will write once just for headers
Logfile.println("  Date           Time           Humidity           Temp");     //Print headers (not saved yet)     
Logfile.close();                                          //Print saved
  // Open up the file we're going to log to!
  dataFile = SD.open("Logfile.csv", FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    // Wait forever since we cant write data
    while (1) ;
  }
  //     following line sets the RTC to the date & time this sketch was compiled
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  
}

void loop()
{
//   float h = dht.readHumidity();                 //Read humidity
//   float t = dht.readTemperature();              //Read temperature celcius
 
DateTime now = RTC.now();                        //Clock call
 if(now.second()==0){                            //Sample every minute
  
Logfile=SD.open("Log file.csv",FILE_WRITE);       //Will open and will write date
Serial.print("File Created ");
now =RTC.now();

Logfile.print(now.year(), DEC);                //Print date and time(not saved yet)
Logfile.print("/");
Logfile.print(now.month(), DEC);
Logfile.print("/");
Logfile.print(now.day(), DEC);
Logfile.print("           ");
Logfile.print(now.hour(), DEC);
Logfile.print(":");
Logfile.print(now.minute(), DEC);
Logfile.print(":");
Logfile.print(now.second(), DEC);
Logfile.print("           ");                            //Space between data

Logfile.print("20");                               //Print humidity(not saved yet)
Logfile.print("%");                             //Print simbol
Logfile.print("           ");                            //Space between data
Logfile.print("50");                               //Print temperature
Logfile.print("°C");                            //Print simbol
Logfile.println();                               //Jump to the next line
Logfile.close();                                 //Print saved
 }
  
  // Take 1 measurement every 500 milliseconds
  delay(500);
}









