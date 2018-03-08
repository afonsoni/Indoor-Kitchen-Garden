#include <OneWire.h>
#include <DallasTemperature.h>


//excel
int linha = 0;
int LABEL = 1;




//TEMPERATURA DO SOLO
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//HUMIDADE DO SOLO
#define    analogi    A0
#define    digital    15
#define    gnd_pin    16
#define    vcc_pin    17
double humsolo;

//VENTOINHA
int sensorPin = A1;
int PWM = 3;
int sensorVal = 0;
int PWMVal = 0;
double erro;
int K = 75;

//BUZZER
int buzzer = 10;

//LÂMPADA
int portaRele = 7;

void setup() {

  //VENTOINHA
  pinMode(sensorPin, INPUT);
  pinMode(PWM, OUTPUT);
  Serial.begin(9600);

  //Humidade do solo
  pinMode(analogi,  INPUT);
  pinMode(digital,  INPUT);
  pinMode(gnd_pin, OUTPUT);
  pinMode(vcc_pin, OUTPUT);
  digitalWrite(gnd_pin,  LOW);
  digitalWrite(vcc_pin, HIGH);

  //temperatura do solo
  sensors.begin();

  //LÂMPADA
  pinMode(portaRele, OUTPUT);

  //BUZZER
  pinMode (buzzer, OUTPUT);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Hora, Humidade do solo , Temperatura do solo(C), Humidade do ar (%), Temperatuta do ar (C), Linha");

}


void loop() {
  linha++;
  
  solo();
  dados(); //imprime os dados
  delay(2000);
}
void dados() {
  Serial.print("DATA,TIME,");
  Serial.print( humsolo, 1 );
  Serial.print(",");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(",");
  Serial.println(linha);

}
void solo() {
  //humidade do solo
  humsolo = analogRead(analogi);

  //temperatura do solo
  sensors.requestTemperatures(); // Send the command to get temperature readings


}




