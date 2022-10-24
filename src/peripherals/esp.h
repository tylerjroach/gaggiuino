#ifndef ESP_H
#define ESP_H

#include "eeprom_data.h"
#include "sensors_state.h"

void espInit(void);
void sendEspSensorUpdate(eepromValues_t &runningCfg, SensorState &currentState, bool brewActive, bool scalesPresent, unsigned long currentBrewMillis);

#endif