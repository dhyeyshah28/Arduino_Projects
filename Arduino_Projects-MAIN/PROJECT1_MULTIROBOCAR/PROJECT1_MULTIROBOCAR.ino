// 1) IR TESTED, AT LOW = DETECTS OBJECT, OK
// 2) INPUT LED AND FUNCTION SWITCH TESTED, O = WHITE(OBS), I = YELLOW(BLU), OK
// 3) SERVO AT 10, ANGLE AT 75 TESTED, 75 -- 115, FRONT VIEW AS OBSERVOR TO THE RIGHT OF OBS, 75 -- 35,  FRONT VIEW AS OBSERVOR TO THE LEFT OF OBS, OK
// 4) BLUETOOTH MODULE TESTED, USED ON SERIAL1, OK
// 5) ALL 4 DC MOTORS, 

#include <AFMotor.h>
#include <Servo.h>
#define IR 21 
#define rase 100
int Switch = 25;
int led_obs = 31;     //White LED
int led_blu = 26;     //Yellow LED
const int TP = A4;
const int EP = A5;
long unsigned duration = 0;
long distance;
long dist; 
char val;
int ang = 75;
int L;
int R;
Servo servo;
AF_DCMotor motor1 (1); //Motor on Right Front
AF_DCMotor motor2 (2); //Motor on Left Front
AF_DCMotor motor3 (4); //Motor on Right Back
AF_DCMotor motor4 (3); //Motor on Left Back

void setup() {
  Serial.begin(9600);
  //Serial.begin(9600);
  motor1.setSpeed(rase);
  motor2.setSpeed(rase);
  motor3.setSpeed(rase);
  motor4.setSpeed(rase);
  servo.attach(10);
  servo.write(75);
  pinMode(IR, INPUT);
  pinMode(TP, OUTPUT);
  pinMode(EP, INPUT);
  pinMode(Switch, INPUT);
  pinMode(led_obs, OUTPUT);
  pinMode(led_blu, OUTPUT);
  
}

void loop() {
  obstacle();
  }



//---------Primary Functions Made Availibe to Use----------------------------------------------------------------------------------------------------------------------------------

void obstacle() {    // Obstacle Avoiding Bot Version
  dist = ultra_read();

  if (distance <= 15){
    Serial.println(dist);
    halt();
    move_back();
    delay(150);      //IMPRO 3
    halt();
    L = look_left();
    servo.write(ang);
    R = look_right();
    servo.write(ang);
  }
    if (L < R){
      turn_right();
      delay(400);    //IMPRO 4
      halt();
      delay(200);    //IMPRO 5
      }
    else if (L > R){
      turn_left();
      delay(400);    //.
      halt();
      delay(200);    //.
      }
    
  else {
    move_forward();
    }
}

void bluetooth(){    // Bluetooth Control with Mobile RC or Voice Control. Manual Version
  dist = ultra_read();
  if (Serial.available() > 0){
    val = Serial.read();
    Serial.println(val);
    if (val == '1'){
      move_forward();
      if (dist <= 15){
        halt();
      }
      }
    else if (val == '2'){
      move_back();
      }
    else if (val == '3'){
      turn_right();
      }
    else if (val == '4'){
      turn_left();
      }
    else if (val == '5'){
      halt();
      }
    }
}

//---------Secondary Functions to be Used----------------------------------------------------------------------------------------------------------------------------------

int ultra_read() {  // Reading Distance with Ultrasonic Sensor
  digitalWrite(TP, HIGH);   //IMPRO 1
  delayMicroseconds(10);    //IMPOR 2
  digitalWrite(TP,LOW);

  duration = pulseIn(EP, HIGH, 30000);
  distance = (duration/2)/29.1;
  if (distance <= 15) {
    Serial.println(distance);
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
  motor1.run(BACKWARD);  //Due to Opposite Polarity attached
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  }  
  
void halt(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  }

void move_back(){
  if (digitalRead(IR) == LOW){  //Back IR Control Usage
    halt();
    }
  motor1.run(FORWARD);     //Due to Opposite Polarity attached
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  }

void turn_left(){
  motor1.run(BACKWARD);    //Due to Opposite Polarity attached
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  }

void turn_right(){
  motor1.run(FORWARD);     //Due to Opposite Polarity attached
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  }
