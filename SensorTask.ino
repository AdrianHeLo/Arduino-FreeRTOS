//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠DefiniciondePines☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠Sensor☠☠☠☠☠☠☠☠☠
#define Sensor 7              //Pin del Senso

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠Variables☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
unsigned int cycles = 0;   // Variable que guarda los ciclos (dando un rango útil de 0 a 65,535 ciclos)

bool sensorLectura;
bool sensorOld;
bool doorPosition;
bool EstadoPuerta;
enum ESTADO_PUERTA{
     Puerta_Cerrada,       //Valor booleano 0 asignado a la Puerta Cerrada
     Puerta_Abierta        //Valor booleano 1 asignado a la Puerta Aberta
   };

TaskHandle_t sensor_Handle;

void setup() {
  // put your setup code here, to run once:
xTaskCreate(Sensor_Task,
              "SENSOR TASK",
              1024,
              NULL,
              1,
              &sensor_Handle);
}

void Sensor_Task(void *pvParameters){
  pinMode(Sensor, INPUT);
  while(1){
    sensorLectura = digitalRead(Sensor);
    sensorOld = sensorLectura;
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

void loop() {
  // put your main code here, to run repeatedly:

}
