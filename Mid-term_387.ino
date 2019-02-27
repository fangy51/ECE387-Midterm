#include <LiquidCrystal.h>
#include<SoftwareSerial.h>

SoftwareSerial mySerial(16, 17); //A2 and A3 on UNO R3 board
int OPP = 14;
int OPP1 = 12;
int OPP2 = 10;
int OPP_GND = 15;
int OPP_GND1 = 13;
int OPP_GND2 = 11;
int dis;
int str;
int ck;
int i;
int j[9];
const int C = 0x59;

// assign arduino pin number for LCD 1602
const int rs = 8, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2, rw = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
pinMode(LED_BUILTIN, OUTPUT);
pinMode(OPP, OUTPUT);
pinMode(OPP1, OUTPUT);
pinMode(OPP2, OUTPUT);
pinMode(OPP_GND, OUTPUT);
pinMode(OPP_GND1, OUTPUT);
pinMode(OPP_GND2, OUTPUT);
pinMode(rw, OUTPUT);
digitalWrite(OPP_GND, LOW);
digitalWrite(OPP_GND1, LOW);
digitalWrite(OPP_GND2, LOW);
digitalWrite(rw, LOW);
lcd.begin(16, 2);
Serial.begin(115200);
mySerial.begin(115200);
}

void loop(){
 if (mySerial.available())//check if there is input
 {
    if(mySerial.read()==C)//check frame header
    {
      j[0]=C;
      if(mySerial.read()==C){
        j[1]=C;
        for(i=2;i<9;i++){
          j[i]=mySerial.read();
        } 
       ck=j[0]+j[1]+j[2]+j[3]+j[4]+j[5]+j[6]+j[7];
        if(j[8]==(ck&0xff))//check result
        {
          dis=j[2]+j[3]*256;//calculate distance
          str=j[4]+j[5]*256;//calculate signal strength

lcd.setCursor(0, 0);
lcd.print("D=");
//Leave a space if quantity of distance/signal strength is small
if(dis<100 && dis >=10){ 
lcd.print(" ");
lcd.print(dis);
}
else if(dis>0 && dis<10){
lcd.print(" ");
lcd.print(dis); 
}
else{
lcd.print(dis);
}

lcd.print("cm S=");
if(str>=100 && str<=999){
lcd.print(str);
lcd.print(" ");
}
else if(str<100 && str>=10){ 
lcd.print(str);
lcd.print(" ");
}
else{
lcd.print(str);
}
Serial.print("Object Distance = ");
  Serial.print(dis);
  Serial.print(" cm      signal strength = ");
  Serial.println(str); 
    }
   }
  } 
 }
}
