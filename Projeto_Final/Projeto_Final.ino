#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <LiquidCrystal.h>

#define sensorHumidade A1 //Humi
#define ONE_WIRE_BUS 2 //Temp
#define DHTPIN 4 //Ar
#define DHTTYPE DHT22 //Ar


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

//Variaveis projeto

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


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 3
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DHT dht(DHTPIN, DHTTYPE);

//motor ventoinha
int IN1 = 7;
int IN2 = 8 ;
int velocidadeA = 9; //PWM

/*
//motor água (se arranjarmos isso)
int IN3 = 13;
int IN4 = 12;
int velocidadeB = 11; //PWM
*/
int velocidade = 0;

int leitura;
float h;
float t;

void setup()
{
  pinMode(3, OUTPUT); //buzzer
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  //pinMode(IN3,OUTPUT);
  //pinMode(IN4,OUTPUT);
  pinMode(velocidadeA,OUTPUT);
  //pinMode(velocidadeB,OUTPUT);
  
  Serial.begin(9600);
  dht.begin();
  sensors.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);             
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.println("INDOOR KITCHEN");
  lcd.setCursor(5,1);
  lcd.println("GARDEN");
  Serial.println("Indoor Kitchen Garden");
  delay(500);
  Serial.println("Início");
  delay(1000);
}

void getHumidity()
{
  leitura = analogRead(sensorHumidade);
  // Leitura dos dados analógicos vindos do sensor de humidade de solo
}
  
void getTemperature()
{
  sensors.requestTemperatures();
  // Send the command to get temperature readings
}
  
void getAirHnT()
{
  // A leitura da temperatura e humidade pode levar 250ms
  // O atraso do sensor pode chegar a 2 segundos.
  h = dht.readHumidity();
  t = dht.readTemperature();
}

void loop()
{
  getAirHnT();
  getTemperature();
  getHumidity();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print(h); //humi air
    Serial.print(";");
    Serial.print(t); //temp air
    Serial.print(";");
    Serial.print(sensors.getTempCByIndex(0)); //temp solo
    // Porquê "byIndex"?  
    // Pode haver mais do que um DS18B20
    // 0 representa o primeiro sensor
    Serial.print(";");
    Serial.print(leitura); //humi solo
    Serial.print(";");
  }
    lcd_key = read_LCD_buttons();   // ´lê os botões

   switch (lcd_key){               // tem uma ação dependendo do botão

       case btnUP:{    //  TEMPERATURA AR
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("TEMPERATURA AR:");
            lcd.setCursor(0,1);
            lcd.print(t);
            lcd.print(" ºC");
            break;
       }
       
       case btnRIGHT:{     //HUMIDADE SOLO
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("HUMIDADE SOLO:"); 
             lcd.setCursor(0,1);
             lcd.print(leitura);
             lcd.print("%");
             break;
       }    
       
       case btnLEFT:{       //TEMP SOLO
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("TEMP SOLO:");
            lcd.setCursor(0,1);
            lcd.print(sensors.getTempCByIndex(0));
            lcd.print(" ºC");
            break;
       }
       
       case btnDOWN:{  //Humidade Ar
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("HUMIDADE AR:");
             lcd.setCursor(0,1);
             lcd.print(h);
             lcd.print("%");
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
        delay(1000);
        lcd.clear();
       } 
   }      
  
  

  
}
