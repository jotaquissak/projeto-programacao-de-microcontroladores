// Carrega a Biblioteca LiquidCrystal
#include <LiquidCrystal_I2C.h>
// Carrega a Biblioteca Wire.h
#include <Wire.h>

// Define os pinos que serão utilizados para ligação ao display
LiquidCrystal_I2C lcd(32, 16, 2);

// Variáveis

int SensorTempPino=0;
int porcem=0;


// Define o pino 3 para o alerta de temperatura baixa
int AlertaTempAlta=3;
// Define o pino 2 para o alerta de temperatura alta
int AlertaTempSuperAlta=2;

// Define temperatura alta como acima de 40 graus Celsius
int TempAlta=40;
// Define temperatura super alta como acima de 50 graus Celsius
int TempSuperAlta=50;

// Define os pinos 2 e 3 para os Leds
const int ledVermelho = 2;
const int ledAmarelo = 3;

// Define variaveis de alarme e emergência
bool alarm = false;
bool emergency = false;
bool mostrarMensagemAlerta = false;
unsigned long ultimoTempo = 0;
const unsigned long intervalo = 2000;


void setup() 
{
  
  // Informa se os pinos dos LEDs são de entrada ou saída
  pinMode(AlertaTempAlta, OUTPUT);  
  pinMode(AlertaTempSuperAlta, OUTPUT);
	
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
  
  // Define LCD 16 colunas por 2 linhas
  lcd.begin(16,2);
  lcd.clear();
  
  //Posiciona o cursor na coluna 0, linha 0;
  lcd.setCursor(0,0);
  
  // Imprime a mensagem no LCD
  lcd.print("  Temperatura:  ");
  
  // Muda o cursor para a primeira coluna e segunda linha do LCD
  lcd.setCursor(0,1);
  
  // Imprime a mensagem no LCD
  lcd.print("          C     ");

  // Inicialização dos Leds
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
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
  
  // Estrutura condicional de temperatura alta e super alta
  	if (TemperaturaC>=AlertaTempAlta && TemperaturaC < AlertaTempSuperAlta) {
  		digitalWrite(AlertaTempAlta, HIGH);
  		digitalWrite(ledAmarelo, HIGH);
  		digitalWrite(AlertaTempSuperAlta, LOW);
  		digitalWrite(ledVermelho, LOW);
      alarm = true;
      emergency = false;

    }
  	else if (TemperaturaC>AlertaTempSuperAlta) {
  		digitalWrite(AlertaTempAlta, LOW);
  		digitalWrite(ledAmarelo, LOW);
  		digitalWrite(AlertaTempSuperAlta, HIGH);
  		digitalWrite(ledVermelho, HIGH);
      alarm = false;
      emergency = true;

  	}
  	else {
  		digitalWrite(AlertaTempAlta, LOW);
  		digitalWrite(ledAmarelo, LOW);
  		digitalWrite(AlertaTempSuperAlta, LOW);
  		digitalWrite(ledVermelho, LOW);
      alarm = false;
      emergency = false;

    }

  // Troca de mensagens a cada 5 segundos 
  if (millis() - ultimoTempo >= intervalo) {
    lcd.clear();
    if ((alarm || emergency) && mostrarMensagemAlerta) {
      lcd.setCursor(0, 0);
      if (emergency) {
        lcd.print("EMERGENCIA!");
      } else {
        lcd.print("ALARME!");
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("  Temperatura:  ");
      lcd.setCursor(0,1);
      lcd.print("          C     ");
      lcd.setCursor(5,1);
      lcd.print(TemperaturaC);
    }

    mostrarMensagemAlerta = !mostrarMensagemAlerta;
    ultimoTempo = millis();
  }
}
