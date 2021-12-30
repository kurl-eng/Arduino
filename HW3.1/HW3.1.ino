#include <OneWire.h>
OneWire ds(8);
int temperature = 0;
long lastUpdateTime = 0;
const int TEMP_UPDATE_TIME = 1000;

#define RED 5
#define GREEN 6
#define BLUE 7

void setup() {
Serial.begin(9600);
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
}

void loop() {
    for (temperature; temperature > detectTemperature(); temperature) {
    Serial.print("Измеряю температуру: ");
        if ((temperature > -10) && (temperature < 25)) {
            Serial.print("Температура = ");
            Serial.print(temperature);
            Serial.println(" градусов Цельсия. (Прохладно)");
            analogWrite(RED, 0);
            analogWrite(GREEN, 0);
            analogWrite(BLUE, 255);
            //setColor(0, 0, 255);
            delay(1000);
        } else if ((temperature >= 25) && (temperature < 40)) {
            Serial.print("Температура = ");
            Serial.print(temperature);
            Serial.println(" градусов Цельсия. (Тепло)");
            analogWrite(RED, 0);
            analogWrite(GREEN, 255);
            analogWrite(BLUE, 0);
        //setColor(0, 255, 0);
        delay(1000);
        } else if ((temperature >= 40) && (temperature <= 80)) {
            Serial.print("Температура = ");
            Serial.print(temperature);
            Serial.println(" градусов Цельсия. (Горячо)");
            analogWrite(RED, 255);
            analogWrite(GREEN, 255);
            analogWrite(BLUE, 0);
            //setColor(255, 255, 0);
            delay(1000);
        } else if ((temperature > 80) && (temperature <= 100)) {
            Serial.print("Температура = ");
            Serial.print(temperature);
            Serial.println(" градусов Цельсия. (Очень горячо)");
            analogWrite(RED, 250);
            analogWrite(GREEN, 0);
            analogWrite(BLUE, 0);
            //setColor(255, 0, 0);
            delay(1000);
        }
    }

// BLUE - cold
//setColor(0, 0, 255);
//delay(1000);
// GREEN - normal
//setColor(0, 255, 0);
//delay(1000);
// YELLOW - hot
//setColor(255, 255, 0);
//delay(1000);
// RED - very hot
//setColor(255, 0, 0);
//delay(1000);
// WHITE - LED on
//setColor(255, 255, 255);
//delay(1000);
}

void setColor(int R, int G, int B) {
    analogWrite(RED, R);
    analogWrite(GREEN, G);
    analogWrite(BLUE, B);
}

int detectTemperature() {
byte data[2];
ds.reset();
ds.write(0xCC);
ds.write(0x44);

    if (millis() - lastUpdateTime > TEMP_UPDATE_TIME) {
        lastUpdateTime = millis();
        ds.reset();
        ds.write(0xCC);
        ds.write(0xBE);
        data[0] = ds.read();
        data[1] = ds.read();

        temperature = (data[1] << 8) + data[0];
        temperature = temperature >> 4;
    }
}
