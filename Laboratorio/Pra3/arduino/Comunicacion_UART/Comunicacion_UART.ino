#include <SoftwareSerial.h>
const int RX = 3;
const int TX = 4;
#define sleep   1000

byte trama_tem[4]= {0x24,0x01,0x00,0x25};
byte trama_dis[4]= {0x24,0x02,0x00,0x26};
byte trama_led[4]= {0x24,0x83,0x32,0xD2};
byte trama_mot[4]= {0x24,0x84,0x0A,0xD9};
byte con=0;
SoftwareSerial mi_uart(RX, TX);
void setup()
{
   Serial.begin(115200);
   mi_uart.begin(9600);
   delay(1000);
}
void send_data(byte trama[4]);
void loop()
{
  if (mi_uart.available()){
      char data;
      data = mi_uart.read();
      Serial.print(data,HEX);
      Serial.print(",");
  }
  else{
      switch(con){
      case 0:
        send_data(trama_dis);
        delay(sleep);
        con++;
        Serial.println("");
      break;
      case 1:
        send_data(trama_tem);
        delay(sleep);
        con++;
        Serial.println("");
      break;
      case 2:
        trama_mot[3]=(trama_mot[0]+trama_mot[1]+trama_mot[2]) % 256;
        send_data(trama_mot);
        delay(sleep);
        trama_mot[2]+=10;
        con++;
        Serial.println("");
      break;
      case 3:
        con=0;
      break;
  }
  }
  
  
}
void send_data(byte trama[4]){
      for (int i=0;i<4;i++){
          mi_uart.write(trama[i]);
          //Serial.println(trama[i]);  
          delay(1);
      }
}

   /*if (mi_uart.available())
   {
      char data;
      data = mi_uart.read();
      Serial.print(data);
      mi_uart.print(data);
      /*
      for(int i=0;i<4;i++){
        mi_uart.print(trama[i]);
        Serial.print(trama[i]);
      }
   }*/
   
