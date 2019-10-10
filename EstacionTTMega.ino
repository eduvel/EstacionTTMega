
#include "manejoSensores.h"



void setup() {
 inicioSensores();
 
 Serial.println("Iniciando");
}

void loop() {
  if(tiempoMedicion(10))
    Serial.println(medicionSensores());
 
}




   
    
