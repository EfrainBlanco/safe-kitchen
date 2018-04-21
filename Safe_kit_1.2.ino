#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11 


const int flama = 3;
DHT dht(DHTPIN, DHTTYPE);  //Indica el pin con el que trabajamos y el tipo de sensor
int maxh=0, minh=100, maxt=0, mint=10;
int humoV = A0, gasV = A1;
int humo = 0, gas = 0;
const int paro = 8;

 
 void setup()
{
   Serial.begin(9600);
   pinMode(flama, INPUT);
   Serial.println("Comprobacion de temperatura:");
   dht.begin();
   pinMode(4, OUTPUT);
   pinMode(13,OUTPUT); //humo - motor
   pinMode(12,OUTPUT); //flama
   pinMode(11,OUTPUT); //temperatura
   pinMode(10,OUTPUT); //gas
   pinMode(9,OUTPUT); //electrovalvula
   pinMode(5, OUTPUT); //gas
}
 
void loop()
{


if (digitalRead(paro)==HIGH)
{
  digitalWrite(4,0);
}

//-----------------------Flama--------------------------  
   int humedad = digitalRead(flama);
 
     if (humedad == HIGH)
   {
      Serial.println("ESTUFA ENCENDIDA");
      digitalWrite(12,1);   
   }
   else
  {
    digitalWrite(12,0);
  }
  

//-----------------------Temperatura------------------------------

int h = dht.readHumidity();  //Guarda la lectura de la humedad en la variable float h
  int t = dht.readTemperature();  //Guarda la lectura de la temperatura en la variable float t
 
  // Comprobamos si lo que devuelve el sensor es valido, si no son numeros algo esta fallando
  if (isnan(t) || isnan(h)) // funcion que comprueba si son numeros las variables indicadas 
  {
    Serial.println("Fallo al leer del sensor DHT"); //Mostramos mensaje de fallo si no son numeros
  } else {
    //Mostramos mensaje con valores actuales de humedad y temperatura, asi como maximos y minimos de cada uno de ellos
    Serial.print("Humedad relativa: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: "); 
    Serial.print(t);
    Serial.println(" *C");
    //Comprobacion de maximos y minimos de humedad y temperatura
    if (maxh<h)
      maxh=h;
    if (h<minh)
      minh=h;
    if (maxt<t)
      maxt=t;
    if (t<mint)
      mint=t;
    Serial.print("Max: ");
    Serial.print(maxh);
    Serial.print(" % ");
    Serial.print("Min: ");
    Serial.print(minh);
    Serial.print(" %\t");
    Serial.print("Max: ");
    Serial.print(maxt);
    Serial.print(" *C ");
    Serial.print("Min: ");
    Serial.print(mint);
    Serial.println(" *C\n");
    if(t<=29)
    {
      digitalWrite(11,0);
    }
    else
    {
      digitalWrite(11,1);
      Serial.print("TEMPERATURA ALTA");
      Serial.print("\n");
    }
     
  }
 

//-------------------------Humo--------------------------

humo = analogRead (humoV)/4;


if (humo > 127)
  {
  Serial.print("DETECCIÓN DE HUMO");
  Serial.print("\n");
  digitalWrite(4,1);
  digitalWrite(13,1);
  
  }

if (humo <=127)
digitalWrite(4,0);
digitalWrite(13,0);




//---------------------FUGA de gas---------------------

gas = analogRead (gasV)/4;


if (gas > 127)
  {
  Serial.print("FUGA DE GAS");
  Serial.print("\n");
  digitalWrite(4,0);
  digitalWrite(5,0);
  }
else{
   digitalWrite(5,1);
}

delay(1000);
Serial.flush();

  
}
