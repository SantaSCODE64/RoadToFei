#include<math.h>
const int left_motor_forward = 4;
const int left_motor_backward = 5;
const int right_motor_forward = 3;
const int right_motor_backward = 2;
int last_side_arr_size = 20;
int ir_pins[5] = {22, 23, 24, 25, 26};
int ir[5];
int sum_of_ir;
int last_states[last_side_arr_size][5];
char last_side;
int first_arr_i = 0;


void binArray() {
  int powers_array[5];
  int number;
  int int_conversion = 0;
  for (number = 0; number<5; number++){
      ir[number] = 1 - digitalRead(number + 22);
      sum_of_ir += ir[number];
  }
}

void lastStatesAdd(){
  for(int number = 0; number < 5; number++){
    last_states[first_arr_i][number] = 1 - digitalRead(number + 22);
  }
}

void goForward(int _speed) {
  analogWrite(left_motor_forward,_speed);
  analogWrite(right_motor_forward,_speed);
  analogWrite(left_motor_backward,LOW);
  analogWrite(right_motor_backward, LOW);
}

void turnLeft(int _speed, int tuning_speed) {
  analogWrite(left_motor_forward, tuning_speed);
  analogWrite(right_motor_forward, _speed);
  analogWrite(left_motor_backward, LOW);
  analogWrite(right_motor_backward, LOW);
}

void turnFullLeft(int _speed, int backward_speed) {
  analogWrite(left_motor_forward, LOW);
  analogWrite(right_motor_forward, _speed);
  analogWrite(left_motor_backward, backward_speed);
  analogWrite(right_motor_backward, LOW);
}

void turnRight(int _speed, int tuning_speed) {
  analogWrite(left_motor_forward, _speed);
  analogWrite(right_motor_forward, tuning_speed);
  analogWrite(left_motor_backward, LOW);
  analogWrite(right_motor_backward, LOW);
}

void turnFullRight(int _speed, int backward_speed) { 
  analogWrite(left_motor_forward, _speed);
  analogWrite(right_motor_forward, LOW);
  analogWrite(left_motor_backward, LOW);
  analogWrite(right_motor_backward, backward_speed);
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
        turnLeft(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnLeft(turn_speed, turn_speed/5);
        goForward(forward_speed);
        turnLeft(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnLeft(turn_speed, turn_speed/5);
      }
      else if(lastSide == 'l'){
        turnLeft(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        //+
        analogWrite(left_motor_forward,LOW);
        analogWrite(right_motor_forward,LOW);
        analogWrite(left_motor_backward,backward_speed);
        analogWrite(right_motor_backward, backward_speed);
        //+
        turnLeft(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnLeft(turn_speed, turn_speed/5);
        goForward(forward_speed);
        turnLeft(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnLeft(turn_speed, turn_speed/5);
      }
      else if(lastSide == 'r'){
        turnRight(turn_speed, turn_speed/5);
        turnLeft(turn_speed, turn_speed/5);
        //+
        analogWrite(left_motor_forward,LOW);
        analogWrite(right_motor_forward,LOW);
        analogWrite(left_motor_backward,backward_speed);
        analogWrite(right_motor_backward, backward_speed);
        //+
        turnLeft(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnLeft(turn_speed, turn_speed/5);
        goForward(forward_speed);
        turnLeft(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnRight(turn_speed, turn_speed/5);
        turnLeft(turn_speed, turn_speed/5);
      } 
      
    }
  }

void setup() {
  int pins;
  Serial.begin (9600);
  for (pins = 0; pins < 5; pins++) {
    pinMode(ir_pins[pins], INPUT);
  }

  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);

  delay(500);
}

void loop() {
  int number = 0;
  binArray();
  lastStateAdd();
  first_arr_i++;
  if(first_arr_i >= last_side_arr_size - 1){
    first_arr_i--;
    for (int element = 1; element <= first_arr_i){
        for(int number = 0; number < 5; number++){
          last_states[element - 1][number] = last_states[element][number];
        }
    }
  }
  
  for (number = 0; number<5; number++){
      Serial.print(ir[number]);
  }
  Serial.println();
  // Mozes menit rychlosti ja som ich tam dal len tak odhadom
  if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0) {
      lastSide = 'm';
      goForward(110);
  }
  else if (ir[0] == 1 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
      lastSide = 'l';
      // tato funkcia dostava pohon do praveho kolesa dopredu a do laveho kolesa dozadu takze sa uplne otoci, ale ked to nebude fungovat tak to vymen za klasicke turnLeft
      turnFullLeft(120, 20);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
    lastSide = 'l';
        turnFullLeft(120, 20); 
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
      lastSide = 'l';
          turnLeft(120, 20);
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
      lastSide = 'l';
          turnLeft(120, 20);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      lastSide = 'r';
          turnRight(120, 20);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 0){
      lastSide = 'r';
          turnRight(120, 20);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 1){
      lastSide = 'r';
          turnFullRight(120, 20);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 1){
      lastSide = 'r';
          // tato funkcia dostava pohon do laveho kolesa dopredu a do praveho kolesa dozadu takze sa uplne otoci, ale ked to nebude fungovat tak to vymen za klasicke turnRight
          turnFullRight(120, 20);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
        goForward(110);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
      lastSide = 'l';
          turnLeft(120, 20);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
      lastSide = 'r';
          turnRight(120, 20);
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      lastSide = 'm';
          goForward(110);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      lastSide = 'l';
          turnLeft(120, 20);
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
      lastSide = 'r';
          turnRight(120, 20);
  }
  else if(sum_of_ir == 0){
    //Prvy krat to skusaj s touto funkciou goForward, ale vytvoril som funkciu findLine ktoru v tejto podmienke mozes otestovat
    if(lastSide == 'l'){
      turnLeft(120, 20);
    }

    if(lastSide == 'r'){
      turnRight(120, 20);
    }

    if(lastSide == 'm'){
      goForward(110);
    }
  }
}
