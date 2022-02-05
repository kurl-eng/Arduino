// Setup modules PINs and variables

//SPI TFT LCD 1.8" V1.1: ST7735
#include <TFT.h>
#include <SPI.h>
TFT TFTscreen = TFT(10, 9, 8);

// DHT22 AM2302 :
// Inside temerature and humidity sensor
#include <DHT.h>
int maxHum = 60;
int maxTemp = 40;
DHT dht(A1, DHT22);
char tempInsidePrintout[6];
char humInsidePrintout[6];

// DS18B20 :
// Outside temerature sensor
#include <OneWire.h>
OneWire ds(A0);                     // Connected PIN
float temperature = 0;
long lastUpdateTime = 0;
const int TEMP_UPDATE_TIME = 1000;
char tempOutsidePrintout[7];

// DS1302 :
// RTC module
#include <ThreeWire.h>  
#include <RtcDS1302.h>
ThreeWire myWire(7,6,5);            // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
char rtcPrintout[20];

// KY-040 :
// Rotary encoder
#include <GyverEncoder.h>
#define CLK 3
#define DT 2
#define SW 4
// для работы c кнопкой
Encoder enc1(CLK, DT, SW);

// Setup modules and initialize them
void setup() {

Serial.begin(9600);

// TFT initialize
TFTscreen.begin();
TFTscreen.setRotation(90);
TFTscreen.background(255, 255, 255);
TFTscreen.stroke(0, 0, 0);
TFTscreen.setTextSize(1.5);
TFTscreen.text("RTC time: \n", 10, 5);
TFTscreen.text("Temp. Outside: \n", 10, 15);
TFTscreen.text("Temp. Inside: \n", 10, 25);
TFTscreen.text("Humidity: \n", 10, 35);

// Inside temperature module initialize
dht.begin();

// RTC initializing
Rtc.Begin();

// Rotary encoder setup :
//enc1.setType(TYPE2);
}

void loop() {
RtcDateTime now = Rtc.GetDateTime();
printDateTime(now);

// Outside temperature module:
detectTemperature();
// Inside temperature module:
float h = dht.readHumidity();
float t = dht.readTemperature();

// Module string convertion
String tempOutside = String(temperature);
tempOutside.toCharArray(tempOutsidePrintout, 7);
String tempInside = String(t);
tempInside.toCharArray(tempInsidePrintout, 6);
String humInside = String(h);
humInside.toCharArray(humInsidePrintout, 6);
String rtcTime = String(Rtc.GetDateTime());
rtcTime.toCharArray(rtcPrintout, 20);

// Screen refresh rate
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(rtcPrintout, 65, 5);
  TFTscreen.text(tempOutsidePrintout, 95, 15);
  TFTscreen.text(tempInsidePrintout, 95, 25);
  TFTscreen.text(humInsidePrintout, 95, 35);
delay(1000);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text(rtcPrintout, 65, 5);
  TFTscreen.text(tempOutsidePrintout, 95, 15);
  TFTscreen.text(tempInsidePrintout, 95, 25);
  TFTscreen.text(humInsidePrintout, 95, 35);


// Rotary encoder :
enc1.tick();
  // если был совершён поворот (индикатор поворота в любую сторону)
  if (enc1.isTurn()) {         
    // ваш код
  }
  // если был поворот
  if (enc1.isRight()) Serial.println("Right");         
  if (enc1.isLeft()) Serial.println("Left");
  
  // если было удержание + поворот
  if (enc1.isRightH()) Serial.println("Right holded");
  if (enc1.isLeftH()) Serial.println("Left holded");
  
  // нажатие на кнопку (+ дебаунс)
  if (enc1.isPress()) Serial.println("Press");
    
  // отпускание кнопки (+ дебаунс)       
  if (enc1.isClick()) Serial.println("Click");   
     
  // то же самое, что isClick
  //if (enc1.isRelease()) Serial.println("Release");
       
  // если была удержана и энк не поворачивался
  if (enc1.isHolded()) Serial.println("Holded");
  
  // возвращает состояние кнопки
  //if (enc1.isHold()) Serial.println("Hold");      
}

// Outside temperature detection function
float detectTemperature(){

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

    temperature =  ((data[1] << 8) | data[0]) * 0.0625;
  }
}

#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.println(datestring);
}