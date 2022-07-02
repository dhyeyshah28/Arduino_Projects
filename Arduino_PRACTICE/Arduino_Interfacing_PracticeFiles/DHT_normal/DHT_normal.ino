#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11
#include <LiquidCrystal.h>

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  dht.begin();
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  pinMode(10,OUTPUT);
  digitalWrite(9,LOW);
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.println("Dhyey is the Best");
  //Serial.print(" ");
  //Serial.println(h);
  lcd.setCursor(0,0);
  lcd.print(t);
  lcd.setCursor(0,0);
  lcd.print(h);
  delay(1000);
}
