// Объявление переменных для пинов Ардуино :
#define FIRST_LED_PIN 3 // Порт первого пина LED
#define LAST_LED_PIN 11 // Порт последнего пина LED
const int POT = A0; // Порт пина ручки потенциометра
// Переменные :
int potIn = 0; // Переменная порта потенциометра
const int ledpin[] = {3, 4, 5, 6, 7, 8, 9, 10, 11}; // Массив пинов LED
int ledcount = sizeof(ledpin) / sizeof(int); // Переменная количества пинов массива LED

void setup() {
Serial.begin(9600); //Бодрейт шины Ардуино
    // Цикл счетчика переменной ledcount портов LED присваивает значения кажому пину
    for (int ledcount = FIRST_LED_PIN; ledcount <= LAST_LED_PIN; ledcount++) {
        pinMode(ledcount, OUTPUT);
        digitalWrite(ledpin[ledcount], LOW);
    }
    // Цикл счетчика ledcount присваивает переменным массива ledpin начальные значения
    /*for (int ledcount = 0; ledcount < ledpin[ledcount]; ledcount++) {
        pinMode(ledpin[ledcount], OUTPUT);
        digitalWrite(ledpin[ledcount], LOW);
    }*/
}

void loop() {
unsigned int ms = millis();
int pin = LAST_LED_PIN - (ms / 100) % 10; // Бегущий огонь в обратном направлении
//int pin = FIRST_LED_PIN + (ms / 100) % 10; // Бегущий огонь в прямом направлении
digitalWrite(pin, HIGH); // Есди поменять значения, 
delay(100);
digitalWrite(pin, LOW); //огонь будет бежать сквозь горящие LED
// Переменная potIn присваивается порту POT = A0
potIn = analogRead(POT);
Serial.print("rotate = ");
Serial.println(potIn);
//соотношение масштаба аналогово сигнал с количеством LED
potIn = map(potIn, 0, 1023, 0, 9);
//Ограничение входного значения сигнала
constrain(potIn, 0, 9);
//Цикл вращения ручки потенциометра 
for (int i = 0; i < 9; i++) {
    if (i < potIn) {
        digitalWrite(ledpin[i], HIGH); // При обратном значении напряжения 
        delay(0);
    } else
        digitalWrite(ledpin[i], LOW); //инвертирует последовательность включения LED
        delay(0);
    }
}
