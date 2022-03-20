#include <LiquidCrystal.h>
#include <DHT.h>
#include <PinChangeInt.h>
#include <string.h>
#include <avr/sleep.h>
#include "GHMFunctions.h"

#define DHT11_PIN 7
#define DHTTYPE DHT11
#define lightSensor A0
#define moisture A1
DHT dht(DHT11_PIN, DHTTYPE);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int scrollButtonPin = 8;
const int sleepButtonPin = 9;
const int powerPin = 13;


int temp;
int humidity;
int light;
String displaysString[4] = {"Temp: ","Humidity: ","Light: ","Moisture: "};
String units[4] = {"", "%","%","%"};
double values[4];
int page;
unsigned long previousRefreshTime;
unsigned long previousActionTime;
int calibrationValue;
double lightMean;
double meanIndex;

void setup(){
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);
  pinMode(scrollButtonPin, INPUT_PULLUP);
  pinMode(sleepButtonPin, INPUT_PULLUP);
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  PCintPort::attachInterrupt(scrollButtonPin, scroll, RISING);
  units[0] = (char)223;
  units[0].concat("C");
  page = 0;
  previousRefreshTime = 0;
  previousActionTime = 0;
  meanIndex = 0;
  calibration();
}

void loop(){
  if (millis()- previousRefreshTime > 3000){
    previousRefreshTime = millis();
    refresh();
  }
  lightMean += analogRead(lightSensor);
  meanIndex++;
  if (millis() - previousActionTime > 30000){
    goToSleep();
  }
}
