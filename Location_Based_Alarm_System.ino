// Project 16 - Location based alarm system.
// by VK <http://www.microcontrollershub.com>
// Created on 23 December 2019

#include <TinyGPS++.h>

TinyGPSPlus gps;                                   // The TinyGPS++ object.
#define user_defined_Lat    27.167904              // Update this value according to your requirement
#define user_defined_Lang   78.036011              // Update this value according to your requirement
#define user_defined_radius 0.003                  // Area covered around the user defined locaition, increase value to cover more area

void setup()
{
  Serial.begin(9600);                              // Start Serial communication with 9600 Baud rate.
  pinMode(13, OUTPUT);
}

void loop()
{
  while (Serial.available() > 0)                   // If data is available on Serial bus.
  {
    if (gps.encode(Serial.read()))                 // Decode GPS NMEA sentennces.
    {
      bool status = NeedToNotify();                // Check if reached the destination and Print required data.
      if (status == true)
      {
        TurnOnAlarm();                             // Trigger the alarm to notify the user
      }
      else
      {
        TurnOffAlarm();
      }
    }
  }
}
bool NeedToNotify()
{
  if (gps.location.isValid())
  {
    double lat, lng, latOffset, lngOffset;
    // Extract GPS co-ordinates
    lat = gps.location.lat();
    lng = gps.location.lng();

    // Print GPS co-ordinates on Serial monitor
    Serial.print(F("Location: ")); 
    Serial.print(lat, 5);                                       // Print Latitude.      
    Serial.print(F(","));
    Serial.print(lng, 5);                                       // Print Longitude. 
    latOffset = user_defined_Lat - lat;
    lngOffset = user_defined_Lang - lng;
    if( ((latOffset <= user_defined_radius) && (latOffset >= (user_defined_radius * -1))) && ((lngOffset <= user_defined_radius) && (lngOffset >= (user_defined_radius * -1))) )
    {
      return true;                                              // User has reached in the predefined area.
    }
  }
  else
  {
    Serial.print(F("Error in getting GPS coordinates, Please check hardware connection."));
  } 
  return false; 
}
void TurnOnAlarm()
{
  Serial.println(" \t Device is in provided location range. Turning ON the alarm");
  digitalWrite(13, HIGH);
}
void TurnOffAlarm()
{
  Serial.println(" \t Turning OFF the alarm");
  digitalWrite(13, LOW);
}
