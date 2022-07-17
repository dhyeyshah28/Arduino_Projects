//#include <AFMotor.h>
//#include <EEPROM.h>

#include <Servo.h>
#define IR 21
//#define rase 230

const int Switch = 14;
int Switch_state = 0;
int led_obs = 22;       //White LED
int led_blu = 23;       //Yellow LED
const int TP = A15;
const int EP = A14;
int distance;
char val;
int ang = 75;
int L;
int R;
int in1 = 2;      // Left Motor
int in2 = 3;      // Right Motor
int in3 = 4;
int in4 = 5;

Servo servo;
//AF_DCMotor motor1 (1); //Motor on Left Back
//AF_DCMotor motor2 (2); //Motor on Right Back

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  //motor1.setSpeed(rase);
  //motor2.setSpeed(rase);
  servo.attach(8);
  servo.write(75);
  pinMode(IR, INPUT);
  pinMode(TP, OUTPUT);
  pinMode(EP, INPUT);
  pinMode(Switch, INPUT_PULLUP);
  pinMode(led_obs, OUTPUT);
  pinMode(led_blu, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  if (digitalRead(Switch)==1){
    digitalWrite(13, LOW);
    digitalWrite(led_obs, HIGH);
    obstacle();
  }
  
  else if (digitalRead(Switch)==0){
    digitalWrite(13, HIGH);
    digitalWrite(led_obs, LOW);
    bluetooth();
  }
  
}

//---------Primary Functions Made Availibe to Use----------------------------------------------------------------------------------------------------------------------------------

void obstacle(){           // Obstacle Avoiding Bot Version
  
  distance = ultra_read();

  if (distance <= 15 && distance != 0){
    Serial.println(distance);
    Stop();
    move_back();
    delay(150);
    Stop();
    L = look_left();
    servo.write(ang);
    R = look_right();
    servo.write(ang);

    if(L < R){
      turn_right();
      delay(400);
      Stop();
      delay(200);
      }
    else if (L > R){
      turn_left();
      delay(400);
      Stop();
      delay(200);
      }
  }
    else {
      move_forward();
    }
  }
  
void bluetooth(){         // Bluetooth Control with Mobile RC or Voice Control. Manual Version
  
  distance = ultra_read();
  
  if (Serial1.available()>0){
    val = Serial1.read();
    Serial.println(val);

    //int stored = EEPROM.read(0)
    //Serial.println(stored)
  }
  if (distance <= 15){
        Stop();
        }
  if (val == '1'){
      move_forward();
      if (distance <= 15){
        Stop();
        }
  }
  else if(val == '2'){
        move_back();
        if (digitalRead(IR) == LOW){
          Stop();
        }
  }
  else if(val == '3'){
        turn_right();
  }
  else if(val == '4'){
        turn_left();
  }
  else if(val == '5'){
        Stop();
  }
                   
}

//---------Secondary Functions to be Used----------------------------------------------------------------------------------------------------------------------------------

int ultra_read(){
  
  digitalWrite(TP, HIGH);
  delayMicroseconds(10);
  digitalWrite(TP, LOW);
  
  long unsigned duration = pulseIn(EP, HIGH, 30000);
  distance = (duration/2)/29.1;
  return distance;
  }

int look_left(){
  servo.write(115);
  delay(600);          //IMPRO 6
  L = ultra_read();
  return L;
  }

int look_right(){
  servo.write(35);
  delay(600);          //IMPRO 7
  R = ultra_read();
  return R;
  }
  
void move_forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //motor1.run(BACKWARD);  //
  //motor2.run(FORWARD);
  }

void Stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  //motor1.run(RELEASE);
  //motor2.run(RELEASE);
  }

void move_back(){
  if (digitalRead(IR) == LOW){  //Back IR Control Usage
    Stop();
    }
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
  //motor1.run(FORWARD);     //Due to Opposite Polarity attached
  //motor2.run(BACKWARD);
  }

void turn_left(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500);
  //motor1.run(FORWARD);    //
  //motor2.run(FORWARD);
  }

void turn_right(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(500);
  //motor1.run(BACKWARD);     //Due to Opposite Polarity attached
  //motor2.run(BACKWARD);
  }
