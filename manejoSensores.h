#include <DHT.h>
//#include <DHT_U.h>
#include <Wire.h>
#include <RTClib.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#include <EEPROM.h>
#include <TimerOne.h>
#include <SoftwareSerial.h>
#include "ManejoSD.h"
#include "ManejoClock.h"
#include "ManejoSensorTemperatura.h"


#ifndef _MANEJOSENSORES
#define _MANEJOSENSORES
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 6
// Dependiendo del tipo de sensor
#define DHTTYPE DHT22

#define Anemometro 18
#define Pluviometro 19
#define CS_SD 53
#define RFM95_CS 49
#define SensorHumedadCH A4 //deberia ir A4, pero esta rota en arduino
#define SensorRadiacionGlobal A1 //deberia ser A1, pero no anda
#define SensorPH A2
#define ActivacionSensorH 23
#define SensorHumedad A3
#define SensorHidrico A0
#define SensorRadiacionV A6

boolean tiempoMedicion(uint16_t Ts);
void inicioSensores();
String medicionSensores();
float mapfloat( float x,float int_min, float int_max,float out_min,float out_max ) ;
void Tic();
void MedirViento();
void MedirLluvia();

#endif
