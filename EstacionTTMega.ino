
#include "manejoSensores.h"



void setup() {
 inicioSensores();
 
 


}

void loop() {
  if(tiempoMedicion(10))
    Serial.println(medicionSensores());
}




   
    
