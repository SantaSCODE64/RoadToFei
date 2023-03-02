#include<math.h>
int left_motor_forward = 4;
int left_motor_backward = 5;
int right_motor_forward = 3;
int right_motor_backward = 2;
int ir_pins[5] = {22, 23, 24, 25, 26};
int ir[5];
int sum_of_ir;

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
    digitalWrite(left_motor_forward, LOW);
    analogWrite(right_motor_forward, _speed);
    analogWrite(left_motor_backward, LOW);
    digitalWrite(right_motor_backward, LOW);
  }

  void turnRight(int _speed) {
    analogWrite(left_motor_forward, _speed);
    digitalWrite(right_motor_forward, LOW);
    digitalWrite(left_motor_backward, LOW);
    analogWrite(right_motor_backward, LOW);
  }
  void Stop() {
    digitalWrite(left_motor_forward, LOW);
    digitalWrite(right_motor_forward, LOW);
    digitalWrite(left_motor_backward, LOW);
    digitalWrite(right_motor_backward, LOW);
  }

  void goBack(int _speed) {
    digitalWrite(left_motor_forward, LOW);
    digitalWrite(right_motor_forward, LOW);
    analogWrite(left_motor_backward, _speed);
    analogWrite(right_motor_backward, _speed);
  }
  void findLine(int _speed) {
    analogWrite(left_motor_forward, _speed);
    analogWrite(left_motor_forward, 0);
    analogWrite(right_motor_forward, _speed);
    analogWrite(right_motor_forward, _speed);
    analogWrite(right_motor_forward, 0);
    analogWrite(left_motor_forward, _speed);
    analogWrite(left_motor_forward, 0);
  }

void loop() {
  int number = 0;
  binArray();

  
  for (number = 0; number<5; number++){
    Serial.print(ir[number]);
  }
  Serial.println();
  delay(500);
  if (ir[2] == 1){
    goForward(60);
  }
  if (ir[0] == 1){
    turnLeft(60);
  }
  if (ir[4] == 1){
    turnRight(60);
  }
  if (ir[3] == 1){
    turnRight(60);
  }
  if (ir[1] == 1){
    turnLeft(60);
  }
  if(ir[0] == 1 && ir[1] == 1){
    turnLeft(40);
  }
  if(ir[3] == 1 && ir[4] == 1){
    turnRight(40);
  }
  if(sum_of_ir == 0){
    goForward(60);
  }
}
