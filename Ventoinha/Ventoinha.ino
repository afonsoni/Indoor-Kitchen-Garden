/*Pinagem do arduino*/
/*
//motor_A
int IN1 = 7 ;
int IN2 = 8 ;
int velocidadeA = 9; //PWM
*/
//motor_B
int IN3 = 8 ;
int IN4 = 7 ;
int velocidadeB = 9; //PWM

//variavel auxiliar
int velocidade = 0; 
 
//Inicializa Pinos
void setup(){
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(velocidadeA,OUTPUT);
pinMode(velocidadeB,OUTPUT);
}

void loop(){
 
/*Exemplo de velocidades no motor A 
 
//Sentido 2
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);


analogWrite(velocidadeA, 250);
*/

//Exemplo de variacao de velocidade no motor B
 
//Sentido 2
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 

analogWrite(velocidadeB, 250);
}
