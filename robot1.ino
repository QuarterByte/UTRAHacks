// Motor A connections
int enA = 9;
int in1 = 13;
int in2 = 12;
// Motor B connections
int enB = 8;
int in3 = 11;
int in4 = 10;

//Ultrasonic sensors 
const int trigPin = 0;
const int echoPin = 1;
#define OE_PIN A5

float duration, distance; //store the duration and distance measured by the echo pin
//millis(): returns the value of the current time: call millis before and after a function that you want to measure.
//stopwatch(): 

//COLOUR SENSOR 
// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 3

// Calibration Values
// *Get these from Calibration Sketch
const int redMin = 70; // Red minimum value
const int redMax = 1400; // Red maximum value
const int greenMin = 70; // Green minimum value
const int greenMax = 1400; // Green maximum value
const int blueMin = 50; // Blue minimum value
const int blueMax = 1300; // Blue maximum value


// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;


int colour; 
int speed_motor = 100;

void setup() {
	pinMode(OE_PIN,OUTPUT);
  digitalWrite(OE_PIN, LOW);
  
  // Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

  //Ultrasonic Sensor 
  pinMode(trigPin, OUTPUT); // trigger Pin for left
  pinMode(echoPin, INPUT); // echo Pin for Ultrasonic

  //Colour sensor 
  // Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Pulse Width scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

  // Setup Serial Monitor
	Serial.begin(9600);

}




void loop() {
	
  //calculate distance
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

  //when hit wall (25cm)
  if (distance < 30){
    Serial.println("Hit wall");
    
    stop();

    checkcolour(); 

    if (colour == 1) { //if colour == black 
      Serial.println("resetting");
      delay(5000);
    }
    else if (colour == 2){ //red 
      turnU();
      delay(4000);
    }
    else if (colour == 3){ //blue 
      turnleft();
      delay(4000);
    }
    else if (colour == 4){ //green 
      turnright(); 
      delay(4000);
    }
    //hopefully never
    else {
      Serial.println("WAIT WHY AM I HERE");
      stop(); 
    }

  }
  else {
    Serial.println("going straight");
    gostraight();
    delay(100);
  }
  
}

void checkcolour(){
  // Read Red Pulse Width
	redPW = getRedPW();
	// Delay to stabilize sensor
	delay(200);

	// Read Green Pulse Width
	greenPW = getGreenPW();
	// Delay to stabilize sensor
	delay(200);

	// Read Blue Pulse Width
	bluePW = getBluePW();
	// Delay to stabilize sensor
	delay(200);

	// Print output to Serial Monitor
	Serial.print("Red PW = ");
	Serial.print(redPW);
	Serial.print(" - Green PW = ");
	Serial.print(greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(bluePW);

  if (redPW > 500 && bluePW > 500 && greenPW > 500){
    Serial.println("black"); 
    colour = 1; 
  }
  else if (redPW < bluePW && redPW < greenPW){
    Serial.println("red"); 
    colour = 2;
  }
  else if (bluePW < redPW && bluePW < greenPW){
    Serial.println("blue"); 
    colour = 3; 
  }
  else if (greenPW < redPW && greenPW < bluePW){
    Serial.println("green"); 
    colour = 4; 
  }

  else{
    colour = 5; //edge case something's wrong
  }

}

void stop(){
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void gostraight() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enA, speed_motor);
	analogWrite(enB, speed_motor);

	// Turn on motor A & B
  //right motor
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
  //left motor 
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2000);
	
}

void turnleft() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enA, speed_motor);
	analogWrite(enB, speed_motor);


  // Turn on motor A & B
  //right motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //left motor 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(5000);
	
	
}

void turnright() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enA, speed_motor);
	analogWrite(enB, speed_motor);

  // Turn on motor A & B
  //right motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //left motor 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(5000);
	
}

void turnU() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enA, speed_motor);
	analogWrite(enB, speed_motor);

  // Turn on motor A & B
  //right motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //left motor 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(5000);

	
}




// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}