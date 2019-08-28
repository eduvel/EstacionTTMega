#define NombreArchivo "datalog.txt"
#include <SPI.h>
#include <SD.h>

class Registro{
  public:
  String dataString;
  String sHumedadAmbiente;
  String sTemperaturaAmbiente;
  String sHumedadSuelo;
  String sTemperaturaDS;
  String sRadiacion;
  String sSensorHidricoU;
  String sSensorHidricoB;
  String sSensorViento;
  String sSensorLluvia;
  
  
  String Cadena(){
    return dataString+","+sHumedadAmbiente+","+sTemperaturaAmbiente+","+sHumedadSuelo+","+sTemperaturaDS+","+sRadiacion+","+sSensorHidricoU+","+sSensorHidricoB+","+sSensorViento+","+sSensorLluvia;
   
    }
  };

 
 
const int chipSelect = 10; //53 
/*
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
 **
  */

void InicioSD();
void EscribirRegistro(Registro Dato);
//void LeerRegistro(void);
//void BorrarSD(void);
