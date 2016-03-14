
#include "SauroTypes.h"

class SauRoSensor
{
private:
unsigned long echo_arka = 43;
int trig_arka = 42; // Ultrasound signal pin
unsigned long echo_on = 39;
int trig_on = 38;
int maxMesafe=70;
int minMesafe=30;


public:
SauRoSensor()
{
}
void ultrasonicbegin()
{

  maxMesafe*=58.2;
  minMesafe*=58.2;
  pinMode(trig_on, OUTPUT);
  pinMode(trig_arka, OUTPUT);
  pinMode(echo_on, INPUT);
  pinMode(echo_arka, INPUT);
}



int SensorYonHareketBelirle(int hiz,HareketYon hareketYon){
 
  int hesaplananHiz;
  int mesafe;
  
  if(hareketYon==On){
   mesafe = SensorOn();
  }

  else if(hareketYon==Arka){
    mesafe = SensorArka();
  }

  if((mesafe<maxMesafe)&&(mesafe>minMesafe))
  {
    hesaplananHiz = map(mesafe, minMesafe ,maxMesafe, 1,10);
    if(hiz<hesaplananHiz)
    {
      hesaplananHiz = hiz;
    }
  }
    
  else if(mesafe<=minMesafe){
    hesaplananHiz = 0;
  }

  else if(mesafe>=maxMesafe)
  {
    hesaplananHiz = hiz;
  }

   #ifdef debug
  Serial.println("F:SensorYonHareketBelirle; Gelen Hizi=" +String (hiz) +"Yon="+String (hareketYon) +"Hesapanan Hiz=" +String (hesaplananHiz));
  #endif 
  
 return hesaplananHiz; 
}

int SensorOn()
{
trighesap(trig_on);
return mesafe(echo_on);
}

int SensorArka()
{
trighesap(trig_arka);
return mesafe(echo_arka);
}


void trighesap(int trig){
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
}


int mesafe(int echo ){ 
  return pulseIn(echo, HIGH);
}
 
};
