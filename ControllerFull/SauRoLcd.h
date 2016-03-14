#include <LiquidCrystal.h>

class SauRoLcd
{
  private:
  int D4=32;
  int D5=33;
  int D6=34;
  int D7=35;
  int RS = 30;
  int EN=31;
  int V0=11;
  String Satir[2]={"",""};
  
  public:
  LiquidCrystal & lcd = *(new LiquidCrystal (RS, EN, D4, D5, D6, D7));
  SauRoLcd()
  {
  }
  void ikinciSatiraYaz(String yazi)
  {
     Satir[1]= yazi;
     Yaz();
  }
  void birinciSatiraYaz(String yazi)
  {
      Satir[0]= yazi;
      Yaz();
  }
  void Yaz()
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(Satir[0]);
    lcd.setCursor(0,1);
    lcd.print(Satir[1]);
  }
  
  void Lcdbegin() {
    lcd.begin(16, 2);
    pinMode(V0,OUTPUT);
    //analogWrite(V0,150);
    digitalWrite(V0,LOW);
  }
};




