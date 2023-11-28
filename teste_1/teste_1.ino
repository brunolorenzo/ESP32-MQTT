/*
  Bruno Lorenzo Thomaz Marques
  INSTITUTO FEDERAL DO ESPIRITO SANTO - SERRA ES
  
  Trabalho para avaliação da disciplina Comunicação de Dados 2023/2
  Professor: Maxwell Eduardo Monteiro
*/

// BIBLIOTECAS:
#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <time.h>

// SENSOR
//#define DHTPIN ALTERAR

// REDE WIFI
const char *ssid = "Brunorca2002";
const char *password = "br167901"; 

// MQTT Broker
const char *mqtt_broker = "broker.hivemq.com";
const char *topic = "teste/teste1";
const char *mqtt_username = "brunocod";
const char *mqtt_password = "Br12kl345";
const int mqtt_port = 1883;

// FUSO-HORÁRIO
long fuso_horario = -3;
byte horario_verao = 1;


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    
    //CONECTAR A REDE WIFI:
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("tentando conectar ao WiFi..");
    }
    Serial.println("Conectado a rede WiFi");
    
    //CONECTANDO AO MQTT Broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf(" %s Conectando ao MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("CONECTADO.");
        } else {
            Serial.print("FALHA: ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // Publica e Inscreve-se
    client.publish(topic, "Olá eu sou a ESP32.");
    client.subscribe(topic);

    configTime(3600 * fuso_horario, horario_verao * 3600, "time.nist.gov", "0.pool.ntp.org", "1.pool.ntp.org");

}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Mensagem recebida do topico: ");
    Serial.println(topic);
    Serial.print("Mensagem:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}
int i = 0;

void loop() {

    struct tm tmstruct ;

    tmstruct.tm_year = 0;
    getLocalTime(&tmstruct);

    String date = (String(tmstruct.tm_mday)+ "/" + String(( tmstruct.tm_mon) + 1) + "/" + ((tmstruct.tm_year) -100));
  
    String hour = (String(tmstruct.tm_hour) + ":" + String(tmstruct.tm_min) + ":" + String(tmstruct.tm_sec));

    Serial.println("Date: " + date + " - Time: " + hour);


    i += 1;
    client.loop();
    delay(1000);
    client.publish(topic, (String(i).c_str()));
}
