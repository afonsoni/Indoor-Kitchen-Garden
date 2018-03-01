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

void setup()
{
  Serial.begin (9600);
  lcd.begin(16, 2);               
  lcd.setCursor(0,0);             
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.println(" VELOZES    E   ");
   lcd.setCursor(0,1);
   lcd.println(" FURIOSOS       ");
}

void loop()
{  
   lcd_key = read_LCD_buttons();   // ´lê os botões

   switch (lcd_key){               // tem uma ação dependendo do botão

       case btnUP:{    //  velocidade máxima
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Top Speed:      ");
            lcd.setCursor(0,1);
            lcd.println(velomaxima);
            lcd.setCursor(6,1);
            lcd.println("Km/h      ");
            break;
       }
       
       case btnRIGHT:{     //  calorias
             lcd.clear();
             lcd.print("Calorias:       "); 
             lcd.setCursor(0,1);
             lcd.print(calo);
             lcd.setCursor(5,1);
             lcd.print("cal         ");
             break;
       }    
       
       case btnLEFT:{       //  distância
            lcd.clear();
            lcd.print("Dist.perc.: ");  
             if (distancia > 0){
                lcd.setCursor(0,1);
                lcd.println(distancia);
                lcd.setCursor(4,1);
                lcd.println("KM          ");
             } else {
              lcd.setCursor(0,1);
              lcd.print("0");
              lcd.setCursor(7,1);
              lcd.println("KM       ");
             }
             break;
       }
       
       case btnDOWN:{  // Velocidade instantanea
             lcd.clear();
             lcd.print("Velocidade ");
             lcd.setCursor(0,1);
             lcd.print(velocidade);
             lcd.setCursor(7,1);
             lcd.print("km/h");
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
       } 
   }      
   
}
}
