#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
#include <LiquidCrystal.h>

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  dht.begin();
  lcd.begin(16,2);
  lcd.clear();
  analogWrite(6,100);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
}

void loop() {
  int t = dht.readTemperature();
  float h = dht.readHumidity();
  
  lcd.print("Temp: ");
  lcd.print(t);
  //lcd.print((char)176);
  lcd.print("C | ");
  lcd.print((t*(9/5))+32);
  //lcd.print((char)176);
  lcd.println("F");
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(h);
  delay(2000);
  
}
