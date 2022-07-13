//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Ficheros☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
#include "RelayTask.h"
#include "SensorTask.h"

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Librerias☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal_I2C.h>
#include<Wire.h>
#include <EEPROM.h>
#include <SPI.h>
#include <SD.h>

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠DefiniciondePines☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠


//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Variables☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
typedef int TaskProfiler;
TaskProfiler TimerProfiler;

//unsigned int cycles = 0;   // Variable que guarda los ciclos (dando un rango útil de 0 a 65,535 ciclos)
int timer;                 //Tiempo que mostrara la pantalla LCD
uint32_t tiempoTemp = 10;  //Valor del temporizador del timer predeterminado

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Tasks☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
TaskHandle_t relay_Handle, sensor_Handle, botonArriba_Handle, botonAbajo_Handle, botonPause_Handle, botonReiniciar_Handle, timer_Handle, restartTimer_Handle, timerTemp_Handle;

const TickType_t xTicketToWait = pdMS_TO_TICKS(1000);

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠SetUp☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xTaskCreate(Timer_Task,
              "TIMER TASK",
              1024,
              NULL,
              1,
              &timer_Handle);
  xTaskCreate(Relay_Task,
              "RELAY TASK",
              1024,
              NULL,
              1,
              &relay_Handle); 
  xTaskCreate(Sensor_Task,
              "SENSOR TASK",
              1024,
              NULL,
              1,
              &sensor_Handle); 
}


//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠CallbackTasks☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
void Timer_Task(void *pvParameters)
 {
  for(;;)
  {
   tiempoTemp--;
   Serial.print("RUN TIME : ");
   Serial.print(tiempoTemp);
   
   if(tiempoTemp <= 0)
      {
        tiempoTemp = 10; 
        vTaskResume(relay_Handle);
      }
      else
      {
        vTaskSuspend(relay_Handle);
      }  
   vTaskDelay(100);
  }
 }


void loop(){}
