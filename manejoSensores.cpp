#include "manejoSensores.h"
SoftwareSerial MySerial(8, 9); // RX, TX

//float fHumedadAmbiente;
//float fHumedadSuelo;
//float fTemperaturaAmbiente;
//float fTemperaturaDS;
//float fRadiacion;
//float fSensorHidricoU;
//float fSensorHidricoB;
//float fSensorViento;
float fSensorLluvia;
int cViento;


char strSeteado;


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
 Serial.begin(9600);
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

String medicionSensores(uint16_t Ts){
  //Serial.println(TiempoActual(rtc));
//digitalWrite(ActivacionSensorH,HIGH);
delay(20);
//int valor=analogRead(SensorPH);
//Serial.println(dht.readHumidity());
//Serial.println(dht.readTemperature());
Serial.println(analogRead(SensorRadiacionV));
//float valor=sensorTemperatura1.getTemperatura().toFloat();
//Serial.println(sensorTemperatura1.getTemperatura());
//int Dato=analogRead(A0);
//Serial.println(analogRead(SensorHidrico));
//digitalWrite(ActivacionSensorH,LOW);
delay(500);
//  TiempoUnix = TiempoActualInt(rtc);
//
//  if (TiempoUnix >= (TiempoUnixBase + 600 )) {
//    /*Toma de datos temperatura y reloj
//    Armado de registro para guardar en SD*/
//    TiempoUnixBase = TiempoUnix;
//    Dato.dataString = TiempoActual(rtc);
//    Dato.sHumedadAmbiente = fHumedadAmbiente;
//    Dato.sTemperaturaAmbiente = fTemperaturaAmbiente; 
//    Dato.sHumedadSuelo = fHumedadSuelo; 
//    Dato.sTemperaturaDS = fTemperaturaDS;
//    Dato.sRadiacion= fRadiacion;
//    Dato.sSensorHidricoU = fSensorHidricoU;
//    Dato.sSensorHidricoB = fSensorHidricoB;
//    Dato.sSensorViento = fSensorViento;
//    Dato.sSensorLluvia = fSensorLluvia;


//    Dato.sHumedadAmbiente = dht.readHumidity();
//    Dato.sTemperaturaAmbiente = dht.readTemperature();;
//    Dato.sHumedadSuelo = analogRead(A0);
//    Dato.sTemperaturaDS = sensorTemperatura1.getTemperatura().toFloat();
//    Dato.sRadiacion= mapfloat(analogRead(A2),200,593,0.0,15.0);
//    Dato.sSensorHidricoU = "0.0";
//    Dato.sSensorHidricoB = mapfloat(analogRead(A1),496,122,0.0,80.0);
//    // Dato.sSensorViento = "";
//    Dato.sSensorLluvia = fSensorLluvia;
//    EscribirRegistro(Dato);
//    Serial.println(Dato.Cadena());
//    
//     
//  }
  return "";
  }

float mapfloat( float x,float int_min, float int_max,float out_min,float out_max ) {
    return(x - int_min)*(out_max - out_min) / (int_max - int_min) + out_min;
  }


void Tic(){
// fSensorViento=cViento;
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
