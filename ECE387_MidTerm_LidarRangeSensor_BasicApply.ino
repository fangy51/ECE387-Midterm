//Author: Yifan Fang
//ECE387_SPRING 2019 TERM

#include <SoftwareSerial.h>

// Setup software serial port 
SoftwareSerial mySerial(11, 12);      // 12 > TXD, 11 > RXD, 5V > red cable, GND > black cable
int dis;// distance detected
int str;// signal strength
int ck;// used for saving data while checking
int i;
int j[9];//
const int C=0x59;//


void setup() {
  //Initialize hardware serial port
  Serial.begin(115200);
  
  // wait for serial port to connect.
  while (!Serial);
     
  Serial.println ("getting ready...");

  //Initialize data rate for the SoftwareSerial port
  mySerial.begin(115200);    
}


void loop() {
  if (mySerial.available())//check if there is input
  {
    if(mySerial.read()==C)//check frame header
    {
      j[0]=C;
      if(mySerial.read()==C)//
      {
        j[1]=C;
        for(i=2;i<9;i++)//
        {
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
  delay(100);
  }
}
      }
    }
  }
 }

// the detected distance and signal strengh can be monited monitored by Tools>> Serial monitor (Ctrl+Shift+M)
// the measurable range is from 30cm to 1200cm 
