#include "ILC.h"

#define VEML6040_CONF 0x00  // command codes
#define VEML6040_R_DATA 0x08
#define VEML6040_G_DATA 0x09
#define VEML6040_B_DATA 0x0A
#define VEML6040_W_DATA 0x0B
#define VEML6040_ADDRESS 0x10
uint16_t count = 0;

enum IT {
    IT_40 = 0,  //   40 ms
    IT_80,      //   80 ms
    IT_160,     //  160 ms
    IT_320,     //  320 ms
    IT_640,     //  640 ms
    IT_1280     // 1280 ms
};

// Specify VEML6070 Integration time
uint8_t IT = IT_160;
uint16_t ITime = 160;  // milliseconds
uint16_t RGBWData[4] = {0, 0, 0, 0};
float GSensitivity = 0.25168 / ((float)(1 << IT));  // ambient light sensitivity increases with integration time

ILC::ILC() {
}

bool ILC::begin() {
    Wire.beginTransmission(VEML6040_ADDRESS);
    if (!Wire.endTransmission())
        return false;

    Wire.beginTransmission(VEML6040_ADDRESS);
    Wire.write(VEML6040_CONF);  // Command code for configuration register
    Wire.write(IT << 4);        // Bit 3 must be 0, bit 0 is 0 for run and 1 for shutdown, LS Byte
    Wire.write(0x00);           // MS Byte
    Wire.endTransmission();
    return true;
}

bool ILC::getData(float &R, float &G, float &B, float &W, float &C) {
    Wire.beginTransmission(VEML6040_ADDRESS);
    if (!Wire.endTransmission())
        return false;

    for (int j = 0; j < 4; j++) {
        uint8_t rawData[2] = {0, 0};
        Wire.beginTransmission(VEML6040_ADDRESS);
        Wire.write(VEML6040_R_DATA + j);   // Command code for reading rgbw data channels in sequence
        Wire.endTransmission(false);  // Send the Tx buffer, but send a restart to keep connection alive

        Wire.requestFrom(VEML6040_ADDRESS, 2);  // Read two bytes from slave register address
        uint8_t i = 0;
        while (Wire.available()) {
            rawData[i++] = Wire.read();  // Put read results in the Rx buffer
        }
        Wire.endTransmission();
        RGBWData[j] = ((uint16_t)rawData[1] << 8) | rawData[0];  // 16-bit unsigned integer
    }

    R = (float)RGBWData[0] / 96.0f;
    G = (float)RGBWData[1] / 74.0f;
    B = (float)RGBWData[2] / 56.0f;
    W = (float)RGBWData[1] * GSensitivity;

    // Empirical estimation of the correlated color temperature CCT:
    // see https://www.vishay.com/docs/84331/designingveml6040.pdf
    float temp = ((float)(RGBWData[0] - RGBWData[2]) / (float)RGBWData[1]);
    C = 4278.6f * pow(temp, -1.2455) + 0.5f;

    return true;  // Return true for successful read (add error handling if needed)
}

bool ILC::getJSON(JsonDocument &doc) {
    float R, G, B, W, C;
    if (!getData(R, G, B, W, C)) {
        return false;
    }

    JsonArray dataArray = doc["ILC"].to<JsonArray>();

    JsonObject dataSet = dataArray.add<JsonObject>();  // First data set
    dataSet["name"] = "Red";
    dataSet["value"] = R;
    dataSet["unit"] = "µW/cm²";

    dataSet = dataArray.add<JsonObject>();  // Subsequent data sets
    dataSet["name"] = "Green";
    dataSet["value"] = G;
    dataSet["unit"] = "µW/cm²";

    dataSet = dataArray.add<JsonObject>();  // Subsequent data sets
    dataSet["name"] = "Blue";
    dataSet["value"] = B;
    dataSet["unit"] = "µW/cm²";

    dataSet = dataArray.add<JsonObject>();  // Subsequent data sets
    dataSet["name"] = "Ambient Light";
    dataSet["value"] = W;
    dataSet["unit"] = "lx";

    dataSet = dataArray.add<JsonObject>();  // Subsequent data sets
    dataSet["name"] = "Color Temperature";
    dataSet["value"] = C;
    dataSet["unit"] = "Kelvin";
    return true;
}
