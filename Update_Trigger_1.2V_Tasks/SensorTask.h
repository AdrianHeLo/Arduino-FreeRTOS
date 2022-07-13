//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Librerias☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
#include <Arduino_FreeRTOS.h>

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠DefiniciondePines☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠Sensor☠☠☠☠☠☠☠☠☠
#define Sensor 7           //Pin del Sensor

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Variables☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
unsigned int cycles = 0;   // Variable que guarda los ciclos (dando un rango útil de 0 a 65,535 ciclos)

bool doorPosition;
bool EstadoPuerta;
enum ESTADO_PUERTA{
     Puerta_Cerrada,       //Valor booleano 0 asignado a la Puerta Cerrada
     Puerta_Abierta        //Valor booleano 1 asignado a la Puerta Aberta
   };


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
