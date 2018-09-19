//-----------------------------------------//
//  Created by I Putu Adi Prahasta Giri.   //
//  Email: adiprahastagiri18@gmail.com     //
//  Please consider credit and contribute. //
//  Share with your friend                 //
//  Cheers!                                //
//-----------------------------------------//

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

#include <Servo.h>
Servo servoFeed; 

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int relayPin = 8;

void setup () {

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(9600);
  servoFeed.attach (9);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
  //==========================//
  //          FEEDER          //
  //==========================//
  if (now.hour()==7&&now.minute()==55&&now.second()==0){ 
    //Morning
    servoFeed.write(180);
    delay(1000);
    servoFeed.write(0);
  }else if(now.hour()==11&&now.minute()==55&&now.second()==0){
    //Noon
    servoFeed.write(180);
    delay(1000);
    servoFeed.write(0);
  }else if(now.hour()==15&&now.minute()==55&&now.second()==0){
    //Night
  servoFeed.write(180);
    delay(1000);
    servoFeed.write(0);
  };
  //==========================//
  //          LAMP            //
  //==========================//
  if((now.hour()>=8)&&(now.hour()<=17)){
  digitalWrite(relayPin, LOW);
  }else{
    digitalWrite(relayPin, HIGH);
  };
}
