#include <Servo.h>

// Define pin numbers
int servoPin = 10;
int pushButtonPin = 2;
int closeAngle = 5;
int openedAngle = 170;
boolean isClose = true;
unsigned long time;
unsigned long reverseGearRemovalTime;
int openStateTime = 7000;

// Create a Servo object
Servo myServo;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  myServo.attach(servoPin);
  pinMode(pushButtonPin, INPUT_PULLUP);
  myServo.write(closeAngle);
}

void loop() {    
  time = millis();
  digitalWrite(LED_BUILTIN, HIGH);

  if (digitalRead(pushButtonPin) == LOW && isClose) {
    // Door is open, close it
    reverseGearRemovalTime = time;
    isClose = false;
    moveServoTo(closeAngle);
  }
  else if (digitalRead(pushButtonPin) == HIGH && !isClose && time - reverseGearRemovalTime > openStateTime) {
    // Door is closed, open it
    moveServoTo(openedAngle);
    delay(700); // Optional delay for stability
    isClose = true;
  }
}

// Function to smoothly move the servo to the target angle
void moveServoTo(int targetAngle) {
  int currentAngle = myServo.read();
  int step = (targetAngle > currentAngle) ? 1 : -1;

  for (int angle = currentAngle; angle != targetAngle; angle += step) {
    myServo.write(angle);
    delay(15); // Adjust this delay for smoother motion
  }

  myServo.write(targetAngle); // Ensure the servo reaches the target position
}
