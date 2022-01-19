// Ведомое устройство
#include <Wire.h>

byte i2c_rcv;
unsigned long time_start;
int stat_LED;
byte value_pot;

void setup()
{
    // Инициализация канала по шине от ведомого устройства
	Wire.begin(0x08);
	Wire.onReceive(dataRcv);
	Wire.onRequest(dataRqst);
	
	i2c_rcv = 255;
	time_start = millis();
	stat_LED = 0;
	
	pinMode(13, OUTPUT);
}

void loop()
{
	value_pot = analogRead(A0);

        if((millis() - time_start) > (1000 * (float)(i2c_rcv/255))) {
		stat_LED = !stat_LED;
		time_start = millis();
	}
	digitalWrite(13, stat_LED);
}

// Фукнция получения данных
void dataRcv(int numBytes)
{
	while(Wire.available()) {	// read all bytes received
		i2c_rcv = Wire.read();
	}
}

// Фукнция запроса данных
void dataRqst()
{
	Wire.write(value_pot); // send potentiometer position
}