#include <OneWire.h>
#include <TFT.h>
#include <SPI.h>
#include <UTFT.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define cs 10
#define dc 9
#define rst 8
TFT TFTscreen = TFT(cs, dc, rst);
// создадим массив для вывода на экран значений
char sensorPrintout[5];

OneWire ds(A0);
float temperature = 0;
long lastUpdateTime = 0;
const int TEMP_UPDATE_TIME = 1000;
char tempPrintout[6];
int timing;
void setup() {

  // инициализируем экран
TFTscreen.begin();
// ставим черный фон
TFTscreen.background(255, 255, 255);
// пишем текст на экран белого цвета
TFTscreen.stroke(0, 0, 0);
// задаем размер текста
TFTscreen.setTextSize(2);
// передвигаем курсор в левый верхний угол, чтобы начать писать оттуда
TFTscreen.text("Sensor Value:\n ", 5, 3);
// задаем размер текста для значений с потенциометра
TFTscreen.setTextSize(2);
TFTscreen.text("Temperature:\n", 5, 40);

}

void loop() {
  detectTemperature();
// считываем значения с потенциометра в переменную типа string
// преобразуем полученную строку в массив символов
String sensorVal = String(analogRead(A0));
sensorVal.toCharArray(sensorPrintout, 5);
String tempVal = String(temperature);
tempVal.toCharArray(tempPrintout, 6);
// выводим значения на экран
TFTscreen.stroke(0, 0, 0);
TFTscreen.text(sensorPrintout, 5, 20);
TFTscreen.stroke(0,0,0);
TFTscreen.text(tempPrintout, 5, 70);
delay(1000);
TFTscreen.stroke(255, 255, 255);
TFTscreen.text(tempPrintout, 5, 70);
TFTscreen.stroke(255, 255, 255);
TFTscreen.text(sensorPrintout, 5, 20);

 //Serial.println(temperature);
}


float detectTemperature(){

  byte data[2];
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);

  if (millis() - lastUpdateTime > TEMP_UPDATE_TIME)
  {
    lastUpdateTime = millis();
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    data[0] = ds.read();
    data[1] = ds.read();

    temperature =  ((data[1] << 8) | data[0]) * 0.0625;
  }
}
