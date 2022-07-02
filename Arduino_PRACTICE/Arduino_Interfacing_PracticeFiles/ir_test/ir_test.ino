
int tracking_sensor_pin =2;
void setup() 
{    
  pinMode(tracking_sensor_pin , INPUT);            
  Serial.begin(9600);
}

void loop() {
  int x = digitalRead(tracking_sensor_pin);//reading Sensor signal pin
  if(x == 1){
   Serial.println("BLACK");
   delay(200);  
  }
  else if(x == 0){
   Serial.println("WHITE"); 
   delay(200);
  }
}
