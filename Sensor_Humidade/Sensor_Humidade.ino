#define sensorHumidade A1 // Sensor de humidade de solo do módulo
unsigned long tempoAnterior = 0; // Variável utilizada para guardar o tempo anterior
unsigned long intervalo = 1000; // Intervalo de tempo em MS para cada leituraa
void setup() {
  Serial.begin(9600); // Inicialização da comunicação serial
 
}
void loop() {
  unsigned long tempoAtual = millis(); // Realizamos a leitura atual do tempo em que o nosso Arduino Nano está ligado
  if (tempoAtual-tempoAnterior > intervalo){ // Pequena lógica para realizar leituras temporizadas sem parar o microcontrolador
      tempoAnterior =tempoAtual; // Guardamos o tempo anterior como o ultimo intervalo de tempo lido
      int leitura = analogRead(sensorHumidade); // Leitura dos dados analógicos vindos do sensor de umidade de solo
 
      if (leitura<=1023 && leitura>=500){ // Se a leitura feita for um valor entre 1023 e 682 podemos definir que o solo está com uma baixa condutividade, logo a planta deve ser regada
        Serial.print("Nível de Humidade Alto: ");
        Serial.println(leitura);
      }else{
        if (leitura<=500 && leitura>=250){ // Se a leitura feita for um valor entre 681 e 341 podemos definir que o solo está com um nível médio de humidade, logo dependendo da planta pode ou não ser vantajoso regar
        Serial.print("Nível de Humidade Médio: ");
        Serial.println(leitura);
        }
        else{
          if (leitura<=250 && leitura>=0){ // Se a leitura feita for um valor entre 0 e 340 podemos definir que o solo está com um nível aceitável de humidade, logo talvez não seja interessante regar neste momento
            Serial.print("Nível de Humidade Baixo: ");
            Serial.println(leitura);
          }
        } 
      }
  }
}
