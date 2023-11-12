#include <Servo.h>
Servo myServo;
int servoPin = 10;
int pushButtonPin = 2;
int closeAngle = 5;
int openedAngle = 170;
boolean isClose = true;
unsigned long time;
unsigned long reverseGgearRemovalTime;
int openStateTime = 7000;

void setup() {
  pinMode(LED_BUILTIN, HIGH);
  myServo.attach(servoPin);
  pinMode(pushButtonPin, INPUT_PULLUP);
  myServo.write(closeAngle);
 Serial.begin(9600);
 Serial.println("Hello World");
 
 }

void loop() {    
  time=millis();
  digitalWrite(LED_BUILTIN,HIGH);
//  Serial.println(time);
  if (digitalRead(pushButtonPin) == LOW){
    reverseGgearRemovalTime= time;
    Serial.println("in R");    
    Serial.println(time);    
    isClose = false;
    Serial.println("Hello World");
    myServo.write(openedAngle);
  }
  
  else if (digitalRead(pushButtonPin) == HIGH && time - reverseGgearRemovalTime > openStateTime && !isClose) {
    Serial.println("not in R ");
    Serial.println(reverseGgearRemovalTime);
    Serial.println(" World");
      myServo.write(closeAngle);
      delay(700);
      isClose = true;
    }
}
 
