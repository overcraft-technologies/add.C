#include <addC.h>



addC usbc(71 ,1);
String stringRead;
int addr;
int regid;

void setup() 
{
  Serial.begin(9600);
  while (!Serial) {;}
  
  Serial.println("OverCraft Technologies add.C Connector");
  syssetup();



  Serial.print("\nDevice: ");
  for(int i = 7; i >= 0; i--)
  {
    Serial.write(usbc.deviceId(i));
    delay(100);
  }
  Serial.println("");
}
void loop()
{
  menu();
}
void menu()
{
  while(Serial.available() == 0) {;}

  stringRead = Serial.readString();

  if(stringRead == "lesen;\n")
  {
    lesen();
  }
  else if(stringRead == "schreiben;\n")
  {
    schreiben();
  }
  else if(stringRead == "hilfe\n")
  {
    hilfe();
  }
  else if(stringRead == "setup\n")
  {
    syssetup();
  }
  else
  {
    Serial.println("\n---error 01--- //Befehl existiert nicht.");
    Serial.println("Benutze 'hilfe' um eine Liste mit allen Befehlen anzuzeigen.");
  }
}

void lesen()
{
  Serial.print("Current Detect: ");
  Serial.println(usbc.currentDetect(), BIN);
delay(100);
  Serial.print("Accessory Connected: ");
  Serial.println(usbc.accessoryConnected(), BIN);
delay(100);
  Serial.print("Active Cable: ");
  Serial.println(usbc.activeCable(), BIN);
delay(100);
  Serial.print("Attached State: ");
  Serial.println(usbc.attachedState(), BIN);
delay(100);
  Serial.print("Cable Direction: ");
  Serial.println(usbc.cableDirection(), BIN);
delay(100);
  Serial.print("Interrupt Status: ");
  Serial.println(usbc.interruptStatus(), BIN);
delay(100);
}

void schreiben()
{
 
  Serial.println("\n*Schreiben*\n");
  
}

void syssetup()
{
  Serial.println("\n*SETUP*\n");
  Serial.print("Addrese eingeben: ");
  while(Serial.available() == 0) {;}

  addr = Serial.parseInt();

  Serial.print("Die Addresse ist 0x");
  Serial.print(addr, HEX);
  Serial.print(" HEX, ");
  Serial.print(addr, DEC);
  Serial.println(" DEC.");

  
}
void hilfe()
{
  Serial.println("\n*BEFEHLE*\n");
  Serial.println("lesen");
  Serial.println("schreiben");
  Serial.println("setup");
  Serial.println("Alle Befehle müssen von einem Semikolon ';' gefolgt werden. ");
}


