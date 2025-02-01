#include <Servo.h>

Servo myservo;  //create servo object to control a servo


#define trigPin = 9; //labels to identify the individual digital pins
#define echoPin = 8;
#define servoPin = 2;


float duration, distance;  //store the duration and distance measured by the echo pin

void setup() {
  pinMode(trigPin, OUTPUT);  // trigger Pin for left
  pinMode(echoPin, INPUT);   // echo Pin for Ultrasonic

  Serial.begin(9600); //open the serial monitor and print hello
  Serial.print("Hello!");

  //for the claws
  myservo.attach(servoPin);  //attachs the servo on pin 10 to servo object
  myservo.write(0);    //back to 0 degrees
  delay(1000);         //wait for a second
}

void loop() {

  //pulsing; sending ultrasonic waves out to be detected by the trigger:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //ends

  duration = pulseIn(echoPin, HIGH); //picking up the duration between sending and receiving the ultrasonic signal
  distance = (duration * .0343) / 2; //formula to convert duration into distance (cm)

  Serial.print("Distance measured: ");
  Serial.println(distance); // printing the distance
  delay(100);

  if (distance < 10) { // move the claw if the object is close according to the ultrasonic sensor
    myservo.write(0); // reset angle to 0
    delay(10);
    for (int i = 0; i <= 100; i++){ // slowly close the claws by adjusting the servo
      myservo.write(i);
     // write the i angle to the servo
        delay(15);
      //delay 15ms
    }
    delay(100); //delay just in case
  }
}
