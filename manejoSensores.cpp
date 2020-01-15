#include "manejoSensores.h"
SoftwareSerial MySerial(8, 9); // RX, TX

float fHumedadAmbiente=20.0;
float fHumedadSuelo=20.0;
float fHumedadSueloCH=20.0;
float fTemperaturaAmbiente=25.0;
float fTemperaturaDS=25.0;
float fRadiacionV=0.0;
float fRadiacionGlobal=0.0;
float fSensorHidricoB=0.0;;
float fSensorViento=0.0;
float fSensorLluvia=0.0;
float fSensorPH=7.0;
int cViento;
uint32_t TiempoUnixBase =0;
uint32_t TiempoUnix=0;
uint32_t TiempoMillisBase = 0;
uint32_t TiempoMillis = 0;
Registro Dato;

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;
OneWire ourWire1(5);
SensorDS18B20 sensorTemperatura1(&ourWire1);
void inicioSensores(){
  pinMode(CS_SD, OUTPUT);
  digitalWrite(CS_SD, HIGH);
  pinMode(RFM95_CS, OUTPUT);
  digitalWrite(RFM95_CS, HIGH);
  pinMode(ActivacionSensorH, OUTPUT);
  digitalWrite(ActivacionSensorH, LOW);
  Serial.begin(19200);// 9600);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(Tic) ;
  pinMode(Anemometro,INPUT_PULLUP);
  pinMode(Pluviometro,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Anemometro),MedirViento,FALLING);
  attachInterrupt(digitalPinToInterrupt(Pluviometro),MedirLluvia,FALLING);
  dht.begin();
  InicioSD();
  InicioRTC(rtc);
  sensorTemperatura1.InicioDS18B20();
  
  //Dato.sSensorLluvia=0.0;
}
boolean tiempoMedicion(uint16_t Ts){
  
  TiempoUnix = TiempoActualUnix(rtc);
  if (TiempoUnix >= (TiempoUnixBase + Ts )) {
      TiempoUnixBase = TiempoUnix;
      return true;
  }else
    return false;
  
  }
boolean tiempoMedicionMillis(uint32_t Ts) {

	TiempoMillis = millis();
	if ((TiempoMillis - TiempoMillisBase) >= (Ts * 1000)) {
		TiempoMillisBase = TiempoMillis;
		return true;
	}
	else
		return false;

}

String medicionSensores(){
 
      /*Toma de datos temperatura y reloj
    Armado de registro para guardar en SD*/
      String HoraActual=TiempoActualPC(rtc);

      digitalWrite(ActivacionSensorH,HIGH);
      delay(20);
      int valor=analogRead(SensorPH);
      digitalWrite(ActivacionSensorH,LOW);
      fHumedadAmbiente=dht.readHumidity();
      fHumedadSuelo=valor*7/512; //valor a calibrar
      fHumedadSueloCH=analogRead(SensorHumedadCH);
      fTemperaturaAmbiente=dht.readTemperature();
      fTemperaturaDS=sensorTemperatura1.getTemperatura();
      fRadiacionV=analogRead(SensorRadiacionV);
      fRadiacionGlobal=analogRead(SensorRadiacionGlobal);
      fSensorHidricoB=analogRead(SensorHidrico);
      //fSensorViento= fSensorVient;
      //fSensorLluvia=colocar a cero al escribir;
      fSensorPH=analogRead(SensorPH);




    Dato.dataString = HoraActual;
    Dato.sHumedadAmbiente = String(fHumedadAmbiente);
    Dato.sTemperaturaAmbiente = String(fTemperaturaAmbiente);
    Dato.sHumedadSueloCH = String(fHumedadSueloCH);
    Dato.sHumedadSuelo = String(fHumedadSuelo);
    Dato.sTemperaturaDS = String(fTemperaturaDS);
    Dato.sRadiacionV= String(fRadiacionV);
    Dato.sRadiacionGlobal= String(fRadiacionGlobal);
    Dato.sSensorHidricoB = String(fSensorHidricoB);
    Dato.sSensorViento = String(fSensorViento);
    Dato.sSensorLluvia = String(fSensorLluvia);
    Dato.sTemperaturaDS = String(fTemperaturaDS);
    Dato.sSensorPH= String(fSensorPH);
    fSensorLluvia=0;

    Dato.sSensorLluvia = String(fSensorLluvia);
    EscribirRegistro(Dato);
    Serial.println(F("registro escrito"));
    /*return  Dato.dataString+";"+
            Dato.sHumedadAmbiente+";"+
            Dato.sTemperaturaAmbiente+";"+ 
            Dato.sHumedadSueloCH+";"+
            Dato.sHumedadSuelo+";"+
            Dato.sTemperaturaDS+";"+
            Dato.sRadiacionV+";"+
            Dato.sRadiacionGlobal+";"+
            Dato.sSensorHidricoB+";"+
            Dato.sSensorViento+";"+
            Dato.sSensorLluvia+";"+
            Dato.sTemperaturaDS+";"+
            Dato.sSensorPH;*/

    return  "{\"dataString\":\""+Dato.dataString+"\","+
            "\"humedadAmbiente\":\""+Dato.sHumedadAmbiente+"\","+
            "\"temperaturaAmbiente\":\""+Dato.sTemperaturaAmbiente+"\","+ 
            "\"humedadSueloCH\":\""+Dato.sHumedadSueloCH+"\","+
            "\"humedadSuelo\":\""+Dato.sHumedadSuelo+"\","+
            "\"temperaturaDS\":\""+Dato.sTemperaturaDS+"\","+
            "\"radiacionV\":\""+Dato.sRadiacionV+"\","+
            "\"radiacionGlobal\":\""+Dato.sRadiacionGlobal+"\","+
            "\"sensorHidricoB\":\""+Dato.sSensorHidricoB+"\","+
            "\"sensorViento\":\""+Dato.sSensorViento+"\","+
            "\"sensorLluvia\":\""+Dato.sSensorLluvia+"\","+
            "\"sensorPH\":\""+Dato.sSensorPH+"\"}";
  }

float mapfloat( float x,float int_min, float int_max,float out_min,float out_max ) {
    return(x - int_min)*(out_max - out_min) / (int_max - int_min) + out_min;
  }


void Tic(){
  fSensorViento=cViento;
  //Dato.sSensorViento=cViento;
  cViento=0;

 
};
void MedirViento(){
     cViento++;
     Serial.println(cViento);
}

void MedirLluvia(){
         fSensorLluvia += 0.2794;
         Serial.println(fSensorLluvia);
}



 
