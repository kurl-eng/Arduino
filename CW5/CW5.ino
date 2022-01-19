// Ведущее устройство
#include <Wire.h> // Встроенная библиотека I2C

byte i2c_rcv;               // Получение сигнала через пин А4
unsigned long time_start;   // Время запуска в милисекундах
int stat_LED;               // Индикация LED: 1 - ВКЛ, 0 - ВЫКЛ
byte value_pot;             // Значение потенциометра

void setup()
{
	Wire.begin(); // Инициализация шины ведущим устройством
	
	// Иницализция глобальных переменных
	i2c_rcv = 255;
	time_start = millis();
	stat_LED = 0;
	
	pinMode(13, OUTPUT);    // Назначим 13 пин на вывод (LED)
}

void loop()
{
	// Считывает значение потенциометра
	value_pot = analogRead(A0);   // Вольтаж на пин А0

	// Отправляем значение потенциометра на ведомое устройство по адресу 0x08
    // Инициализируем канал по шине на ведомое устройство 8 по адресу (0x08)
    Wire.beginTransmission(0x08);
    // Отправляем значение переменной потенциометра
	Wire.write(value_pot);
    // Закрываем канал передачи данных по шине
	Wire.endTransmission();
    // Ждем значение потенциометра с ведомого устройства по адресу 0x08 и кол-во байт (1)
	Wire.requestFrom(0x08, 1);
    // Считываем значение от потенциометра ведомого устройства в переменную
	if(Wire.available()) {
		i2c_rcv = Wire.read();
	}
	
	// Алгоритм мигания LED
	if((millis() - time_start) > (1000 * (float)(i2c_rcv/255))) {
		stat_LED = !stat_LED;
		time_start = millis();
	}
	digitalWrite(13, stat_LED);
}