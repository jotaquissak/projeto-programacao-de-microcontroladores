// Carrega a Biblioteca LiquidCrystal
#include <LiquidCrystal.h>

// Define os pinos que serão utilizados para ligação ao display
LiquidCrystal LCD(12,11,5,4,3,2);

// Variáveis

int SensorTempPino=0;
int SensorUmidPino=1;
int porcem=0;


// Define o pino 8 para o alerta de temperatura baixa
int AlertaTempBaixa=8;
// Define o pino 13 para o alerta de temperatura alta
int AlertaTempAlta=13;

// Define temperatura baixa como abaixo de zero grau Celsius
int TempBaixa=0;
// Define temperatura alta como acima de 40 graus Celsius
int TempAlta=23;


void setup() 
{
  // Informa se os pinos dos LEDs são de entrada ou saída
  pinMode(AlertaTempBaixa, OUTPUT);  
  pinMode(AlertaTempAlta, OUTPUT);
	
  // Define LCD 16 colunas por 2 linhas
  LCD.begin(16,2);
  
  //Posiciona o cursor na coluna 0, linha 0;
  LCD.setCursor(0,0);
  
  // Imprime a mensagem no LCD
  LCD.print("  Temperatura:  ");
  
  // Muda o cursor para a primeira coluna e segunda linha do LCD
  LCD.setCursor(0,1);
  
  // Imprime a mensagem no LCD
  LCD.print("          C     ");
  
}

void loop()
{
   // Faz a leitura da tensao no Sensor de Temperatura
   int SensorTempTensao=analogRead(SensorTempPino);

   // Converte a tensao lida
   float Tensao=SensorTempTensao*5;
   Tensao/=1024;

   // Converte a tensao lida em Graus Celsius
   float TemperaturaC=(Tensao-0.5)*100;

   // Muda o cursor para a primeira coluna e segunda linha do LCD
   LCD.setCursor(5,1);

   // Imprime a temperatura em Graus Celsius
   LCD.print(TemperaturaC);     
  
  // Acende ou apaga os alertas luminosos de temperatura baixa e alta
  	if (TemperaturaC>=TempAlta) {
  		digitalWrite(AlertaTempBaixa, LOW);
  		digitalWrite(AlertaTempAlta, HIGH);
    }
  	else if (TemperaturaC<=TempBaixa) {
  		digitalWrite(AlertaTempBaixa, HIGH);
  		digitalWrite(AlertaTempAlta, LOW);
  	}
  	else {
  		digitalWrite(AlertaTempBaixa, LOW);
  		digitalWrite(AlertaTempAlta, LOW);
    }

  // Aguarda 1 segundo
  	delay(1000);
}  
  
   
   
 
   