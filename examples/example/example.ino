#include <ArduinoJson.h>
#include <Wire.h>
#ifndef I2C_SDA
#define I2C_SDA SDA
#endif
#ifndef I2C_SCL
#define I2C_SCL SCL
#endif
#include <ILC.h>

ILC ILC;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.printf("\nILC Test\n");

    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();

    if (ILC.begin()) {
        Serial.println("ILC sensor initialized successfully.");
    } else {
        Serial.println("Failed to initialize ILC sensor!");
        exit(0);
    }
}

void loop() {
    float R,G,B,W,C;

    if (ILC.getData(R, G, B, W, C)) {
        Serial.printf("Red: %.2f µW/cm², Green: %.2f µW/cm², Blue: %.2f µW/cm², Ambient Ligh: %.2f lx, Color Temp.: %.2f Kelvin\n", R, G, B, W, C);
    } else {
        Serial.println("Failed to ILC data.");
    }

    delay(1000);
}