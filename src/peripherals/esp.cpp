#include "ArduinoJson.h"
#include "esp.h"
#include "pindef.h"

void espInit(void) {
  USART_ESP32.begin(115200);
}

/*
Example Deserialization Below
---------------------
StaticJsonDocument<128> sensorData;
DeserializationError error = deserializeJson(sensorData, input);
if (error) { return; }
int m = sensorData["m"]; // mode : Depending on mode, some below data may not be present
long ms = sensorData["ms"]; // brew time millis
float t = sensorData["t"]; // temperature
float p = sensorData["p"]; // pressure
float w = sensorData["w"]; // weight
float f = sensorData["f"]; // flow
*/
void sendEspSensorUpdate(eepromValues_t &runningCfg, SensorState &currentState, bool brewActive, bool scalesPresent, unsigned long currentBrewMillis) {
    StaticJsonDocument<96> sensorData;
    sensorData["t"] = currentState.temperature - runningCfg.offsetTemp;

    if(brewActive) {
      sensorData["ms"] = currentBrewMillis;
      sensorData["m"] = 1;
      sensorData["p"] = currentState.smoothedPressure;
      sensorData["w"] = scalesPresent ? currentState.weight : currentState.shotWeight;
      sensorData["f"] = currentState.weight > 0.4f ? currentState.weightFlow : currentState.smoothedPumpFlow;
    } else {
      sensorData["m"] = 0;
      sensorData["p"] = currentState.pressure;
      sensorData["w"] = currentState.weight;
    }

    serializeJson(sensorData, USART_ESP32);
}

