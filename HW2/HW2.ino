const int POT = A0;
int potIn = 0;
const int ledpin[9] = {3, 4, 5, 6, 7, 8, 9, 10, 11};
int ledcount = 0;

void setup() {
    for (int i = 0; i <= 9; i++) {
        pinMode(ledpin[i], OUTPUT);
        digitalWrite(ledpin[i], LOW);
    }
}

void loop() {
potIn = analogRead(POT);
ledcount = map(potIn, 0, 1023, 0, 9);
    for (int i = 0; i <= 9; i++) {
        if (i <= ledcount)
        digitalWrite(ledpin[i], HIGH);
        else
        digitalWrite(ledpin[i], LOW);
    }
}
