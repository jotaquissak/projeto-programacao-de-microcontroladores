// Carrega a Biblioteca LiquidCrystal
#include <LiquidCrystal_I2C.h>

// Define os pinos que serão utilizados para ligação ao display
LiquidCrystal_I2C lcd(32, 16, 2);

// Variáveis

int SensorTempPino=0;
int porcem=0;


// Define o pino 8 para o alerta de temperatura baixa
int AlertaTempBaixa=3;
// Define o pino 13 para o alerta de temperatura alta
int AlertaTempAlta=2;

// Define temperatura baixa como abaixo de zero grau Celsius
int TempBaixa=0;
// Define temperatura alta como acima de 40 graus Celsius
int TempAlta=50;


void setup() 
{
  
  // Informa se os pinos dos LEDs são de entrada ou saída
  pinMode(AlertaTempBaixa, OUTPUT);  
  pinMode(AlertaTempAlta, OUTPUT);
	
  // Define LCD 16 colunas por 2 linhas
  lcd.begin(16,2);
  
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  //Posiciona o cursor na coluna 0, linha 0;
  lcd.setCursor(0,0);
  
  // Imprime a mensagem no LCD
  lcd.print("  Temperatura:  ");
  
  // Muda o cursor para a primeira coluna e segunda linha do LCD
  lcd.setCursor(0,1);
  
  // Imprime a mensagem no LCD
  lcd.print("          C     ");
  
  Serial.begin(9600);
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
   lcd.setCursor(5,1);

   // Imprime a temperatura em Graus Celsius
   lcd.print(TemperaturaC);     
  
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