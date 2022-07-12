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
//☠☠☠☠☠☠☠Realy☠☠☠☠☠☠☠☠☠☠
#define pinRelay A0           // Salida del Relay
//☠☠☠☠☠☠☠Sensor☠☠☠☠☠☠☠☠☠
#define Sensor 7              //Pin del Senso
//☠☠☠☠☠☠☠LCD I2C☠☠☠☠☠☠☠☠☠

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Variables☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
typedef int TaskProfiler;
TaskProfiler TimerProfiler;

unsigned int cycles = 0;   // Variable que guarda los ciclos (dando un rango útil de 0 a 65,535 ciclos)
int timer;                 //Tiempo que mostrara la pantalla LCD
uint32_t tiempoTemp = 10;  //Valor del temporizador del timer predeterminado

bool doorPosition;
bool EstadoPuerta;
enum ESTADO_PUERTA{
     Puerta_Cerrada,       //Valor booleano 0 asignado a la Puerta Cerrada
     Puerta_Abierta        //Valor booleano 1 asignado a la Puerta Aberta
   };


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
              100,
              NULL,
              1,
              &timer_Handle);
  xTaskCreate(Relay_Task,
              "RELAY TASK",
              100,
              NULL,
              1,
              &relay_Handle); 
  xTaskCreate(Sensor_Task,
              "SENSOR TASK",
              100,
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

void Relay_Task(void *pvParameters)
{
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW);
  vTaskDelay(100);
  digitalWrite(pinRelay, HIGH);
}

void Sensor_Task(void *pvParameters){
  pinMode(Sensor, INPUT);
  while(1){
    doorPosition = digitalRead(Sensor);
    Serial.print(" / DOOR POSITION : ");
    if(doorPosition == Puerta_Cerrada)
     {
      Serial.print("Door Closed / ");
      if(EstadoPuerta == false)
      {
        cycles++;
        EstadoPuerta = true;
      }
     }
     else
     {
      Serial.print("Door Opened / ");
      EstadoPuerta = false;
     }
    Serial.print("#CYCLES : ");
    Serial.println(cycles); 
    vTaskDelay(100);
  }
}

  



void loop(){}
