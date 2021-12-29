#define RED_LED 11
#define GREEN_LED 3
#define BLUE_LED 6
int t = 7;

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

}

void loop() {
    for (int light = 0; light <= 255; light++) {
        analogWrite(RED_LED, 255);
        analogWrite(GREEN_LED, light);
        analogWrite(BLUE_LED, LOW);
        delay(t);
    }
    for (int light = 0; light <= 255; light++) {
        analogWrite(RED_LED, 255 - light);
        analogWrite(GREEN_LED, 255);
        analogWrite(BLUE_LED, LOW);
        delay(t);
    }
}