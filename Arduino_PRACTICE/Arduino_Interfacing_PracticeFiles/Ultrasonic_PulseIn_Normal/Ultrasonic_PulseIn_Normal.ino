//ULTRASONIC SENSOR TUTORIAL NORMAL - PULSEIN METHOD

const int TP = A15;
const int EP = A14;

long unsigned duration = 0;
long distance;

void setup() {
  pinMode(TP, OUTPUT);
  pinMode(EP, INPUT);
  Serial.begin(9600);
  //Serial1.begin(9600);
}

void loop(){
  digitalWrite(TP, HIGH);
  delayMicroseconds(10);
  digitalWrite(TP, LOW);
  
  duration = pulseIn(EP, HIGH, 30000);
  distance = (duration/2)/29.1;
  
  if (distance <= 15 && distance != 0)
  {
    Serial.println(distance);
    //Serial1.println(distance);
    }
}
