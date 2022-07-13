//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Librerias☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
#include <Arduino_FreeRTOS.h>

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠DefiniciondePines☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠Realy☠☠☠☠☠☠☠☠☠☠
#define pinRelay A0           // Salida del Relay


void Relay_Task(void *pvParameters)
{
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW);
  vTaskDelay(75);
  digitalWrite(pinRelay, HIGH);
}
