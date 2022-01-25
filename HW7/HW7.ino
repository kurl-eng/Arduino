#include <avr/sleep.h>

// LED pins
const int ledPin0 = 3;
const int ledPin1 = 5;
const int ledPin2 = 7;
// LED flags
bool ledState0 = 0;
bool ledState1 = 0;
bool ledState2 = 0;
// LEDs delay in microseconds
unsigned long myTimer0, myTimer1, myTimer2;

// Button pin
const int inputPin = 2;
// Button tick variable
volatile int counter = 0;

// Interrupt flag
volatile boolean flag;

void setup() {
  // Serial bus setup  
  Serial.begin(9600);
  // Declaring LED pins
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // Declaring button
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, buttontick, FALLING);
  // AVR sleep function
  goToSleep();
}

// Tick counter function
void buttontick() {
  counter++;
}

// Set flag function
void setFlag() {
  flag = true;
}

// Sleep function
void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(0, setFlag, LOW); // контакт D2
  // включить энергосберегающий режим
  sleep_mode();
  // Теперь микроконтроллер простаивает, пока уровень напряжения
  // на контакте прерывания не упадет до LOW, затем... 
  //sleep_disable();
  detachInterrupt(0);
 
}

// LED indication function
void ledIndication() {
  if (millis() - myTimer0 >= 1000) {
    myTimer0 = millis();
    ledState0 =! ledState0;
    digitalWrite(3, ledState0);
  }

  if (millis() - myTimer1 >= 333) {
    myTimer1 = millis();
    ledState1 =! ledState1;
    digitalWrite(5, ledState1);
  }
  
  if (millis() - myTimer2 >= 2000) {
    myTimer2 = millis();
    ledState2 =! ledState2;
    digitalWrite(7, ledState2);
  }
}

void loop() {
  Serial.println(counter++);
  delay(2000);
  if (flag) {
   ledIndication();  
   flag = false;
   goToSleep();
  }
}
