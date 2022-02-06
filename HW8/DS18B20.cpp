#include "DS18B20.h"

static OneWire oneWire(ONE_WIRE_BUS);
static DallasTemperature sensors(&oneWire);

void Temperature::begin() {
    // Запуск датчика по присвоеному пину
    sensors.begin();
    // Асинхронное получение данных
    sensors.setWaitForConversion(false);
}

void Temperature::filter() {
    // Получим суммарное значение измерений
    tempSum += sensors.getTempCByIndex(0);
    sensors.requestTemperatures();
    // Среднее значение
    // Подсчёт измерений
    tempCount++;
    // Если больше 5, то
    if (tempCount >= 5) {
        // Обнулить счётчик
        tempCount = 0;
        // В temp присвоить среднее значение tempSum от 5
        temp = tempSum / 5;
        // Обнулить сумму измерений
        tempSum = 0;
    }
}

float Temperature::get() {
    return temp;
}