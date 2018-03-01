#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
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
    Serial.print("Humidade: ");
    Serial.print(h);
    Serial.print(" %");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" ºC");
  }
}
