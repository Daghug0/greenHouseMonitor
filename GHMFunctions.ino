#include <PinChangeInt.h>
#include <string.h>
#include <avr/sleep.h>
#include "GHMFunctions.h"

void displayData() {
  lcd.setCursor(0,0);
  lcd.print(displaysString[2*page]);
  lcd.print(values[2*page]);
  lcd.print(units[2*page]);
  lcd.print("                       ");
  lcd.setCursor(0, 1);
  lcd.print(displaysString[2*page+1]);
  lcd.print(values[2*page+1]);
  lcd.print(units[2*page+1]);
  lcd.print("                       ");
}

void refresh(){
  values[0] = dht.readTemperature();
  values[1] = dht.readHumidity();
  values[2] = lightMean/meanIndex;
  values[3] = map(analogRead(moisture),1023,calibrationValue,0,100);
  meanIndex = 0;
  lightMean = 0;
  displayData();
}

void scroll(){
  if ( millis() - previousActionTime > 100){
    page = !page; 
    previousActionTime = millis();
    displayData();
  }
}

void calibration(){
  calibrationValue = analogRead(moisture);
}
void goToSleep(){
  sleep_enable();
  PCintPort::attachInterrupt(sleepButtonPin, wakeUp, RISING);
  digitalWrite(powerPin, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
  digitalWrite(powerPin, HIGH);
  lcd.setCursor(0,0);
  lcd.print("waking up...                 ");
  lcd.setCursor(0,1);
  lcd.print("                             ");
}
void wakeUp(){
  sleep_disable();
  PCintPort::detachInterrupt(sleepButtonPin);
  previousActionTime = millis();
}
