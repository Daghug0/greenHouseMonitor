#include <LiquidCrystal.h>
#include <DHT.h>
#include <PinChangeInt.h>;
#include <string.h>

#define DHT11_PIN 7
#define DHTTYPE DHT11
#define lightSensor A0
DHT dht(DHT11_PIN, DHTTYPE);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int buttonPin = 8;

int temp;
int humidity;
int light;
int lightPourcent;
String displaysString[4];
String units[4];
int values[4];
int page;
unsigned long previousRefreshTime;
unsigned long previousScrollTime;

void setup(){
  lcd.begin(16, 2);
  dht.begin();
  pinMode(buttonPin, INPUT_PULLUP);
  PCintPort::attachInterrupt(buttonPin, scroll, RISING);
  displaysString[0] = "Temp: ";
  displaysString[1] = "Humidity: ";
  displaysString[2] = "Light: ";
  displaysString[3] = "Moisture: ";
  units[0] = (char)223;
  units[0].concat("C");
  units[1] = "%";
  units[2] = "%";
  units[3] = "%";
  page = 0;
  previousRefreshTime = 0;
  previousScrollTime = 0;
}

void loop(){
  if ( millis()- previousRefreshTime > 1000){
    previousRefreshTime = millis();
    refresh();
  }
}

void refresh(){
 values[0] = dht.readTemperature();
 values[1] = dht.readHumidity();
 values[2] = analogRead(lightSensor);
 values[3] = 0;
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

void scroll(){
  if ( millis() - previousScrollTime > 100){
    page = !page; 
    previousScrollTime = millis();
  }
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
