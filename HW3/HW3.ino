//#define LED 3
const int LED = 3;

void setup() {
Serial.begin(9600);
pinMode(LED, OUTPUT);
}

void loop() {
const int light = analogRead(A0);
const int brightness = map(light, 0, 1023, 0, 255);

analogWrite(LED, brightness);

Serial.print("Analog: ");
Serial.print(light);
Serial.print(", Brightness: ");
Serial.println(brightness);
delay(100);
}