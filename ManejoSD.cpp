#include"ManejoSD.h"
void InicioSD(){
  Serial.print(F("Initializing SD card..."));

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("SD failed");
    // don't do anything more:
    return;
  }
  Serial.println("SD Ok");
  };
void EscribirRegistro(Registro Dato){
  File dataFile = SD.open(NombreArchivo, FILE_WRITE);
    
      // if the file is available, write to it:
      if (dataFile) {
        //dataFile.println("1,2,3,4");//Dato.Cadena());//dataString);

    /*String dataString;
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
    String sSensorPH;*/

        dataFile.print(Dato.dataString);
        dataFile.print(";HA;");
        dataFile.print(Dato.sHumedadAmbiente);
        dataFile.print(";TA;");
        dataFile.print(Dato.sTemperaturaAmbiente); 
        dataFile.print(";HSCH;");
        dataFile.print(Dato.sHumedadSueloCH); 
        dataFile.print(";HS;");
        dataFile.print(Dato.sHumedadSuelo); 
        dataFile.print(";TDS;");
        dataFile.print(Dato.sTemperaturaDS);
        dataFile.print(";RUV;");
        dataFile.print(Dato.sRadiacionV);
        dataFile.print(";RUVG;");
        dataFile.print(Dato.sRadiacionV);
        dataFile.print(";SHB;");
        dataFile.print(Dato.sSensorHidricoB);
        dataFile.print(";SVO;");
        dataFile.print(Dato.sSensorViento);
        dataFile.print(";SLL;");
        dataFile.println(Dato.sSensorLluvia);
        dataFile.print(";SPH;");
        dataFile.println(Dato.sSensorPH);
        dataFile.close();
        // print to the serial port too:
        //Serial.println(Dato.Cadena());
      }
      // if the file isn't open, pop up an error:
      else {
        Serial.println(F("error opening datalog.txt"));
      };
      
};

//void LeerRegistro(void){
//  long TiempoActual;
//  long TiempoInicio;
//  File dataFile = SD.open(NombreArchivo, FILE_READ);
//      char Dato;
//      // if the file is available, write to it:
//      if (dataFile) {
//        //dataFile.println(Dato.Cadena());//dataString);
//        
//        while(dataFile.available()){
//        // print to the serial port too:
//          Dato=dataFile.read();
//          Serial.write(Dato);
////          //delay(100);
////          if(Dato==13){
////            TiempoInicio=millis();
////            while((Serial.available()<=0) && (TiempoInicio+10>TiempoActual)){
////              TiempoActual=millis();
////              };
////            (void)(Serial.read()==0);
////            }
//        }
//        dataFile.close();
//      }
//      // if the file isn't open, pop up an error:
//      else {
//        Serial.println("error opening datalog.txt");
//      };
//      Serial.write('>');
//};
//
void BorrarSD(void){
       
       if (SD.exists(NombreArchivo))
       SD.remove(NombreArchivo);
       
       if (!SD.exists(NombreArchivo))
       Serial.print("K");
}
