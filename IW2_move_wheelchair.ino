#include <Arduino.h>


int speed_pwm_pin = 6;
int dir_pwm_pin = 5;

int safety_max = 150;
int safety_min = 90;

String speed_str = "121";
String direction_str = "121";
int speed = 121;
int direction = 121;


void setup(){
  // The led in the board just to inform if the arduino is running
  pinMode(13,OUTPUT);
  pinMode(speed_pwm_pin, OUTPUT);
  pinMode(dir_pwm_pin,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  
  // Escrever no serial monitor X,Y  onde X é a velocidade pretendida e Y é a direção.
  // write in the serial monitor X,Y, where X is the speed and Y the direction
  // the safe interval for both parameters is from 90 to 150 
  // the limit interval is from 87 to 153 that corresponds to 4.22V and 7.49V

  // just turns the led ON
  digitalWrite(13, HIGH);
  
  // Just put the correct voltage for the startup
  analogWrite(speed_pwm_pin, speed);
  analogWrite(dir_pwm_pin, direction);
  
  if(Serial.available()>0){
    
    speed_str  = Serial.readStringUntil(',');
    speed = speed_str.toInt();
    Serial.read(); //next character is comma, so skip it using this
    direction_str = Serial.readStringUntil('\n');
    direction = direction_str.toInt();
    
    if( speed < safety_min || speed > safety_max ){
      Serial.println("Speed value is out of range");
      speed = 121;
    }
    if( direction < safety_min || direction > safety_max ){
      Serial.println("Direction value is out of range");
      direction = 121;
    }
    
    analogWrite(speed_pwm_pin, speed);
    analogWrite(dir_pwm_pin, direction);
  }

}
