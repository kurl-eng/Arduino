#include "timer.h"

//SPI TFT LCD 1.8" V1.1: ST7735
#include <TFT.h>
#include <SPI.h>
TFT TFTscreen = TFT(10, 9, 8);
Timer refreshWhite(3000);
Timer refreshBlack(3000);

// Outside temperature module
#include "DS18B20.h"
Temperature dallas;
char printDallas [6];
Timer tempTimer(1000);

// DHT22 AM2302 :
// Inside temerature and humidity sensor
#include <DHT.h>
int maxHum = 60;
int maxTemp = 40;
DHT dht(A1, DHT22);
char tempInsidePrint[6];
char humInsidePrint[6];

// DS1302 :
// RTC module
#include <ThreeWire.h>  
#include <RtcDS1302.h>
ThreeWire myWire(7,6,5);            // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
#define countof(a) (sizeof(a) / sizeof(a[0]))
char printDate[11], printTime[10], printD[11], printT[10];

// KY-040 :
// Rotary encoder
#include <GyverEncoder.h>
#define CLK 4
#define DT 3
#define SW 2
// для работы c кнопкой
Encoder enc1(CLK, DT, SW);

#include <avr/sleep.h>
const int ledPin4 = A4;
const int ledPin5 = A5;
volatile boolean flag;

void TFTinit() {
TFTscreen.begin();
TFTscreen.setRotation(90);
TFTscreen.background(255, 255, 255);
TFTscreen.stroke(0, 0, 0);
TFTscreen.setTextSize(1);
TFTscreen.text("Date : \n", 10, 5);
TFTscreen.text("Time: \n", 80, 5);
TFTscreen.text("Temp. Outside: \n", 10, 25);
TFTscreen.text("Temp. Inside: \n", 10, 35);
TFTscreen.text("Humidity: \n", 10, 45);
TFTscreen.text("Hold to wake up", 10, 140);
TFTscreen.text("Click to sleep", 10, 150);
}

void setup() {
TFTinit();
Serial.begin(9600);
Rtc.Begin();
dallas.begin();
dht.begin();
attachInterrupt(0, isr, FALLING);
pinMode(ledPin4, OUTPUT);
pinMode(ledPin5, OUTPUT);
//goToSleep();
}

int blink4_delay = 1000;
int blink5_delay = 2000;
uint32_t next4 = 0;
uint32_t next5 = 0;

void loop() {

if (millis() > next4) {
  digitalWrite(ledPin4, !digitalRead(ledPin4));
  next4 = millis() + blink4_delay;
}

if (millis() > next5) {
  digitalWrite(ledPin5, !digitalRead(ledPin5));
  next5 = millis() + blink5_delay;
}
  
  enc1.tick(); 
  flag = true;
  // RTC module:
RtcDateTime date = Rtc.GetDateTime();
rtcPrintDate(date);
RtcDateTime time = Rtc.GetDateTime();
rtcPrintTime(time);
// Inside temperature module:
float h, t;
h = dht.readHumidity();
t = dht.readTemperature();
//Outside temperature module:
if (tempTimer.ready()) dallas.filter();

// Module string convertion
String rtcDate = String(Rtc.GetDateTime());
rtcDate.toCharArray(printD, 11);
String rtcTime = String(Rtc.GetDateTime());
rtcTime.toCharArray(printT, 10);
String dallasTemp = String(dallas.get());
dallasTemp.toCharArray(printDallas, 6);
String tempInside = String(t);
tempInside.toCharArray(tempInsidePrint, 6);
String humInside = String(h);
humInside.toCharArray(humInsidePrint, 6);

// Screen output refresh frames
if (refreshBlack.ready()) {
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(printDate, 10, 15);
  TFTscreen.text(printTime, 80, 15);
  TFTscreen.text(printDallas, 95, 25);
  TFTscreen.text(tempInsidePrint, 95, 35);
  TFTscreen.text(humInsidePrint, 95, 45);
}
if (refreshWhite.ready()) {
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text(printDate, 10, 15);
  TFTscreen.text(printTime, 80, 15);
  TFTscreen.text(printDallas, 95, 25);
  TFTscreen.text(tempInsidePrint, 95, 35);
  TFTscreen.text(humInsidePrint, 95, 45);
}
 if (enc1.isClick()) {
  flag = false;
  goToSleep();
  } else if (enc1.isHold()) {
    setFlag();
  }
}

void setFlag() {
flag = true; 
}

void isr() {
  enc1.tick();  // отработка в прерывании
}

void goToSleep() {
set_sleep_mode(SLEEP_MODE_PWR_DOWN);
sleep_enable();
attachInterrupt(0, setFlag, LOW); // контакт D2
sleep_mode(); // включить энергосберегающий режим
// Теперь микроконтроллер простаивает, пока уровень напряжения
// на контакте прерывания не упадет до LOW, затем... sleep_disable();
detachInterrupt(0);
}

// Date struct
void rtcPrintDate(const RtcDateTime& dt) {
    snprintf_P(printDate,
            countof(printDate),
            PSTR("%02u/%02u/%04u"),
            dt.Month(),
            dt.Day(),
            dt.Year()
            );
    //Serial.println(rtcPrintDate);
}

// Time struct
void rtcPrintTime(const RtcDateTime& dt)
{
    snprintf_P(printTime, 
            countof(printTime),
            PSTR("%02u:%02u:%02u"),
            dt.Hour(),
            dt.Minute(),
            dt.Second()
            );
    //Serial.println(rtcPrintTime);
}
