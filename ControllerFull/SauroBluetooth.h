// https://www.arduino.cc/en/Reference/Serial
//http://www.instructables.com/files/orig/FQ1/CUVZ/HXA9PUVQ/FQ1CUVZHXA9PUVQ.pdf
//http://www.martyncurrey.com/hc-05-and-hc-06-zs-040-bluetooth-modules-first-look/


class SauRoBluetooth{
  int Rst=40;
  int Key=41;
  char Syn='U';
  char AckFlag='S';
public:
  SauRoBluetooth(){
  }
  
  HardwareSerial & myBluetooth = Serial3;
  int DURMADEGERI =10;
  int hizYon[2]; 
  
  void Bluetoothbegin() {
    myBluetooth.begin(9600); 
    pinMode(Rst,OUTPUT);
    pinMode(Key,OUTPUT);
    HizYonSifirla();
  }
  
  void HizYonSifirla()
  {
    hizYon[0]=DURMADEGERI;
    hizYon[1]=DURMADEGERI;
  }
  
  bool  HizveYonOku() {
    #ifdef debug
    
    Serial.println("F:HizveYonOku start");
    #endif
    if (myBluetooth.available())                 // bluetooth bağlantısı varsa
    {
      if(myBluetooth.read() != '{')         
      {
        return false;
      }
      hizYon[0]=myBluetooth.parseInt();
      if(',' !=myBluetooth.read())
      {
        return false;
      }
      hizYon[1]=myBluetooth.parseInt();
      return true;
    }
    
    return false;
  }
  bool baglandiMi()
  {
    if (myBluetooth.available())             
    {
      //TODO
      if(myBluetooth.read()==Syn)
      {
        myBluetooth.write(AckFlag); 
        delay(3000);
       if(myBluetooth.read()==AckFlag)
        {  
          return true;
        }               
      }      
      return false;
    }
    else
    {
      return false;
    }
  }
  void Reset()
  {
    digitalWrite(Rst,LOW);
    delay(100);
    digitalWrite(Rst,HIGH);
  }
  String SendAtCommand(String command){
    String response="";
    int querylen;
    char * query;
    command += "\n\r";
    command.toCharArray(query,querylen);
    digitalWrite(Key, HIGH);
    myBluetooth.write(query);
    response =myBluetooth.readString(); 
    digitalWrite(Key, LOW);
    Serial.println(query);
    return response;
  }
};

