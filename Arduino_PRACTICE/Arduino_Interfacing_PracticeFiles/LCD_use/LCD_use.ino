#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

byte Heart[8] = {
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000,
0b00000
};

void setup() {
  analogWrite(6,100);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  lcd.begin(16,2);
  lcd.clear();
  lcd.createChar(0, Heart);
}

void loop() {
  lcd.setCursor(3,0);
  lcd.print("Dhyey Shah");

  lcd.setCursor(3,1);
  lcd.print("LCD Works!");
  lcd.blink();
  lcd.setCursor(13, 0);
  lcd.write(byte(0));

  
}
