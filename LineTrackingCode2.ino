#include<math.h>
int left_motor_forward = 4;
int left_motor_backward = 5;
int right_motor_forward = 3;
int right_motor_backward = 2;
int ir_pins[5] = {22, 23, 24, 25, 26};
int ir[5];
int sum_of_ir;
char lastSide;

void setup() {
  int pins;
  for (pins = 0; pins < 5; pins++) {
    pinMode(ir_pins[pins], INPUT);
    Serial.begin (9600);
  }

  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);


}
  void binArray() {
    int powers_array[5];
    int number;
    int int_conversion = 0;
    for (number = 0; number<5; number++){
      ir[number] = 1 - digitalRead(number + 22);
      sum_of_ir += ir[number];
    }
  }
  void goForward(int _speed) {
    analogWrite(left_motor_forward,_speed);
    analogWrite(right_motor_forward,_speed);
    analogWrite(left_motor_backward,LOW);
    analogWrite(right_motor_backward, LOW);
  }

  void turnLeft(int _speed) {
    analogWrite(left_motor_forward, LOW);
    analogWrite(right_motor_forward, _speed);
    analogWrite(left_motor_backward, LOW);
    analogWrite(right_motor_backward, LOW);
  }

  void turnFullLeft(int _speed) {
    analogWrite(left_motor_forward, LOW);
    analogWrite(right_motor_forward, _speed);
    analogWrite(left_motor_backward, LOW);
    analogWrite(right_motor_backward, LOW);
  }

  void turnRight(int _speed) {
    analogWrite(left_motor_forward, _speed);
    analogWrite(right_motor_forward, LOW);
    analogWrite(left_motor_backward, LOW);
    analogWrite(right_motor_backward, _speed);
  }

  void turnFullRight(int _speed) {
    analogWrite(left_motor_forward, _speed);
    analogWrite(right_motor_forward, LOW);
    analogWrite(left_motor_backward, LOW);
    analogWrite(right_motor_backward, _speed);
  }

  void Stop() {
    analogWrite(left_motor_forward, LOW);
    analogWrite(right_motor_forward, LOW);
    analogWrite(left_motor_backward, LOW);
    analogWrite(right_motor_backward, LOW);
  }

  void goBack(int _speed) {
    analogWrite(left_motor_forward, LOW);
    analogWrite(right_motor_forward, LOW);
    analogWrite(left_motor_backward, _speed);
    analogWrite(right_motor_backward, _speed);
  }
  void findLine(int backward_speed, int forward_speed, int turn_speed) {
    // Ked to nebud fungovat tak skus dat delay na miesta ktore ti oznacim komentarom + a mozes ju skusit kludne este pomenit
    while(sum_of_ir == 0){
      if(lastSide == 'm'){
        analogWrite(left_motor_forward,LOW);
        analogWrite(right_motor_forward,LOW);
        analogWrite(left_motor_backward,backward_speed);
        analogWrite(right_motor_backward, backward_speed);
        //+
        turnLeft(turn_speed);
        turnRight(turn_speed);
        turnRight(turn_speed);
        turnLeft(turn_speed);
        goForward(forward_speed);
        turnLeft(turn_speed);
        turnRight(turn_speed);
        turnRight(turn_speed);
        turnLeft(turn_speed);
      }
      else if(lastSide == 'l'){
        turnLeft(turn_speed);
        turnRight(turn_speed);
        //+
        analogWrite(left_motor_forward,LOW);
        analogWrite(right_motor_forward,LOW);
        analogWrite(left_motor_backward,backward_speed);
        analogWrite(right_motor_backward, backward_speed);
        //+
        turnLeft(turn_speed);
        turnRight(turn_speed);
        turnRight(turn_speed);
        turnLeft(turn_speed);
        goForward(forward_speed);
        turnLeft(turn_speed);
        turnRight(turn_speed);
        turnRight(turn_speed);
        turnLeft(turn_speed);
      }
      else if(lastSide == 'r'){
        turnRight(turn_speed);
        turnLeft(turn_speed);
        //+
        analogWrite(left_motor_forward,LOW);
        analogWrite(right_motor_forward,LOW);
        analogWrite(left_motor_backward,backward_speed);
        analogWrite(right_motor_backward, backward_speed);
        //+
        turnLeft(turn_speed);
        turnRight(turn_speed);
        turnRight(turn_speed);
        turnLeft(turn_speed);
        goForward(forward_speed);
        turnLeft(turn_speed);
        turnRight(turn_speed);
        turnRight(turn_speed);
        turnLeft(turn_speed);
      } 
      
    }
  }

void loop() {
  int number = 0;
  binArray();

  
  for (number = 0; number<5; number++){
    Serial.print(ir[number]);
  }
  Serial.println();
  delay(500);
  // Mozes menit rychlosti ja som ich tam dal len tak odhadom
  if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0) {
      lastSide = 'm';
      while(ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
          goForward(60);
      } 
  }
  else if (ir[0] == 1 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
      lastSide = 'l';
      while (ir[0] == 1 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
        // tato funkcia dostava pohon do praveho kolesa dopredu a do laveho kolesa dozadu takze sa uplne otoci, ale ked to nebude fungovat tak to vymen za klasicke turnLeft
          turnFullLeft(60);
      }
      
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
    lastSide = 'l';
    while(ir[0] == 1 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
        turnLeft(60);
    }   
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
      lastSide = 'l';
      while(ir[0] == 0 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
          turnLeft(60);
      }
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
      lastSide = 'l';
      while(ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
          turnLeft(40);
      }
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      lastSide = 'r';
      while(ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
          turnRight(40);
      }
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 0){
      lastSide = 'r';
      while(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 0){
          turnRight(60);
      }
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 1){
      lastSide = 'r';
      while(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 1){
          turnRight(60);
      }
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 1){
      lastSide = 'r';
      while(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 1){
          // tato funkcia dostava pohon do laveho kolesa dopredu a do praveho kolesa dozadu takze sa uplne otoci, ale ked to nebude fungovat tak to vymen za klasicke turnRight
          turnFullRight(60);
      }
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
    while(ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
        goForward(60);
    } 
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
      lastSide = 'l';
      while(ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
          turnLeft(80);
      }
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
      lastSide = 'r';
      while(ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
          turnRight(80);
      }
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      lastSide = 'm';
      while(ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
          goForward(60);
      }
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      lastSide = 'l';
      while(ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
          turnFullLeft(80);
      }
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
      lastSide = 'r';
      while(ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
          turnFullRight(80);
      }
  }
  else if(sum_of_ir == 0){
    //Prvy krat to skusaj s touto funkciou goForward, ale vytvoril som funkciu findLine ktoru v tejto podmienke mozes otestovat
    goForward(60);
  }
}
