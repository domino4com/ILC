#ifndef ILC_H
#define ILC_H

#include <ArduinoJson.h>
#include <Wire.h>

class ILC {
   public:
    ILC();
    bool begin();
    bool getData(float &R, float &G, float &B, float &W, float &C);
    bool getJSON(JsonDocument &doc);
};

#endif  // ILC_H