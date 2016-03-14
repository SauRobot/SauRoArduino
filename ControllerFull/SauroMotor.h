
#include "SauroTypes.h"

#include <Servo.h>


class SauRoMotor{

  public:

//yon ön motor servo
Servo servomotor;
int servoPin = 8;


//hız arka motor dc
int enbB_hiz = 9;
int IN3 = 12;
int IN4 = 13;
/*
//yon ön motor
int enbA_yon = 4;
int IN2 = 5;
int IN1 = 6;
*/
 
int DereceMin=80;
int DereceMax=130;

int Hiz;
HareketYon AracHareketYon;

SauRoMotor() 
{
}
void DegerGidisYonu()
{
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enbB_hiz, OUTPUT);
}

void ileriGit()
{
  #ifdef debug
  Serial.println("F:ileriGit");
  #endif
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void geriGit()
{
  #ifdef debug
  Serial.println("F:gerigit");
  #endif
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void dur()
{
  #ifdef debug
  Serial.println("F:dur");
  #endif
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

int HizBelirle(int hizDeger)
{
  analogWrite(enbB_hiz, map(hizDeger,1,10,100,200));
}

void ServoMotor(int AlinanDeger)
{
 servomotor.write(map(AlinanDeger,0,20,DereceMin,DereceMax));
 #ifdef debug
    String yazi="Yonderece:";yazi+=String(map(AlinanDeger,0,20,DereceMin,DereceMax));
    Serial.println(yazi);
  #endif
}

void MotorBegin()
{
  DegerGidisYonu();
  servomotor.attach(servoPin);
}

void HizDusur(int Hiz)
{
    Hiz =map(Hiz,1,10,1,5);
}
    
void HareketYonveHizHesapla(int hiz)
{
  if(hiz>10) {          //ileri yönde
  Hiz =map(hiz,11,20,1,10);
  AracHareketYon = On;}

  else if(hiz<10){      //geri yönde 
  Hiz = map(hiz,9,0,1,10);
  AracHareketYon = Arka;
  }
  
  else{
  Hiz = 0;
  AracHareketYon = Dur;
  }
   #ifdef debug
  Serial.println("F:HareketYonveHizHesapla; Gelen Hizi=" +String (hiz) +"Yon="+String (AracHareketYon) +"Hesapanan Hiz=" +String (Hiz));
  #endif 
}

void HareketEt(int yon)
{
  //todo:return değiştir.
    
    ServoMotor(20-yon);

  if(Hiz == 0 && !(AracHareketYon == Dur)){

    Hiz = 10;
    if(AracHareketYon == On){
      AracHareketYon = Arka;
    }
    else
    AracHareketYon =On;
    

    #ifdef debug
    Serial.println("F:HareketEt;Yon=" + String (yon) +"Hız: DUR" );
    #endif
    
  }
  
  HizBelirle(Hiz);

  if(AracHareketYon == On){
  ileriGit();
  }
  else if(AracHareketYon == Arka){
  geriGit();
  }
  else if(AracHareketYon == Dur){
  dur();
  }

  #ifdef debug
  Serial.println("F:HareketEt;Yon=" + String (yon) +"Hız"+String (Hiz) );
  #endif

}

};

