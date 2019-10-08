#include <OneWire.h> //Se importan las librerías
#include <DallasTemperature.h>

class SensorDS18B20{
  public:
  SensorDS18B20(OneWire *oneWire);
  float getTemperatura();
  void InicioDS18B20();
  private:
  DallasTemperature sensors;
  OneWire *OneWireBus;
};
