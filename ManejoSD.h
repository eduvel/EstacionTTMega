#define NombreArchivo "datalog.txt"
#include <SPI.h>
#include <SD.h>

class Registro{
  public:
    String dataString;
    String sHumedadAmbiente;
    String sTemperaturaAmbiente;
    String sHumedadSueloCH;
    String sHumedadSuelo;
    String sTemperaturaDS;
    String sRadiacionV;
    String sRadiacionGlobal;
    String sSensorHidricoB;
    String sSensorViento;
    String sSensorLluvia;
    String sSensorPH;
 
  String Cadena(){
    return dataString+";"+sHumedadAmbiente+";"+sTemperaturaAmbiente+";"+sHumedadSueloCH
   +";"+sHumedadSuelo
    +";"+sTemperaturaDS
    +";"+sRadiacionV
   +";"+sRadiacionGlobal
    +";"+sSensorHidricoB
    +";"+sSensorViento
    +";"+sSensorLluvia
    +";"+sTemperaturaDS
    +";"+sSensorPH;
    }
  };

 
 
const int chipSelect = 53;
/*
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
 **
  */

void InicioSD();
void EscribirRegistro(Registro Dato);
void LeerRegistro(void);
void BorrarSD(void);
