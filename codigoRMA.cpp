// codigoRMA.cpp
// 14/11/2023

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 4        // Pino conectado ao DHT11
#define DHTTYPE DHT11   // Tipo do sensor DHT (DHT11 ou DHT22)

DHT dht(DHTPIN, DHTTYPE);

#define MQ_PIN 25       // Pino analógico ao qual o sensor MQ-2 está conectado


void setup() {
  dht.begin();
  Serial.begin(9600);
  Serial.begin(9600, SERIAL_8N1, 3, 1); // Inicialização do serial para que o ESP envie as informações ao LoRa, e ao TTN - (RX0 - 3 | TX0 - 1)

  Serial.println("AT+JOIN");            // Antes do loop(), o ESP32 tentará fazer a conexão com o TTN a partir do AT+JOIN
  delay(10000);
  Serial.println("AT+JOIN");
  delay(10000);

  Serial.setDebugOutput(false);

}

void loop() {
  // Leitura das informações de temperatura, umidade e gases
  static const float temperature = dht.readTemperature();       // DHT11 - Temperatura
  static const float humidity = dht.readHumidity();             // DHT11 - Umidade
  static const uint16_t mqValue = analogRead(MQ_PIN);           // MQ2

  Serial.println(enviaDados(gas, humidity, temperature));       // Exibe os valores no monitor serial e para o TTN
  delay(5000);     
  
}

String enviaDados(String dado1, String dado2, String dado3) // Função que recebe como parâmetro em string() a variável do valor do sensor e envia para o server TTN
{
    static const String dadoTotal = dado1 + ";" + dado2 + ";" + dado3;
    return dadoTotal;
}