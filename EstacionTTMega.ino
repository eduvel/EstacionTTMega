
#include "manejoSensores.h"
#include "tramaMQTT.h"


MQTT moduloGPRS(3, 10);
void setup() {
	moduloGPRS.powerOn();
	inicioSensores();
	moduloGPRS.iniciarSerialSIM900();
	Serial.println("Iniciando");
}

void loop() {
  if(tiempoMedicion(900)){
    String tramaEnviar =medicionSensores();
    Serial.println(tramaEnviar);
	moduloGPRS.enviarTramaMQTT(tramaEnviar);
  }
  if (Serial.available() > 0) {
	  if (Serial.read() == 'L')
		  LeerRegistro();
  }
}
