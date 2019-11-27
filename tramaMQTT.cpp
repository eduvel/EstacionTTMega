#include <arduino.h>
#include "tramaMQTT.h"
#include <string.h>
#include <SoftwareSerial.h>

//extern SoftwareSerial SIM900; // RX, TX
const char tramaConexion[]="103d00064d514973647003c2003c00176d6f73717075627c31363435362d4e54424b2d47332d4500086165697073787768000c564d6a467048565538434a701A";
const char tramaDesconexion[]="e0001a";
char mensaje[350]="\x31\xaf\x02\0\x12/nodoCentral/Trama{\"dataString\":\"2019;11;13;17;14;30\",\"humedadAmbiente\":\"90\",\"temperaturaAmbiente\":\"10.2\",\"humedadSueloCH\":\"1002\",\"humedadSuelo\":\"1002\",\"temperaturaDS\":\"34.4\",\"radiacionV\":\"1002\",\"radiacionGlobal\":\"1002\",\"sensorHidricoB\":\"112\",\"sensorViento\":\"32\",\"sensorLluvia\":\"23.4\",\"sensorPH\":\"07\"}\x1A";
int longitudTrama;


MQTT::MQTT(uint8_t rx, uint8_t tx) {
	this->SIM900 = new SoftwareSerial(rx, tx);

}

void MQTT::iniciarSerialSIM900(){
  SIM900->begin(19200);
  }

void MQTT::powerOn(void) {
	pinMode(9, OUTPUT);
	digitalWrite(9, HIGH);
	delay(3000);
	digitalWrite(9, LOW);
	delay(1500);
};
  
void MQTT::enviarTramaMQTT(String topico){
	topico = "/nodoCentral/Trama" + topico+"\x1A";
  enviarComandoAT("AT\r\n","OK",2000);
  enviarComandoAT("AT+CIPSHUT\r\n","SHUT OK",3000);
  enviarComandoAT("AT+CSTT=\"internet.ctimovil.com.ar\",\"clarogprs\",\"clarogprs999\"\r\n","OK",5000);
  
  enviarComandoAT("AT+CIICR\r\n","OK",2000);
  enviarComandoAT("AT+CIFSR\r\n","OK",1000);
  enviarComandoAT("AT+CGATT=1\r\n","OK",1000);
  enviarComandoAT("AT+CIPSTART=\"TCP\",\"tailor.cloudmqtt.com\",18034\r\n","CONNECT OK",5000);
  enviarComandoAT("AT+CIPSEND\r\n","OK",1000);
  tramaHex(tramaConexion,128);
  delay(5000);
  enviarComandoAT("AT+CIPSEND\r\n","OK",1000);
  topico.toCharArray(&mensaje[5], 345);
  longitudMensaje(&mensaje[1], strlen(&mensaje[5])+1);
  //Serial.print((byte)mensaje[1]);
  //Serial.println((byte)mensaje[2]);
  tramaChar(mensaje,strlen(&mensaje[5])+5);
  delay(5000);
  enviarComandoAT("AT+CIPSEND\r\n","OK",1000);
  tramaHex(tramaDesconexion,6);
  delay(2000);
  enviarComandoAT("AT+CIPSHUT\r\n","SHUT OK",3000);
  //delay(5000);
}

void MQTT::longitudMensaje(char digits[], int X){
  unsigned char digit,valor=0;
  do{
    digit = X % 128;
    X = X / 128;
    // if there are more digits to encode, set the top bit of this digit
    if ( X > 0 )
      digit = digit | 0x80;
    //Serial.println(digit);
	digits[valor] = digit;
	valor++;
    }while ( X> 0 );
}
//
///*void tramaHex(char Trama[]){
//  int i=0;
//  unsigned char Dato;
//  unsigned char datHex[2];
//  while(Trama[i]!='\0'){
//    datHex[0]=Trama[i];
//    datHex[1]=Trama[i+1];
//    Dato= hexToDec(datHex);
//    SIM900.write(Dato);
//    i+=2;
//  }
//
//}*/
void  MQTT::tramaHex(const char Trama[], int longitud){
  int i=0,k;
  unsigned char Dato;
  unsigned char datHex[2];
  for(k=0;k<longitud;k+=2){
    datHex[0]=Trama[i];
    datHex[1]=Trama[i+1];
    Dato= hexToDec(datHex);
 
    SIM900->write(Dato);
    i+=2;
  }

}
//void tramaChar(char Trama[]){
//  int i=0;
//  unsigned char Dato;
//  while(Trama[i]!='\0'){
//    Serial.write(Trama[i]);
//    i++;
//  }
//}
void MQTT::tramaChar(char Trama[], int longitud){
  int i=0,k;
  unsigned char Dato;
 for(k=0;k<longitud;k++){
    SIM900->write(Trama[i]);
    i++;
  }
}

unsigned char MQTT::hexToDec(unsigned char HexStr[]){
  unsigned char mult;
  unsigned char DecNum;
  char ch;
  mult = 1;
  DecNum = 0;
  int i;
  for(i = 1;i>=0;i--){
      ch = HexStr[i];
      if ((ch >= '0') && (ch <= '9'))
          DecNum = DecNum + ((ch - '0')*mult);
      else{
          if ((ch >= 'A') && (ch <= 'F'))
              DecNum = DecNum + (((ch - 'A') + 10) * mult);
          else{
              if ((ch >= 'a') && (ch <= 'f')) 
                  DecNum = DecNum + (((ch - 'a') + 10) * mult);
              else
                  return;
          }
      }
      mult = mult * 16;
  }
  return DecNum;
}

void MQTT::enviarComandoAT(char Comando[],char Respuesta[],int timeOut){
  unsigned long timeInicial,timeActual;
  char valorRespuesta[20];
  char Dato;
  String strDato="";
  SIM900->print(Comando);
  Serial.print(Comando);
  timeInicial=millis();
  do{
    timeActual=millis();
    if (SIM900->available()){
        Dato=SIM900->read();
        
        valorRespuesta[0]='\0';
        if((Dato=='\r') || ((Dato=='\n'))){
          strDato.toCharArray(valorRespuesta,20);
          strDato="";
        }else
          strDato=strDato+Dato;
        //Serial.print(Dato);
      }
      //}while((! ((timeInicial+timeOut)<=timeActual)) && ((strcmp(valorRespuesta,Respuesta))));
	  }while ((!((timeActual - timeOut) >= timeInicial)) && ((strcmp(valorRespuesta, Respuesta))));
      //Serial.println(strDato);
      //Serial.println(valorRespuesta);
}
