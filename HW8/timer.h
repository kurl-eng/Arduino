#pragma once
#include <Arduino.h>

class Timer {
        public:
            // С указанием периода
            Timer (int period) {
                _period = period;
            }

            // Возвращает true при срабатывании
            bool ready() {
                if (millis() - _tmr >= _period) {
                    return true;
                }
                return false;
            }
        private:
            uint32_t _tmr;
            int _period;
};