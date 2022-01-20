#include <TFT.h>
#include <SPI.h>
#define cs 10
#define dc 9
#define rst 8
TFT TFTscreen = TFT(cs, dc, rst);
// создадим массив для вывода на экран значений
char sensorPrintout[5];
void setup() {
// инициализируем экран
TFTscreen.begin();
// ставим черный фон
TFTscreen.background(0, 0, 0);
// пишем текст на экран белого цвета
TFTscreen.stroke(255, 255, 255);
// задаем размер текста
TFTscreen.setTextSize(1);
// передвигаем курсор в левый верхний угол, чтобы начать писать оттуда
TFTscreen.text("Sensor Value :\n ", 3, 3);
// задаем размер текста для значений с потенциометра
TFTscreen.setTextSize(3);
}
void loop() {
// считываем значения с потенциометра в переменную типа string
String sensorVal = String(analogRead(A0));
// преобразуем полученную строку в массив символов
sensorVal.toCharArray(sensorPrintout, 5);
TFTscreen.stroke(255, 255, 255);
// выводим значения на экран
TFTscreen.text(sensorPrintout, 0, 20);
delay(250);
TFTscreen.stroke(0, 0, 0);
TFTscreen.text(sensorPrintout, 0, 20);
}
