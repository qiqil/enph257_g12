//Encoder Based Movements
const int eKd = 15; //8
const int eKp = 10;
const int eKi = 30;
const int integralLimit = 60;
const int stepSize = 1;
const int MAX_SPEED = 255;

void stopMotors (){
  motor.speed(0, 0);
  motor.speed(1, 0);
}

void driveStraight(unsigned long distance, int speed){
  int prevControl = 0;
  int control= 0;
  int devCount = 0;
  int integralControl = 0;

  resetRotations();
  
  while(left_rotations < distance || right_rotations < distance) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print(left_rotations);
    LCD.setCursor(7, 0); LCD.print(speed-control);
    LCD.setCursor(0, 1); LCD.print(right_rotations);
    LCD.setCursor(7, 1); LCD.print(speed+control);

//    //trouble shooting POS
//    char buffer [100];
//    int output = sprintf(buffer, "Control is: %d, Integral is : %d", control, I);
//    for(int i = 0; i <= output; i++){
//      Serial.print(buffer[i]);
//    }
    Serial.println(integralControl);
 
    control = 0;
    if (left_rotations > right_rotations + stepSize) {
      control = eKi;
//      if (abs(control) >= abs(prevControl)) {integralControl++;}
    } else if (left_rotations < right_rotations - stepSize) {
      control = -eKi;
//      if(abs(control) >= abs(prevControl)) {integralControl--;} 
    }
//
//    if(abs(integralControl) >= integralLimit) {integralControl = integralLimit * integralControl/abs(integralControl);}
//    
//    if (control == prevControl){devCount = 1;}
//    else {devCount++;}
//    
////posterity, incorrect config, donot delete
////    motor.speed(0, speed - control);
////    motor.speed(1, speed + control);

    control += devCount * eKd;
    motor.speed(0, speed + control); // right motor 
    motor.speed(1, speed - control); // left motor

    prevControl = control;
  }

  stopMotors();
}

void reverse(unsigned long distance, int speed){
  
}

void brake(){
  
}

//left wheel = 0, right wheel = 1
//+ angle is CW
void rotate(int angle){
  resetRotations();
  
  if (angle == 0) return;

  int revCountMax = angle/3 + 0.5;
  revCountMax = abs(revCountMax);
  
  LCD.clear(); LCD.home();
  LCD.print(revCountMax);
  if (angle > 0) {
    while(abs(left_rotations) <= revCountMax || abs(right_rotations) <= revCountMax){
      moveRightMotor(-MAX_SPEED);
      moveLeftMotor(MAX_SPEED);
    }
  }

  if (angle < 0) {
    while(abs(left_rotations) <= revCountMax || abs(right_rotations) <= revCountMax){
      moveRightMotor(MAX_SPEED);
      moveLeftMotor(-MAX_SPEED);
    }
  }
  
  stopMotors();
}

void resetRotations(){
  left_rotations = 0;
  right_rotations = 0;
}

void moveRightMotor(int speed){
  motor.speed(0, speed);
}

void moveLeftMotor(int speed){
  motor.speed(1, speed);
}
