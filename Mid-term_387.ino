//Author:Yifan Fang
//ECE387_Spring 2019_MU
//lidar range sensor working together with LCD 1602 module
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>

SoftwareSerial mySerial(11, 12);      // 12 > TXD, 11 > RXD, 5V > red cable, GND > black cable
int dis;// distance detected
int str;// signal strength
int ck;// used for saving data while checking
int i;
int j[9];//
const int C=0x59;//

// assign arduino pin number for LCD 1602

LiquidCrystal lcd(8, 6, 5, 4, 3, 2); // pin8=RS PIN6=E pin5-2=D4-7

void setup(){
Serial.begin(115200);
  while (!Serial);  
  Serial.println ("getting ready...");
mySerial.begin(115200);
delay (1);
lcd.begin(16, 2);

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
          
  // Display the measurement when signal strength >= 0
  if(str >= 0){
   Serial.print("Object Distance = ");
  Serial.print(dis);
  Serial.print(" cm      signal strength = ");
  Serial.println(str); 
  //make a 100 ms delay to reduce data collected/samples

  }
}
      }
    }
  }
lcd.setCursor(0, 0);
lcd.print("D=");
//Leave a space if quantity of distance/signal strength is small（because their was some display errors(display some other number/letter which is useless by end of "dis"/"str"), when I did not leave spaces）
if(dis<100 && dis >=10){ 
lcd.print(" ");
lcd.print(dis);
}
else if(dis>0 && dis<10){
lcd.print(" ");
lcd.print(dis); 
}
else
lcd.print(dis);


lcd.print("cm  S=");
if(str>=100 && str<=999){
lcd.print(str);
lcd.print("    ");
}
else if(str<100 && str>=10){ 
lcd.print(str);
lcd.print("    ");
}
else if(str>=1000)
lcd.print(str);
   
   }
