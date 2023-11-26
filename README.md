# ESP32-MQTT
  INSTITUTO FEDERAL DO ESPÍRITO SANTO
 
  Trabalho para avaliação da disciplina Comunicação de Dados 2023/2. 

## ESPECIFICAÇÕES
    1. Utilizando um ESP 32 ou arduíno com conexão de rede TCP/IP montar um dispositivo 
    com um sensor de temperatura e umidade que realize medidas de minuto a minuto;
    
    2. A cada medida o dispositivo de publicar o dado  medido no seguinte formato[{data-hora} { Temperatura C} {Umidade %}];
    
    3. Os dados serão publicados na nuvem usando o serviço MQTT (https://www.hivemq.com/)
    
    4. O formato do dado publicado deve ser:  data-hora = DD/MM/AA;

    5. Um software separado do dispositivo deve se capaz de plotar e apresentar o gráfico das medidas realizadas;
