int left_move;
int right_move;

//Motor Pins
int EN_A = 9; //Enable pin for first motor
int IN1 = 13; //control pin for first motor
int IN2 = 12; //control pin for first motor
int IN3 = 11; //control pin for second motor
int IN4 = 10; //control pin for second motor
int EN_B = 8; //Enable pin for second motor
//Initializing variables to store data
int motor_speed;
int motor_speed1;

void setup ( ) {
  Serial.begin (9600); //Starting the serial communication at 9600 baud rate
  //Initializing the motor pins as output
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN_B, OUTPUT);

}

void loop () {
  left_move = 10 ; //Reading the horizontal movement value
  right_move = 0 ; //Reading the vertical movement value

  if (left_move > 0){ //Rotating the left motor in clockwise direction
    Serial.print("left turning");
    motor_speed = map(left_move, 400, 0, 0, 255); //Mapping the values to 0-255 to move the motor
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN_A, motor_speed);
  }

  else { //Motors will not move when the joystick will be at center
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  // else if (left_move > 600){ //Rotating the left motor in anticlockwise direction
  //   motor_speed = map(left_move, 600, 1023, 0, 255);
  //   digitalWrite(IN1, HIGH);
  //   digitalWrite(IN2, LOW);
  //   analogWrite(EN_A, motor_speed);
  // }

  if (right_move > 0){ //Rotating the right motor in clockwise direction
    motor_speed1 = map(right_move, 400, 0, 0, 255);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(EN_B, motor_speed1);
  }

  else {//right_move>400 && right_move <600){
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  // else if (right_move > 600){ //Rotating the right motor in anticlockwise direction
  //   motor_speed1 = map(right_move, 600, 1023, 0, 255);
  //   digitalWrite(IN3, HIGH);
  //   digitalWrite(IN4, LOW);
  //   analogWrite(EN_B, motor_speed1);
  // }
}