const int NUMS = 30;
//...

void setup() {
Serial.begin(9600);
}

float val = 0;

void loop() {
int light = analogRead(A0);

/*
int srAriff() {
    long sum = 0;
    for (int i = 0; i < NUM; i++) 
    sum += light;
    return((float)sum/NUMS);
}
*/

val += (light - val)*0.1;
Serial.print(light);
Serial.print(" , ");
Serial.println(val);
val = map(val, 0, 1023, 0, 10);

Serial.print("Sensor scaning: ");
Serial.print(light);

if (light < 100) {
    Serial.println(" - Dark");
} else if (light < 300) {
    Serial.println(" - Dim");
} else if (light < 600) {
    Serial.println(" - Light");    
} else if (light < 900) {
    Serial.println(" - Bright");
} else {
    Serial.println(" - Very bright");
}
delay(500);
}
