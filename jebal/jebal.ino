#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
 
//모터 PIN 설정
#define LEFT_A1 9//왼쪽 바퀴
#define LEFT_B1 10 //왼쪽 바퀴
#define RIGHT_A2 6 //오른쪽 바퀴
#define RIGHT_B2 5 //오른쪽 바퀴
#define LED1 11
#define LED2 12
 
//블루투스 PIN 설정
#define BLUE_TX 8 //블루투스 TX
#define BLUE_RX 7 //블루투스 RX
 
SoftwareSerial mySerial(BLUE_TX, BLUE_RX);  //시리얼 통신을 위한 객체선언
char value; //블루투스에서 받는 값
 
int wheelLeftFront = 9, wheelLeftBack = 10;
int wheelRightFront = 6, wheelRightBack = 5;

int trig = 2, echo = 3; //초음파센서 설정
int spdL = 180, spdR = 180; //속도 값


void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mySerial.begin(9600); //블루투스 시리얼 개방
 
  pinMode(LEFT_A1, OUTPUT);
  pinMode(RIGHT_A2, OUTPUT);
  pinMode(LEFT_B1, OUTPUT);
  pinMode(RIGHT_B2, OUTPUT);  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(wheelLeftFront, OUTPUT);
  pinMode(wheelLeftBack, OUTPUT);
  pinMode(wheelRightFront, OUTPUT);
  pinMode(wheelRightBack, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  Serial.println("Arduino Bluetooth Car is ready to start");
}
 
void loop() {

  float distance, duration;
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;
  Serial.println(distance);
  
   while(mySerial.available())  //mySerial에 전송된 값이 있으면
  {
     value = mySerial.read(); //전송값 읽음
     Serial.print(value);
     
     digitalWrite(LED1, HIGH);
     
     if(value == 'l'){            //좌회전(강)
       Serial.println("left");
       left();
     }else if(value == 'r'){      //우회전(강)
       Serial.println("right");
       right();
     }else if(value == 'f'){      //전진
       Serial.println("forward");
       forward();
     }else if(value == 'b'){      //후진
       Serial.println("backward");
       backward();
     }else if(value == 'w'){      //우회전(약)
       Serial.println("slow right");
       sRight();
     }else if(value == 'q'){      //좌회전(약)
       Serial.println("slow left");
       sLeft();       
     }else if(value == 's'){      //정지
       Serial.println("stop");    
       stop(); 
     }
  }
  if(value == 'o'){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    if(distance > 15){
    //장애물 15cm 이내에 없을 경우 전진
    analogWrite(wheelLeftFront, spdL);
    analogWrite(wheelLeftBack, 0);
    analogWrite(wheelRightFront, spdR);
    analogWrite(wheelRightBack, 0);
  }else{
    //장애물 15cm 이내에 있을 경우 방향전환
    int rd = random(2); //좌,우 회전 랜덤 선택 (랜덤 값 : 0, 1)
    int delayrd = random(300, 700); // 회전 반경, 반환 값 : 200 ~ 500
    if(rd == 1){
      //좌회전
      analogWrite(wheelLeftFront, 0);
      analogWrite(wheelLeftBack, spdL);
      analogWrite(wheelRightFront, spdR);
      analogWrite(wheelRightBack, 0);
    }else{
      //우회전
      analogWrite(wheelLeftFront, spdL);
      analogWrite(wheelLeftBack, 0);
      analogWrite(wheelRightFront, 0);
      analogWrite(wheelRightBack, spdR);
    }
    delay(delayrd);
  }
  }else if(value == 'z'){

    digitalWrite(LED2, LOW);
    digitalWrite(LED1, HIGH);
    while(mySerial.available())  //mySerial에 전송된 값이 있으면
  {
     value = mySerial.read(); //전송값 읽음
     Serial.print(value);
     
     if(value == 'l'){            //좌회전(강)
       Serial.println("left");
       left();
     }else if(value == 'r'){      //우회전(강)
       Serial.println("right");
       right();
     }else if(value == 'f'){      //전진
       Serial.println("forward");
       forward();
     }else if(value == 'b'){      //후진
       Serial.println("backward");
       backward();
     }else if(value == 'w'){      //우회전(약)
       Serial.println("slow right");
       sRight();
     }else if(value == 'q'){      //좌회전(약)
       Serial.println("slow left");
       sLeft();       
     }else if(value == 's'){      //정지
       Serial.println("stop");    
       stop(); 
     }
  }
  }
  }

 
// 자동차 움직임 정의 Function 들
void forward(){
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
}
void backward(){
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, HIGH);
}
void left(){
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
}
void right(){
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, HIGH);
}
void sLeft(){
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
}
void sRight(){
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, LOW);
}
void stop(){
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, LOW);
}
