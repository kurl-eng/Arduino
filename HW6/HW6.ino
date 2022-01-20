#include <TFT.h>
#include <SPI.h>
// pin definition for the Uno
#define cs 10
#define dc 9
#define rst 8
TFT TFTscreen = TFT(cs, dc, rst);
// позиция линии, отображающеей сопротивление, на экране
int xPos = 0;
void setup() {
Serial.begin(9600);
// инициализируем дисплей
TFTscreen.begin();
// создаем задний фон
TFTscreen.background(250, 16, 200);
}
void loop() {
// считываем показания с потенциометра, и масштабируем его к высоте экрана
int sensor = analogRead(A0);
int drawHeight = map(sensor, 0, 1023, 0, TFTscreen.height());
Serial.println(drawHeight);
// рисуем линию
TFTscreen.stroke(250, 180, 10);
TFTscreen.line(xPos, TFTscreen.height() - drawHeight, xPos, TFTscreen.height());
// если линия подходит к краю экрана - обновляем экран
if (xPos >= 160) {
xPos = 0;
TFTscreen.background(250, 16, 200);
} else {
// инкрементируем горизонтальную позицию
xPos++;
}
delay(16);
}
