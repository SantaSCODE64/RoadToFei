#include<math.h>
const int left_motor_forward = 4;
const int left_motor_backward = 5;
const int right_motor_forward = 3;
const int right_motor_backward = 2;
const int diff_arr_size = 19;
int ir_pins[5] = {22, 23, 24, 25, 26};
int ir[5];
int sum_of_ir;
char last_side;
int first_arr_i = 0;
int backward_speed = 80;
int turning_speed = 140;
int forward_speed = 100;
int circle_turning_speed = 80;
int circle_forward_speed = 80;
int forward_turn_speed = 40;
int same_states_number = 0;
int ir_sum;
int same_states_numbers_arr[diff_arr_size];
int powers_arr[5];
int diff_arr_i = 0;
int diff_states_arr[diff_arr_size][5];
int last_states_arr[5];
int before1_last_states_arr[5];
int before2_last_states_arr[5];
int before3_last_states_arr[5];
int before4_last_states_arr[5];
bool is_different = false;
bool isOnCircle = false;

void binArray() {
  int powers_array[5];
  int number;
  int int_conversion = 0;
  for (number = 0; number<5; number++){
      ir[number] = 1 - digitalRead(number + 22);
      sum_of_ir += ir[number];
  }
}

void powersArr(){
  for(int pos = 0; pos < 5; pos++){
    if(pos == 0){
       powers_arr[pos] = pow(2, pos+1);
    }
    if(pos != 0){
       powers_arr[pos] = pow(2, pos+1) + 1;
    }
  }
}

int multOfArrays(int array01[5], int array02[5]){
  int arraysNum = 0;
  for(int num = 0; num < 5; num++){
      arraysNum += array01[num] * array02[num];
  }
  return arraysNum;
}


void goForward(int _speed) {
  analogWrite(left_motor_forward,_speed);
  analogWrite(right_motor_forward,_speed);
  analogWrite(left_motor_backward,LOW);
  analogWrite(right_motor_backward, LOW);
}

void goLeftForward(int _speed, int turn_speed){
  analogWrite(left_motor_forward,_speed);
  analogWrite(right_motor_forward,_speed + turn_speed);
  analogWrite(left_motor_backward,LOW);
  analogWrite(right_motor_backward, LOW);
}

void goRightForward(int _speed, int turn_speed){
  analogWrite(left_motor_forward,_speed + turn_speed);
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
      if(last_side == 'm'){
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
      else if(last_side == 'l'){
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        analogWrite(left_motor_forward,LOW);
        analogWrite(right_motor_forward,LOW);
        analogWrite(left_motor_backward,backward_speed);
        analogWrite(right_motor_backward, backward_speed);
        delay(2000);
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
        goForward(forward_speed);
        delay(2000);
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
      }
      else if(last_side == 'r'){
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
        //+
        analogWrite(left_motor_forward,LOW);
        delay(2000);
        analogWrite(right_motor_forward,LOW);
        delay(2000);
        analogWrite(left_motor_backward,backward_speed);
        delay(2000);
        analogWrite(right_motor_backward, backward_speed);
        delay(2000);
        //+
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
        goForward(forward_speed);
        delay(2000);
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnRight(turn_speed, turn_speed/5);
        delay(2000);
        turnLeft(turn_speed, turn_speed/5);
        delay(2000);
      } 
      
    }
  }



void setup() {
  int pins;
  powersArr();
  Serial.begin (9600);
  for (pins = 0; pins < 5; pins++) {
    pinMode(ir_pins[pins], INPUT);
  }

  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);

  for(int n = 0; n<=diff_arr_size; n++){
    same_states_numbers_arr[n] = 0;
  }

  delay(500);
}

