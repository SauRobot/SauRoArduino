/*
 * Bu proje Android-Bluetooth üzerinden kontrol edilen arabanın Arduino kodlarını içerir.
 * Pin Diagram Arduino mega
 *    
 *    Bluetooth Rx3, Tx3 15, 14  Mega RX TX nasıl Kullanılır ?
 *      int Rst=6;
 *      int State=2;
 *      
 *    Ultrasonic Sensor 1: echo = 39 trig = 38  Ön
 *                      2: echo = 43 trig = 42  Arka
 *                      
 *    Rfid  RST_PIN      48 
 *          SS_PIN (SDA) 53
 *          MOSI         51
 *          MISO         50
 *          SCK          52
 *          Wipe         3
 *          Relay        4   
 *          RedLed       7
 *          IRQ Boş ne işe yarıyor ?
 *          http://playground.arduino.cc/Learning/MFRC522
 *      https://github.com/omersiar/RFID522-Door-Unlock/blob/master/EEPROM/EEPROM.ino
 *      
 *    LCD  22-40 Pin İsim ve bataya yazsın. Bluetooth name i lcd de göster yetli veremn arkadaşı lcd de göster.
 *        D4= 32
 *        D5= 33
 *        D6= 34
 *        D7= 35
 *        RS= 30
 *        EN= 31
 *        
 *    Motorlar 2 çıkış +1 pwm olacak
 *      Ön motor= 8 pwm
 *      IN3= 12
 *      IN4= 13
 *      EN2= 9 pwm    
 *     Button 10,11
 *    Buzzer Kontrol düdüğü 
 *       Buzzer=
 *    Led
 *       Led=
 *    
 * 
 * TODO: Lisans ekle
 */
// extern debugger
//#define debugLight
//#define debug
//#define debug
#include "SauRoMotor.h"
#include "SauRoRFID.h"
#include "SauRoBluetooth.h"
#include "SauRoSensor.h"
#include "SauRoLcd.h"
#include "SauRoTypes.h"
#include "SauRoBluetoothControl.h"

bool yetkiVarMi=false;
bool baglandiMi=true;
unsigned long sensorOkumaSure = 10000; //ms
SauRoLcd myLcd; 
SauRoBluetooth myBt;
SauRoMotor motor;
SauRoRFID RF;
SauRoSensor mySensor;
SauRoBluetoothControl bControl;

int buttonPin=21;
bool surus;
 void Reset(){
   Serial.println("sa");
  bControl.blink();
  }
void setup() {
  Serial.begin(9600);
  Serial.println("SauRo Akilli Araba");
  
  RF.RFIDbegin();
  myBt.Bluetoothbegin();
  myLcd.Lcdbegin();
  mySensor.ultrasonicbegin();
  motor.MotorBegin();
  surus=false;
  bControl.Change();
  myLcd.birinciSatiraYaz("  Hos geldiniz");
  #ifdef debug
    baglandiMi=true;
    yetkiVarMi=true; 
  #endif 

attachInterrupt(digitalPinToInterrupt(buttonPin), Reset, CHANGE);
}

void loop() {
  if(baglandiMi)
  {
    if(yetkiVarMi)
    {
     if(myBt.HizveYonOku())
     {      
      motor.HareketYonveHizHesapla(myBt.hizYon[0]);
      motor.Hiz = mySensor.SensorYonHareketBelirle(motor.Hiz, motor.AracHareketYon);     
      motor.HareketEt(myBt.hizYon[1]);
       
      #ifdef debugLight
        String yazi=String(myBt.hizYon[0]); yazi+= ","; yazi+= String(myBt.hizYon[1]);
        myLcd.ikinciSatiraYaz(yazi);
        Serial.println(yazi);
      #endif
      #ifdef debug
        String yazi=String(myBt.hizYon[0]); yazi+= ","; yazi+= String(myBt.hizYon[1]);
        myLcd.ikinciSatiraYaz(yazi);
        Serial.println(yazi);
      #endif   
     }     
      else
      {         
      motor.Hiz = mySensor.SensorYonHareketBelirle(motor.Hiz, motor.AracHareketYon);     
      motor.HareketEt(myBt.hizYon[1]);
        }
     surus=true;
    }
    else
    {
      myLcd.ikinciSatiraYaz(" Kart Okutunuz!");
      yetkiVarMi = RF.RFIDloop();
      if(yetkiVarMi)
      {
        myLcd.ikinciSatiraYaz("  Iyi Surusler");
      }
    }
  }
  else
  {
    baglandiMi = myBt.baglandiMi();    
  }

}
void MotorTest()
{
}

