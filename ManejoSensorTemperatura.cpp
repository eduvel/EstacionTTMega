#include "ManejoSensorTemperatura.h"


SensorDS18B20::SensorDS18B20(OneWire *oneWire){
  OneWireBus=oneWire;
}

void SensorDS18B20::InicioDS18B20(void){
  //OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
  sensors.setOneWire(OneWireBus);  
  sensors.begin(); //Se inician los sensores de temperatura
  Serial.println(F("Iniciando oneWire!"));
};

float SensorDS18B20::getTemperatura(){
      //String Valor;
      //sensors.requestTemperatures(); //Prepara el sensor para la lectura
	  sensors.requestTemperatures();//ByIndex(0);
      //Valor=sensors.getTempCByIndex(0);
      float temp=sensors.getTempCByIndex(0);
      return temp;

 
};
