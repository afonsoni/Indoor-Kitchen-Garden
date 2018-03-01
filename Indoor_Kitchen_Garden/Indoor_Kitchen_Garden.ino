#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

#define sensorHumidade A1 //
#define ONE_WIRE_BUS 2 //Temp
#define DHTPIN 4 //Ar
#define DHTTYPE DHT22 //Ar

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DHT dht(DHTPIN, DHTTYPE);

unsigned long tempoAnterior = 0;
unsigned long intervalo = 1000;

void setup()
{
  Serial.begin(9600);
  dht.begin();
  sensors.begin();
  Serial.println("Indoor Kitchen Garden");
  delay(500);
  Serial.println("Início");
  delay(2000);
}

void loop()
{
  // A leitura da temperatura e humidade pode levar 250ms
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("HUMIDADE DO AR: ");
    Serial.print(h);
    Serial.print(" %  ");
    Serial.print("TEMPERATURA DO AR: ");
    Serial.print(t);
    Serial.print(" ºC  ");
  }
  //Sensor do Ar ^^
  
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  Serial.print("Temp: "); 
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("  ");
   // Porquê "byIndex"?  
   // Pode haver mais do que um DS18B20
   // 0 representa o primeiro sensor

   //Sensor Temperatura Terra ^^

   unsigned long tempoAtual = millis(); // Realizamos a leitura atual do tempo em que o nosso Arduino Nano está ligado
  if (tempoAtual-tempoAnterior > intervalo)
  { 
  // Pequena lógica para realizar leituras temporizadas sem parar o microcontrolador
  tempoAnterior =tempoAtual; // Guardamos o tempo anterior como o ultimo intervalo de tempo lido
  int leitura = analogRead(sensorHumidade); // Leitura dos dados analógicos vindos do sensor de umidade de solo
 
  if (leitura<=1023 && leitura>=500)
  {
    // Se a leitura feita for um valor entre 1023 e 682 podemos definir que o solo está com uma baixa condutividade, logo a planta deve ser regada
    Serial.print("Nível de Humidade Alto: ");
    Serial.print(leitura);
    Serial.println("  ");
  }
  
  else
  {
     if (leitura<=500 && leitura>=250)
     {
       // Se a leitura feita for um valor entre 681 e 341 podemos definir que o solo está com um nível médio de humidade, logo dependendo da planta pode ou não ser vantajoso regar
       Serial.print("Nível de Humidade Médio: ");
       Serial.print(leitura);
       Serial.println("  ");
     }
     else
     {
        if (leitura<=250 && leitura>=0)
        {
           // Se a leitura feita for um valor entre 0 e 340 podemos definir que o solo está com um nível aceitável de humidade, logo talvez não seja interessante regar neste momento
           Serial.print("Nível de Humidade Baixo: ");
           Serial.print(leitura);
           Serial.println("  ");
        }
     } 
   }
   }

  //Sensor Humidade Terra ^^
  delay(500);
}

