
#include <SoftwareSerial.h>

// Setup software serial port 
SoftwareSerial mySerial(11, 12);      // 12 > RX, 11 > TX
int dis;// distance detected
int str;// signal strength
int ck;// used for saving data while checking
int i;
int uart[9];//
const int C=0x59;//


void setup() {
  //Initialize hardware serial port (serial debug port)
  Serial.begin(115200);
  
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);
     
  Serial.println ("getting ready...");

  // Step 2: Initialize the data rate for the SoftwareSerial port
  mySerial.begin(115200);    
}


void loop() {
  if (mySerial.available())//查看串口是否有数据输入
  {
    if(mySerial.read()==C)//判断数据包帧头0x59
    {
      uart[0]=C;
      if(mySerial.read()==C)//判断数据包帧头0x59
      {
        uart[1]=C;
        for(i=2;i<9;i++)//存储数据到数组
        {
          uart[i]=mySerial.read();
         } 
       ck=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
        if(uart[8]==(ck&0xff))//按照协议对收到的数据进行校验
        {
          dis=uart[2]+uart[3]*256;//计算距离值
          str=uart[4]+uart[5]*256;//计算信号强度值
          
  // Display the measurement
   Serial.print("Object Distance = ");
  Serial.print(dis);
  Serial.print(" cm      signal strength = ");
  Serial.println(str); 
}
      }
    }
  }
 }

// the detected distance and signal strengh can be monited monitored by Tools>> Serial monitor (Ctrl+Shift+M)
// the measurable range is from 30cm to 1200cm 
