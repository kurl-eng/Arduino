//DS18B20 Header file:
#pragma once
#define ONE_WIRE_BUS A0 // Analog pin 0
#include <Arduino.h>
#include <DallasTemperature.h>

class Temperature {
        public:
            void begin();
            void filter();
            float get();

        private:
            float tempSum = 0, temp = 0;
            byte tempCount = 0;
};