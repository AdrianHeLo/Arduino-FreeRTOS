#include <Arduino_FreeRTOS.h>

#define RED 6
#define BLUE 7
#define YELLOW 8

typedef int TaskProfiler;
TaskProfiler RedLedProfiler;
TaskProfiler BlueLedProfiler;
TaskProfiler YellowLedProfiler;

//PREGUNTAS: 
//¿Es una conversion lo de uint16_t* red?
//¿El uint16_t siempre es lo recomendable de usar? si es si, ¿Por qué?
//En el xTaskCreate, ¿El (void *) representa la const uint16_t *red?


//uint8_t = 0 - 255 bytes / uint16_t = 0 - 255 bytes / uint32_t = 0 - 255 bytes / uint64_t = 0 - 255 bytes /

const uint16_t *red = (uint16_t *) RED;
const uint16_t *blue = (uint16_t *) BLUE;
const uint16_t *yellow = (uint16_t *) YELLOW;

void setup() {
  // put your setup code here, to run once:
  xTaskCreate(ledControllerTask,       //TaskFunction_t pvTaskCode   
              "RED LED TASK",          //const char * const pcName
              100,                     //uint16_t usStackDepth    
              (void *)red,             //void *pvParameters
              1,                       //UBaseType_t uxPiority
              NULL);                   //TaskHandle_t *pxCreateTask
  xTaskCreate(ledControllerTask,"BLUE LED TASK", 100, (void *)blue, 1, NULL);  
  xTaskCreate(ledControllerTask, "YELLOW LED TASK", 100, (void *)yellow, 1, NULL);     
}

void ledControllerTask(void *pvParameters){
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  while(1){
      digitalWrite(pvParameters, digitalRead(pvParameters)^1);
    }
}



void loop(){}
