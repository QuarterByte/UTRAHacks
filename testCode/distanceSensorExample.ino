const int trigPin = 9;
const int echoPin = 8;

float duration, distance; //store the duration and distance measured by the echo pin

void setup() {
  pinMode(trigPin, OUTPUT); // trigger Pin for left
  pinMode(echoPin, INPUT); // echo Pin for Ultrasonic

  Serial.begin(9600);
  Serial.print("Hello!");
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
}

