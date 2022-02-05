// Setup modules PINs and variables

//SPI TFT LCD 1.8" V1.1: ST7735
#include <TFT.h>
#include <SPI.h>
TFT TFTscreen = TFT(10, 9, 8);

uint32_t blackFrame;
uint32_t refreshFrame;
int blackFramePeriod = 1;


// DHT22 AM2302 :
// Inside temerature and humidity sensor
#include <DHT.h>
int maxHum = 60;
int maxTemp = 40;
DHT dht(A1, DHT22);
char tempInsidePrint[6];
char humInsidePrint[6];

// DS18B20 :
// Outside temerature sensor
#include <OneWire.h>
OneWire ds(A0);                     // Connected PIN
float temperature = 0;
long lastUpdateTime = 0;
const int TEMP_UPDATE_TIME = 1000;
char tempOutsidePrint[6];

// DS1302 :
// RTC module
#include <ThreeWire.h>  
#include <RtcDS1302.h>
ThreeWire myWire(7,6,5);            // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
#define countof(a) (sizeof(a) / sizeof(a[0]))
char rtcPrintDateTime[20];
char printDT[20];

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
TFTscreen.setTextSize(1);
TFTscreen.text("RTC time: \n", 10, 5);
TFTscreen.text("Temp. Outside: \n", 10, 25);
TFTscreen.text("Temp. Inside: \n", 10, 35);
TFTscreen.text("Humidity: \n", 10, 45);

// Inside temperature module initialize
dht.begin();

// RTC initializing
Rtc.Begin();

// Rotary encoder setup :
//enc1.setType(TYPE2);
}

void loop() {
// RTC module:
RtcDateTime time = Rtc.GetDateTime();
printDateTime(time);

// Outside temperature module:
detectTemperature();

// Inside temperature module:
float h = dht.readHumidity();
float t = dht.readTemperature();

// Module string convertion
String rtcTime = String(Rtc.GetDateTime());
rtcTime.toCharArray(printDT, 20);
String tempOutside = String(temperature);
tempOutside.toCharArray(tempOutsidePrint, 6);
String tempInside = String(t);
tempInside.toCharArray(tempInsidePrint, 6);
String humInside = String(h);
humInside.toCharArray(humInsidePrint, 6);

// Screen refresh rate
refreshFrame = millis() - blackFrame;
if (refreshFrame >= blackFramePeriod) {
  blackFrame += blackFramePeriod * (refreshFrame / blackFramePeriod);
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(rtcPrintDateTime, 10, 15);
  TFTscreen.text(tempOutsidePrint, 95, 25);
  TFTscreen.text(tempInsidePrint, 95, 35);
  TFTscreen.text(humInsidePrint, 95, 45);
}
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.text(rtcPrintDateTime, 10, 15);
  TFTscreen.text(tempOutsidePrint, 95, 25);
  TFTscreen.text(tempInsidePrint, 95, 35);
  TFTscreen.text(humInsidePrint, 95, 45);

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


void printDateTime(const RtcDateTime& dt)
{
    snprintf_P(rtcPrintDateTime, 
            countof(rtcPrintDateTime),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    //Serial.println(rtcPrintDateTime);
}