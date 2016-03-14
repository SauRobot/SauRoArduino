#include <SoftwareSerial.h>
#include <String.h>
#include <Time.h>
class SauRoBluetoothControl
{
	
	 public:
   SauRoBluetoothControl()
  {   
    pinMode(buttonPin, INPUT);
	pinMode(reset, OUTPUT);
	digitalWrite(reset,HIGH ); 
  }
	HardwareSerial & BTserial = Serial3; 
	char c = ' ';
	int buttonPin=21;
	int reset=10;
	int buttonState = LOW;
	time_t oncekisaniye=0;
 void Reset()
{
  time_t saniye;
  saniye = second();
 if(oncekisaniye!=0 && saniye!=oncekisaniye)
 {  
  Serial.println("res");
  digitalWrite(reset,LOW );
  delay(1000);
  digitalWrite(reset,HIGH );
  }
  oncekisaniye=saniye;
  Serial.println("Saniye"+String(saniye));
  buttonState = !buttonState;
}
void Change(){
      String isim=SendAtCommand("AT+NAME=SauRoAkilliAraba");
       Serial.println(isim);
    String sifre=SendAtCommand("AT+PSWD=sauro");
       Serial.println(sifre);
    }
String SendAtCommand(String command){
    
    String response="";
    BTserial.println(command);
    response =BTserial.readString(); 
    return response;
  }
};