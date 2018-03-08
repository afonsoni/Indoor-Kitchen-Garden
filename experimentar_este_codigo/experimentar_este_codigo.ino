#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

//excel
int linha = 0;
int LABEL = 1;



//HUMIDADE E TEMPERATURA DO AR
dht DHT;
#define DHT22_PIN 12
struct
{
  uint32_t total;
  uint32_t ok;
  uint32_t crc_error;
  uint32_t time_out;
  uint32_t connect;
  uint32_t ack_l;
  uint32_t ack_h;
  uint32_t unknown;
} stat = { 0, 0, 0, 0, 0, 0, 0, 0};

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
  ar();
  solo();
  dados(); //imprime os dados
  controlar();
  delay(3000);
}
void dados() {
  Serial.print("DATA,TIME,");
  Serial.print( humsolo, 1 );
  Serial.print(",");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(",");
  Serial.print(DHT.humidity, 1);
  Serial.print(",");
  Serial.print(DHT.temperature, 1);
  Serial.print(",");
  Serial.println(linha);

}
void solo() {
  //humidade do solo
  humsolo = analogRead(analogi);

  //temperatura do solo
  sensors.requestTemperatures(); // Send the command to get temperature readings


}

void ar() {
  int chk = DHT.read22(DHT22_PIN);
  stat.total++;

  switch (chk)
  {
    case DHTLIB_OK:
      stat.ok++;

      break;
    case DHTLIB_ERROR_CHECKSUM:
      stat.crc_error++;

      break;

    case DHTLIB_ERROR_CONNECT:
      stat.connect++;

      break;
    case DHTLIB_ERROR_ACK_L:
      stat.ack_l++;

      break;
    case DHTLIB_ERROR_ACK_H:
      stat.ack_h++;

      break;
    default:
      stat.unknown++;

      break;
  }





}

void controlar() {
  //humsolo é a humidade do solo
  //DHT.temperature DHT.humidity (AR)
  //ISTO DEPOIS TENHO DE CONTROLAR COM OS VALORES DA TEMPERATURA/HUMIDADE
  //A VARIAVEL QUE CONTROLA A VELOCIDADE DA VENTOINHA É A PWMVal

  //                              VENTOINHA
  //-----------------------------------------------------------------------

  if (DHT.humidity > 40, 0 ) {
    sensorVal = 800;
    PWMVal = map(sensorVal, 450, 800, 26, 255);
    analogWrite(PWM, PWMVal);

    delay(2000);
    erro = DHT.humidity - K ;
  } else {
    PWMVal = 0;
  }


  PWMVal = erro * K;

  if (PWMVal < 0) {
    PWMVal = 0;
  } else {
    PWMVal = erro * K;
  }
  delay (1000);
  analogWrite(PWM, PWMVal);

  //-------------------------------------------------------------------------
  //                            LÂMPADA
  if (DHT.temperature <= 25, 0) {
    digitalWrite(portaRele, LOW); // liga a lâmpada
  } else {
    digitalWrite(portaRele, HIGH);
  }
  //-------------------------------------------------------------------------
  //                             BUZZER
  // if (condição){
  tone(10, 300, 300);

}


