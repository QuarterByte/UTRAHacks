// #include <Servo.h>

// Servo myservo;//create servo object to control a servo


const int trigPin = 9;
const int echoPin = 8;

float duration, distance; //store the duration and distance measured by the echo pin

void setup() {
  pinMode(trigPin, OUTPUT); // trigger Pin for left
  pinMode(echoPin, INPUT); // echo Pin for Ultrasonic

  Serial.begin(9600);
  Serial.print("Hello!");

  // //for the claws
  // myservo.attach(10);//attachs the servo on pin 9 to servo object
  // myservo.write(0);//back to 0 degrees
  // delay(1000);//wait for a second

}

void loop() {
  // put your main code here, to run repeatedly:

  //pulse starts:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //ends

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  Serial.print("Distance measured: ");
  Serial.println(distance);
	delay(100);  

  // if (distance < 10){
  //   for (int i = 0; i <= 100; i++)
  //   {
  //     myservo.write(i); //write the i angle to the servo
  //     delay(15); //delay 15ms
  //   }
  //   delay(1000);
    
  // }
  // else {
  //   for (int i = 100; i >= 0; i--)
  //   {
  //     myservo.write(i); //write the i angle to the servo
  //     delay(15); //delay 15ms
  //   }
  //   delay(1000);
  // }

}