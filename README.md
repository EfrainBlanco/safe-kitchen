// SafeKitchen bosquejo entrada salidas 
//
#include "DHT.h"  // se incluye librería 
#define DHTPIN 2  // se declara entrada de sensor
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
const int flama = 3; // se declara la entrada del sensor de flama digital 
int maxh=0, minh=100, maxt=0, mint=10;  // rengos de temperatura maximos y minimos de lectura
int humoV = A0, gasV = A1;  // se declaran las entradas analógicas 
int humo = 0, gas = 0;  // valores iniciales 
int humedad;
 
 void setup()
{
   Serial.begin(9600); // se establece la velocidad de la comunicación
   pinMode(flama, INPUT);// se declara como entrada 
   Serial.println("Comprobacion de temperatura:");
   dht.begin();
}
 
void loop()
{
  //---------------------FUGA de gas---------------------
gas = analogRead (gasV)/4; // se hace la lectura de gas
if (gas > 127)// si el valor del gas es mayor al rango adecuado no hace nada más el programa 
  {
  Serial.print("FUGA DE GAS");
  Serial.print("\n");
  digitalWrite(13,1);
  delay(5000);
  }
else
 {
//-----------------------Flama--------------------------  
humedad = digitalRead(flama);
     if (humedad == HIGH)
   {
      Serial.println("ESTUFA ENCENDIDA");   
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
  }
                                  //-------------------------Humo--------------------------
humo = analogRead (humoV)/4;
if (humo > 127)
      {
  Serial.print("DETECCIÓN DE HUMO");
  Serial.print("\n");
  digitalWrite(4,1);
  delay(5000);
      }
if (humo <=127)
    {
digitalWrite(4,0);
delay(1000);
    }

  }
}
