
/*

Project Name: Smart Home Plant Watering System
Author: Dhyey Shah
Date Modified: 17th July, 2022

*/

/*-----------------------------------------------------------------------------START OF MAIN PROGRAM------------------------------------------------------------------------------*/


// Include Libraries
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>

// Defining Variables
#define ledGreen 8
#define ledWhite 9
#define ledRed 10
#define buzzer 4
#define relay 6
#define sm_sensor A2

unsigned long prevTime_1 = 0;
unsigned long prevTime_2 = 0;

// Creating Objects for Peripherals
LiquidCrystal_I2C lcd (0x3F, 16, 2);
NewPing sonar(11, 12, 80);


/*-------------------------------------------------------------------------------------*/


void setup() {
  
  pinMode(ledGreen, OUTPUT);
  pinMode(ledWhite, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  
  pinMode(sm_sensor, INPUT);

  digitalWrite(relay, HIGH);     // Relay is Active Low Connected
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello Dhyey !");
  lcd.setCursor(0,1);
  lcd.print("Sys Status: ON");
  delay(3000);
  lcd.clear();

  Serial.begin(9600);
  //digitalWrite(ledGreen, LOW);

}

void loop() {
  
  unsigned long currTime = millis();

  unsigned int waterLevel;
  unsigned int moisture_val;

// Reading Water Level with Ultrasonic Sensor Every 30 seconds:
  if ( currTime - prevTime_1 >= 1000 ){
    
      waterLevel = readWaterLevel();
      Serial.print("Water Level Detected = ");
      Serial.print(waterLevel);
      Serial.println(" cm");

// WaterLevel Conditions:
      if (waterLevel < 10){
    
          digitalWrite(ledGreen, LOW);
          digitalWrite(ledWhite, LOW);
          digitalWrite(ledRed, HIGH);
          //digitalWrite(4, HIGH);

          lcd.setCursor(0,1);
          lcd.print("FILL UP TANK !");
    
          Serial.println("Red LED is ON");
          Serial.println("Please fill up the Tank !");
          
//          while (waterLevel < 10 && moisture_val >= 200){
//              digitalWrite(relay, HIGH);   // Active Low Relay Channel
//              digitalWrite(4, HIGH);
//              playBuzzer();
//            } 
        }
    
      else if (waterLevel >= 10 && waterLevel < 18){

          digitalWrite(4, LOW);
          digitalWrite(ledGreen, LOW);
          digitalWrite(ledWhite, HIGH);
          digitalWrite(ledRed, LOW);
    
          Serial.println("White LED is ON");
      }
    
      else if (waterLevel >= 18){

          digitalWrite(4, LOW);
          digitalWrite(ledGreen, HIGH);
          digitalWrite(ledWhite, LOW);
          digitalWrite(ledRed, LOW);
    
          Serial.println("Green LED is ON");
      }
      

      prevTime_1 = currTime;
      
  }




// Reading Soil Moisture Level with Moisture Sensor Every 1 Minute:
  if ( currTime - prevTime_2 >= 3000 ){

      moisture_val = readMoisture();
      Serial.print("Moisture Level Detected = ");
      Serial.println(moisture_val);

if (moisture_val >= 200){
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Moisture: LOW");
        lcd.setCursor(0,1);
        lcd.print("PUMP ON");
        digitalWrite(relay, LOW);
        if (waterLevel < 10){
              digitalWrite(relay, HIGH);   // Active Low Relay Channel
              playBuzzer();
          }
        
        }
  
      else if (moisture_val > 100 && moisture_val < 200){
  
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Moisture: MED");
        lcd.setCursor(0,1);
        lcd.print("PUMP OFF");
        digitalWrite(relay, HIGH);
        
        }
  
      else if (moisture_val < 100){
  
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Moisture: HIGH");
        lcd.setCursor(0,1);
        lcd.print("PUMP OFF");
        digitalWrite(relay, HIGH);
        
        } 

      prevTime_2 = currTime;
  }


}


/*----------------------------SECONDARY USER FUNCTIONS-------------------------------*/


// Reading Soil Moisture Sensor Value
int readMoisture(){
  unsigned int sensor_val = analogRead(sm_sensor);
  unsigned int sm_val = map(sensor_val, 0, 1023, 0, 255);  
  return sm_val;
}

// Reading Bucket Water Level Value
int readWaterLevel(){
  unsigned int wl_val = sonar.ping_cm(); 
  return wl_val;
}

// Playing Buzzer Sound
void playBuzzer(){
  digitalWrite(buzzer, HIGH);  
}
