#include <Servo.h>

Servo servoLeft;  //13번 서보모터 설정(목적->이동)
Servo servoRight; //12번 서보모터 설정(목적->이동)
Servo servoClean; //11번 서보모터 설정(목적->테이블 청소)

void setup() {
  tone(1,4000,1000);
  delay(1000);
  //피에조 스피커 설정

  pinMode(11, INPUT); pinMode(10, OUTPUT);
  pinMode(3, INPUT);  pinMode(2, OUTPUT);
  //입출력 핀 설정(적외선 센서)
  
  servoLeft.attach(13);
  servoRight.attach(12);
  servoClean.attach(11);
  //핀 번호에 따른 서보모터 동작 설정
} //setup함수의 종료

void loop() {
  maneuver(200, 200, 20);   // 1700 1300
  delay(9600);  //전진
  
  maneuver(-200, 200, 340);  //테이블 끝에서 제자리 반시계방향 90degree 회전!   1300 1300

  maneuver(200, 200, 20);     //1700  1300
  delay(2600);  //전진

  maneuver(200, -200, 610);  //테이블 끝에서 제자리 시계방향 180degree 회전!   1700 1700

  maneuver(200, 200, 20);    //1700 1300
  delay(5400);  //전진 
  
  maneuver(200, -200, 300);  //제자리 시계방향 90degree 회전!   1300 1300

  for(int i = 1; i < 5; i++) {
    
    maneuver(200, 200, 400);  //전진  1700 1300  
    
    maneuver(200, -200, 300);  //제자리 시계방향 90degree 회전!   1300 1300
    
    maneuver(200, 200, 2800);  //전진  1700 1300
    
    maneuver(-200, 200, 300); //제자리 반시계방향 90degree 회전!  1700 1700
    
    maneuver(200, 200, 400);  //전진  1700 1300
    
    maneuver(-200, 200, 300);  //제자리 반시계방향 90degree 회전!  1700 1700
    
    maneuver(200, 200, 2800);  //전진  1700 1300

    maneuver(200, -200, 300);  //제자리 시계방향 90degree 회전!   1300 1300
     //총 8회에 걸친 하나의 cycle이 4번 반복한다.
  }
  servoLeft.detach();
  servoRight.detach();
  servoClean.detach();
  //4번 반복을 마치면 서보모터의 동작이 종료된다.

  int irLeft = irDetect(10, 11, 38000);
  int irRight = irDetect(2, 3, 38000);

  if((irLeft == 0) && (irRight == 0)) {       //둘 다 감지되었을 때
    maneuver(-200, -200, 20);     //후진
  }
  else if((irLeft == 0) && (irRight == 1)) {  //왼쪽만 감지되었을 때
    maneuver(-200, 200, 20);     //반시계방향 회전 
  }
  else if((irLeft == 1) && (irRight == 0)){  //오른쪽만 감지되었을 때
    maneuver(200, -200, 20);     //시계방향 회전
  }                             
  else {
    maneuver(200, 200, 20);    //전진
  }

   for(int i = 0; i < 360; i++) 
   {
    servoClean.write(i);
    delay(15);
   }
   servoClean.write(0);
   delay(1000);      //sg90 서보모터의 축이 360 degree만큼 시계방향으로 회전한다.
}  //loop함수의 종료

int irDetect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency, 8);
  delay(1);                      
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;    //적외선 센서의 감지에 관한 사용자 정의 함수
}

void maneuver(int LeftSpeed, int RightSpeed, int Time) {
  servoLeft.writeMicroseconds(1500 + LeftSpeed);  
  servoRight.writeMicroseconds(1500 - RightSpeed);
  delay(Time);

  if(Time == -1) {
    servoLeft.detach();
    servoRight.detach();
    servoClean.detach();
  }
  delay(Time);   //서보모터 13,12(목적:이동)의 동작에 관한 사용자 정의 함수
}
