#include <PS3BT.h>
#include <usbhub.h>
#include <Servo.h>

USB Usb;
BTD Btd(&Usb); 
PS3BT PS3(&Btd); 

Servo myservo[2];  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 110;    // variable to store the servo position
int pos2 = 70;

//1は＋、2はマイナス
#define UR1 22  //右前
#define UR2 24  
#define UL1 26  //左前
#define UL2 28   
#define DR1 30  //後ろ右
#define DR2 32  
#define DL1 34  //後ろ左
#define DL2 36  
#define M1 6    //モーター
#define M2 7
#define Se_1 44  //サーボ1
#define Se_2 46  //サーボ2

void setup() {
  pinMode(UR1,OUTPUT);
  pinMode(UR2,OUTPUT);
  pinMode(UL1,OUTPUT);
  pinMode(UL2,OUTPUT);
  pinMode(DR1,OUTPUT);
  pinMode(DR2,OUTPUT);
  pinMode(DL1,OUTPUT);
  pinMode(DL2,OUTPUT);
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);

  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  myservo[0].attach(Se_1);  // attaches the servo on pin 9 to the servo object
  myservo[1].attach(Se_2);
}

void loop() {
  Usb.Task();
  if (PS3.PS3Connected) {
    //△〇×□ボタン
    if (PS3.getButtonPress(TRIANGLE)){  //サーボ1（アームUp）
      if (pos <= 110){
        Serial.print(F("\r\n△：↗"));
        myservo[0].write(pos);          // tell servo to go to position in variable 'pos'
        pos += 1;
        delay(12);                      // waits 12ms for the servo to reach the position
      }
    }
    else if (PS3.getButtonPress(SQUARE)){  //サーボ1（アームDown）
      if (pos >= 0){
        Serial.print(F("\r\n□：↙"));
        myservo[0].write(pos);             // tell servo to go to position in variable 'pos'
        pos -= 1;
        delay(12);                         // waits 12ms for the servo to reach the position
      }
    }
    else if (PS3.getButtonClick(CIRCLE)){  //サーボ2（つかむ）
      Serial.print(F("\r\n○：open"));
      for (; pos2 <= 70; pos2 += 1) {      // goes from 0 degrees to 180 degrees
        myservo[1].write(pos2);            // tell servo to go to position in variable 'pos'
        delay(12);                         // waits 50ms for the servo to reach the position
      }
    }
    else if (PS3.getButtonClick(CROSS)){  //サーボ2（放す）
      Serial.print(F("\r\n✕：close"));
      for (; pos2 >= 42; pos2 -= 1) {     // goes from 0 degrees to 180 degrees
        myservo[1].write(pos2);           // tell servo to go to position in variable 'pos'
        delay(12);                        // waits 50ms for the servo to reach the position
      }
    }
    //PSボタン
    else if (PS3.getButtonClick(PS)){
      //各ボタンの中にモーターを動かしたりトランジスタを動かしたりサーボを動かす処理をかいてください
      Serial.print(F("\r\nPS"));
    }
    //十字ボタン
    else if (PS3.getButtonPress(UP)) {  //前進
      Serial.print(F("\r\nUp")); 
      digitalWrite(UR1,HIGH);
      digitalWrite(UR2,LOW);
      digitalWrite(UL1,HIGH);
      digitalWrite(UL2,LOW);
      digitalWrite(DR1,HIGH);
      digitalWrite(DR2,LOW);
      digitalWrite(DL1,HIGH);
      digitalWrite(DL2,LOW);
    }
    else  if (PS3.getButtonPress(RIGHT)) {  //右
      Serial.print(F("\r\nRight"));
      digitalWrite(UR1,HIGH);
      digitalWrite(UR2,LOW);
      digitalWrite(UL1,LOW);
      digitalWrite(UL2,HIGH);
      digitalWrite(DR1,HIGH);
      digitalWrite(DR2,LOW);
      digitalWrite(DL1,LOW);
      digitalWrite(DL2,HIGH);
    }
    else  if (PS3.getButtonPress(DOWN)) {  //後進
      Serial.print(F("\r\nDown"));  
      digitalWrite(UR1,LOW);
      digitalWrite(UR2,HIGH);
      digitalWrite(UL1,LOW);
      digitalWrite(UL2,HIGH);
      digitalWrite(DR1,LOW);
      digitalWrite(DR2,HIGH);
      digitalWrite(DL1,LOW);
      digitalWrite(DL2,HIGH);
    }
    else  if (PS3.getButtonPress(LEFT)) {  //左
      Serial.print(F("\r\nLeft"));
      digitalWrite(UR1,LOW);
      digitalWrite(UR2,HIGH);
      digitalWrite(UL1,HIGH);
      digitalWrite(UL2,LOW);
      digitalWrite(DR1,LOW);
      digitalWrite(DR2,HIGH);
      digitalWrite(DL1,HIGH);
      digitalWrite(DL2,LOW);
      
    //その他のボタン
    }
    else if (PS3.getButtonPress(L1)){
      Serial.print(F("\r\nL1：メジャー収納"));
      analogWrite(M1,0);
      analogWrite(M2,254);
    }
    else if (PS3.getButtonPress(L2)) {
      Serial.print(F("\r\nL2：左旋回"));
      digitalWrite(UR1,LOW);
      digitalWrite(UR2,HIGH);
      digitalWrite(UL1,HIGH);
      digitalWrite(UL2,LOW);
      digitalWrite(DR1,HIGH);
      digitalWrite(DR2,LOW);
      digitalWrite(DL1,LOW);
      digitalWrite(DL2,HIGH);
    }
    else if (PS3.getButtonPress(L3)){
      Serial.print(F("\r\nL3"));
    }
    else if (PS3.getButtonPress(R1)){
      Serial.print(F("\r\nR1：メジャー出力"));
      analogWrite(M1,254);
      analogWrite(M2,0);
    }
    else if (PS3.getButtonPress(R2)){
      Serial.print(F("\r\nR2：右旋回"));
      digitalWrite(UR1,HIGH);
      digitalWrite(UR2,LOW);
      digitalWrite(UL1,LOW);
      digitalWrite(UL2,HIGH);
      digitalWrite(DR1,LOW);
      digitalWrite(DR2,HIGH);
      digitalWrite(DL1,HIGH);
      digitalWrite(DL2,LOW);
    }
    else if (PS3.getButtonPress(R3)){
      Serial.print(F("\r\nR3"));
    }
    else if (PS3.getButtonPress(SELECT)) {
      Serial.print(F("\r\nSelect"));
    }
    else if (PS3.getButtonPress(START)) {
      Serial.print(F("\r\nStart"));
    }
    else{
    Serial.print(F("\r"));    
    digitalWrite(UR1,LOW);
    digitalWrite(UR2,LOW);
    digitalWrite(UL1,LOW);
    digitalWrite(UL2,LOW);
    digitalWrite(DR1,LOW);
    digitalWrite(DR2,LOW);
    digitalWrite(DL1,LOW);
    digitalWrite(DL2,LOW);
    digitalWrite(M1,LOW);
    digitalWrite(M2,LOW);
    }
  }
}