void loop() {
  binArray();
  
  if(diff_arr_i >= diff_arr_size){
    diff_arr_i--;
    for (int element = 1; element <= diff_arr_size; element++){
        same_states_numbers_arr[element - 1] = same_states_numbers_arr[element];
        for(int number = 0; number < 5; number++){
          diff_states_arr[element - 1][number] = diff_states_arr[element][number];
        }
    }
  }
  
  if(diff_arr_i == 0){
    is_different = true;             
  }
  else if(diff_arr_i > 0){
    for(int num = 0; num < 5; num++){
      if(diff_states_arr[diff_arr_i - 1][num] != ir[num]){
        is_different = true;                
      }
    }
  }  
  
  for(int num04 = 0; num04 < 5; num04++){
    last_states_arr[num04] = diff_states_arr[diff_arr_i - 1][num04];
  }

  for(int num05 = 0; num05 < 5; num05++){
    before1_last_states_arr[num05] = diff_states_arr[diff_arr_i - 2][num05];
  }
  
  for(int num06 = 0; num06 < 5; num06++){
    before2_last_states_arr[num06] = diff_states_arr[diff_arr_i - 3][num06];
  }

   for(int num07 = 0; num07 < 5; num07++){
      before3_last_states_arr[num07] = diff_states_arr[diff_arr_i - 4][num07];
   }

   for(int num08 = 0; num08 < 5; num08++){
      before4_last_states_arr[num08] = diff_states_arr[diff_arr_i - 5][num08];
   }


  if(is_different == false){
    same_states_number++;
    same_states_numbers_arr[diff_arr_i] = same_states_number;
  }

  if(is_different){
    same_states_number = 0;
    for(int first_e = 0; first_e < 5; first_e++){
      diff_states_arr[diff_arr_i][first_e] = ir[first_e];
    }
    diff_arr_i++;
    is_different = false;            
  }

 

  int arr_num = multOfArrays(last_states_arr, powers_arr);
  int arr_num_before1 = multOfArrays(before1_last_states_arr, powers_arr);
  int arr_num_berfore2 = multOfArrays(before2_last_states_arr, powers_arr);
  int arr_num_berfore3 = multOfArrays(before2_last_states_arr, powers_arr);
  int arr_num_berfore4 = multOfArrays(before2_last_states_arr, powers_arr);
  
  for(int ch00 = 0; ch00 < 5; ch00++){
      Serial.print(last_states_arr[ch00]);
  }
  Serial.println();
  for(int ch01 = 0; ch01 < 5; ch01++){
      Serial.print(before1_last_states_arr[ch01]);
  }
  Serial.println();
  for(int ch02 = 0; ch02 < 5; ch02++){
      Serial.print(before2_last_states_arr[ch02]);
  }
  Serial.println();
  Serial.print(same_states_numbers_arr[diff_arr_i]);
  Serial.println();

  Serial.print(arr_num);
  Serial.println();
  
  
  
  if(arr_num == 62 && same_states_numbers_arr[diff_arr_i] >= 6){
    isOnCircle = true;
    forward_speed = circle_forward_speed;
    turning_speed = circle_turning_speed;
    while(isOnCircle){
      binArray();
      if((ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1 && ir[0] != 1)){
        goForward(forward_speed);
      }
      if(ir[0] == 0 && ir[1] == 0 && ir[2] == 0){
        while(ir[0] != 0 && ir[1] != 0 && ir[2] != 0 && ir[3] != 0 && ir[4] != 0){
          binArray();
          goForward(forward_speed);
        }
        while(ir[1] != 1){
          binArray();
          turnFullRight(turning_speed + 40, backward_speed);
        }
        while(isOnCircle){
          binArray();
          if(ir[0] == 1){
            turnFullLeft(turning_speed, backward_speed);
            delay(100);
            while(ir[0] == 1){
              binArray();
              turnFullLeft(turning_speed + 80, backward_speed);
            }        
            isOnCircle = false;
            forward_speed = 100;
            turning_speed = 140;
          }
          if(ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
            goForward(forward_speed);
          }
          else if(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 1){
            turnFullRight(turning_speed + 20, backward_speed);
          }
          else if(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 1){
            turnFullRight(turning_speed + 20, backward_speed);
          }
          else if(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
            turnFullRight(turning_speed + 20, backward_speed);
          }
          else if(ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
            turnFullLeft(turning_speed, backward_speed);
          }
          for(int ch04 = 0; ch04 < 5; ch04++){
            Serial.print(ir[ch04]);
          } 
          Serial.println();

        }
      }
      
      if(ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
        while(ir[0] != 0 && ir[1] != 0 && ir[2] != 0 && ir[3] != 0 && ir[4] != 0){
          binArray();
          goForward(forward_speed);
        }
        while(ir[3] != 1){
          binArray();
          turnFullLeft(turning_speed + 40, backward_speed);
        }
        while(isOnCircle){
          binArray();
          if(ir[4] == 1){
            turnFullRight(turning_speed, backward_speed);
            delay(100);
            while(ir[4] == 1){
              binArray();
              turnFullRight(turning_speed + 80, backward_speed);
            }
            isOnCircle = false;
            forward_speed = 100;
            turning_speed = 140;
          }
          if(ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
            goForward(forward_speed);
          }
          else if(ir[0] == 1 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
            turnFullLeft(turning_speed + 20, backward_speed);
          }
          else if(ir[0] == 1 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
            turnFullLeft(turning_speed + 20, backward_speed);
          }
          else if(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
            turnFullLeft(turning_speed + 20, backward_speed);
          }
          else if(ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
            turnFullRight(turning_speed, backward_speed);
          }
          for(int ch05 = 0; ch05 < 5; ch05++){
            Serial.print(ir[ch05]);
          } 
          Serial.println();
        }
      }
    }
  }
  if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0) {
      last_side = 'm';
      goForward(forward_speed);
  }
  
  else if (ir[0] == 1 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
      last_side = 'l';
      // tato funkcia dostava pohon do praveho kolesa dopredu a do laveho kolesa dozadu takze sa uplne otoci, ale ked to nebude fungovat tak to vymen za klasicke turnLeft
      turnFullLeft(turning_speed, backward_speed);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
    last_side = 'l';
        turnFullLeft(turning_speed, backward_speed); 
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
      last_side = 'l';
          turnFullLeft(turning_speed, backward_speed);
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
      last_side = 'l';
          turnFullLeft(turning_speed, backward_speed);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      last_side = 'r';
          turnRight(turning_speed, backward_speed);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 0){
      last_side = 'r';
          turnFullRight(turning_speed, backward_speed);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 1){
      last_side = 'r';
          turnFullRight(turning_speed, backward_speed);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 1){
      last_side = 'r';
          // tato funkcia dostava pohon do laveho kolesa dopredu a do praveho kolesa dozadu takze sa uplne otoci, ale ked to nebude fungovat tak to vymen za klasicke turnRight
          turnFullRight(turning_speed, backward_speed);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
      goForward(forward_speed);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 0){
      last_side = 'l';
          turnFullLeft(turning_speed, backward_speed);
  }
  else if (ir[0] == 0 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
      last_side = 'r';
          turnFullRight(turning_speed, backward_speed);
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      last_side = 'm';
          goForward(forward_speed);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 0){
      last_side = 'l';
          turnFullLeft(turning_speed, backward_speed);
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
      last_side = 'r';
          turnFullRight(turning_speed, backward_speed);
  }
  else if(ir[0] == 1 && ir[1] == 0 && ir[2] == 0 && ir[3] == 1 && ir[4] == 1){
    last_side = 'r';
      turnFullRight(turning_speed, backward_speed);
  }
  else if(ir[0] == 1 && ir[1] == 1 && ir[2] == 0 && ir[3] == 0 && ir[4] == 1){
    last_side = 'l';
      turnFullLeft(turning_speed, backward_speed);
  }
  else if(ir[0] == 1 && ir[1] == 0 && ir[2] == 1 && ir[3] == 1 && ir[4] == 1){
    last_side = 'r';
      turnFullRight(turning_speed, backward_speed);
  }
  else if(ir[0] == 1 && ir[1] == 1 && ir[2] == 1 && ir[3] == 0 && ir[4] == 1){
    last_side = 'l';
      turnFullLeft(turning_speed, backward_speed);
  }
  else if(ir[0] == 1 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 1){
    last_side = 'm';
      goForward(forward_speed);
  }
  else if (ir[0] == 1 && ir[1] == 1 && ir[2] == 0 && ir[3] == 1 && ir[4] == 1){
    if(last_side == 'l'){
      turnFullLeft(turning_speed, backward_speed);
    }

    if(last_side == 'r'){
      turnFullRight(turning_speed, backward_speed);
    }

    if(last_side == 'm'){
      goForward(forward_speed);
    }
    
  }
  else if (ir[0] == 0 && ir[1] == 1 && ir[2] == 0 && ir[3] == 1 && ir[4] == 0){
    if(last_side == 'l'){
      turnFullLeft(turning_speed, backward_speed);
    }

    if(last_side == 'r'){
      turnFullRight(turning_speed, backward_speed);
    }

    if(last_side == 'm'){
      goForward(forward_speed);
    }
    
  }
  else if(ir[0] == 1 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 1){
    if(last_side == 'l'){
      turnFullLeft(turning_speed, backward_speed);
    }

    if(last_side == 'r'){
      turnFullRight(turning_speed, backward_speed);
    }

    if(last_side == 'm'){
      goForward(forward_speed);
    }
  }
  
  else if(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
      goForward(forward_speed);
      if(same_states_number == 41){
        Stop();
        turnFullRight(turning_speed, backward_speed);
        delay(800);
        while(ir[0] == 0 && ir[1] == 0 && ir[2] == 0 && ir[3] == 0 && ir[4] == 0){
            goForward(forward_speed);
        }
      }
  }
}
