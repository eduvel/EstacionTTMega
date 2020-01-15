
#include "manejoSensores.h"
#include "tramaMQTT.h"

int cicloTransmision = 0;
MQTT moduloGPRS(3, 10);
void setup() {
	moduloGPRS.powerOn();
	inicioSensores();
	moduloGPRS.iniciarSerialSIM900();
	Serial.println("Iniciando");
}

void loop() {
  if(tiempoMedicionMillis(900)){
    String tramaEnviar =medicionSensores();
    Serial.println(tramaEnviar);
	cicloTransmision++;
	if (cicloTransmision >= 2) {
		moduloGPRS.enviarTramaMQTT(tramaEnviar);
		cicloTransmision = 0;
	}
  }
  if (Serial.available() > 0) {
	  if (Serial.read() == 'L')
		  LeerRegistro();
  }
}
