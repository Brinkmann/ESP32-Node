#include <Arduino.h>
#include <esp_cpu.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp32-hal-log.h"
#include "src/SystemTypes.h"
#include "src/SystemSettings.h"
#include "src/DeviceModel.h"

/**
 * @brief To erase all flash i.e 
 * * esptool --port COM5 --chip esp32s3 erase_flash
 * */

#ifndef MAIN_LOOP_SLEEP_TIME
#define MAIN_LOOP_SLEEP_TIME 2000 
#endif


FeqDeviceModelType* device = nullptr;

static void setDeviceMcuSpeed(void){

  setCpuFrequencyMhz(ESP32_CLOCK_SPEED_WIFI_BLE);
  log_i("System clock frequency %d MHz",getCpuFrequencyMhz());

}

static void disableBrownOutReset(void){

  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
}

static void initDeviceModel(void){

  static FeqDeviceModelType deviceModel;
  memset(&deviceModel,0,sizeof(FeqDeviceModelType));
  device = &deviceModel;

}

static void initDeviceHardware(void){

  disableBrownOutReset();
  setDeviceMcuSpeed();
}

static void initLedStrip(void){

  // Node specific initialization
  static LedStrip ledStrip;
  device->ledStrip = &ledStrip;
  device->ledStrip->init();

}

static void meshNetworkInit(void){

    // Node specific initialization
    static MeshNetwork network;
    device->network = &network;
    device->network->init();

}

void setup(void){

  initDeviceHardware();
  initDeviceModel();
  
  // Initializations
  initLedStrip();
  meshNetworkInit();

}

void loop(void){
  vTaskDelay(pdMS_TO_TICKS(MAIN_LOOP_SLEEP_TIME));
}