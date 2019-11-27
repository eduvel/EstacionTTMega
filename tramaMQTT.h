#include <arduino.h>
#include <SoftwareSerial.h>
class MQTT  {
public:
	MQTT(uint8_t, uint8_t);
	void iniciarSerialSIM900();
	void enviarTramaMQTT(String topico);
	void longitudMensaje(char [], int X);
	//void tramaHex(char Trama[]);
	void tramaHex(const char Trama[], int longitud);
	//void tramaChar(char Trama[]);
	void tramaChar(char Trama[], int longitud);
	unsigned char hexToDec(unsigned char HexStr[]);
	void enviarComandoAT(char Comando[], char Respuesta[], int timeOut);
	void powerOn(void);
private:
	SoftwareSerial  *SIM900;
};
