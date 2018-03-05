/*Pinagem do arduino*/

 

//motor_A

int IN1 = 6;

int IN2 = 7;

int velocidadeA = 5;

#include <LiquidCrystal.h>

//Variaveis LCD

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

    // botoes quando lidos rondam estes valores respetivamente : 0, 144, 329, 504, 741
    // + 50 aprox para ver se os valroes se aproximavam das leituras
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 
/*
    // For V1.1 us this threshold. nao usamos devido aos valores detetados não estarem aprox a estes..
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  */

   // For V1.0 comment the other threshold and use the one below: usamos este devido aos valores serem mais precisos
   
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   
   
      return btnNONE;                // quando todos os botoes falharem retorna...
}


#include <OneWire.h>

#include <DallasTemperature.h>

#include "DHT.h"


#define sensorHumidade A1 // HUmidade

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
//VENTOINHA 
pinMode(IN1,OUTPUT);

pinMode(IN2,OUTPUT);

pinMode(velocidadeA,OUTPUT);
 


  Serial.begin(9600);

  dht.begin();

  sensors.begin();

  Serial.println("Indoor Kitchen Garden");

   lcd.begin(16, 2);               
   lcd.setCursor(0,0);             
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.println(" INDOOR KITCHEN ");
   lcd.setCursor(0,1);
   lcd.println(" GARDEN       ");

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

  Serial.print("     ");

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

    Serial.println("     ");

  }

  

  else

  {

     if (leitura<=500 && leitura>=250)

     {

       // Se a leitura feita for um valor entre 681 e 341 podemos definir que o solo está com um nível médio de humidade, logo dependendo da planta pode ou não ser vantajoso regar

       Serial.print("Nível de Humidade Médio: ");

       Serial.print(leitura);

       Serial.println("     ");

     }

     else

     {

        if (leitura<=250 && leitura>=0)

        {

           // Se a leitura feita for um valor entre 0 e 340 podemos definir que o solo está com um nível aceitável de humidade, logo talvez não seja interessante regar neste momento

           Serial.print("Nível de Humidade Baixo: ");

           Serial.print(leitura);

           Serial.println("     ");

        }

     } 

   }

   }



  //Sensor Humidade Terra ^^

  delay(500);

//LCD DISPLAY BUTTONS

  lcd_key = read_LCD_buttons();   // ´lê os botões

   switch (lcd_key){               // tem uma ação dependendo do botão

       case btnUP:{    //  
            lcd.clear();
            lcd.setCursor(0,0);
          
            break;
       }
       
       case btnRIGHT:{     //
             lcd.clear();
           
             break;
       }    
       
       case btnLEFT:{       // 
            lcd.clear();
        
             
             break;
       }
       
       case btnDOWN:{  //
             lcd.clear();
             
             break;
                    
       }
       
     case btnSELECT:{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.println(" COME AGAIN SOON");
        lcd.setCursor(0,1);
        lcd.println("   WAITING 4U   ");
        delay(1000);
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("BYEEE CLASS");
        break;
       } 
   } 
 //VENTOINHA
//Sentido 2

digitalWrite(IN1,HIGH);

digitalWrite(IN2,LOW);

analogWrite(velocidadeA, 255);

delay(50);




}
