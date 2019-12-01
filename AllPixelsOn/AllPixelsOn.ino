#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "Arduino.h"

#include "esp32-hal.h"

#define START_SEG 6
#define DATA_SEG 90*3
#define END_SEG 14
#define WAITTIME 1400

#define DATA_SIZE (START_SEG + DATA_SEG + END_SEG)

const rmt_data_t startbit1[] = { {7, 1, 1713, 0}, {5, 0, 5, 0}, {5, 0, 5, 0}, {7, 1, 293, 0}, {5, 0, 5, 0}, {5, 0, 5, 0} };
const rmt_data_t startbit2[] = { {11, 1, 68, 0}, {11, 1, 1639, 0}, {5, 0, 5, 0}, {11, 1, 69, 0}, {11, 1, 223, 0}, {5, 0, 5, 0} };
const rmt_data_t startbit3[] = { {11, 1, 59, 0}, {11, 1, 1649, 0}, {5, 0, 5, 0}, {11, 1, 60, 0}, {11, 1, 230, 0}, {5, 0, 5, 0} };
const rmt_data_t startbit4[] = { {11, 1, 59, 0}, {18, 1, 1642, 0}, {5, 0, 5, 0}, {11, 1, 60, 0}, {18, 1, 223, 0}, {5, 0, 5, 0} };
const rmt_data_t startbit5[] = { {11, 1, 52, 0}, {11, 1, 1657, 0}, {5, 0, 5, 0}, {11, 1, 51, 0}, {11, 1, 239, 0}, {5, 0, 5, 0} };
const rmt_data_t startbit6[] = { {11, 1, 52, 0}, {10, 1, 8, 0}, {11, 1, 1649, 0}, {11, 1, 51, 0}, {10, 1, 8, 0}, {11, 1, 231, 0} };
const rmt_data_t startbit7[] = { {11, 1, 52, 0}, {18, 1, 1652, 0}, {5, 0, 5, 0}, {11, 1, 50, 0}, {18, 1, 232, 0}, {5, 0, 5, 0} };


const rmt_data_t endbit1[] = { {10, 1, 34, 0}, {10, 1, 614, 0}, {8, 0, 8, 0}, {8, 0, 8, 0},  {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 442, 0}, {9, 1, 18, 0}, {9, 1, 260, 0}, {9, 1, 27, 0}, {9, 1, 16, 0}, {9, 0, 9, 0}, {9, 0, 9, 0} };
const rmt_data_t endbit2[] = { {8, 1, 36, 0}, {9, 1, 25, 0}, {9, 1, 596, 0}, {8, 0, 8, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 442, 0}, {9, 1, 18, 0}, {9, 1, 260, 0}, {9, 1, 27, 0}, {9, 1, 36, 0}, {9, 1, 9, 0}, {9, 0, 9, 0} };
const rmt_data_t endbit3[] = { {9, 1, 35, 0}, {9, 1, 16, 0}, {9, 1, 605, 0}, {8, 0, 8, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 442, 0}, {9, 1, 18, 0}, {9, 1, 260, 0}, {9, 1, 27, 0}, {9, 1, 26, 0}, {9, 1, 9, 0}, {9, 0, 9, 0} };
const rmt_data_t endbit4[] = { {9, 1, 35, 0}, {9, 1, 18, 0}, {18, 1, 594, 0}, {8, 0, 8, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 442, 0}, {9, 1, 18, 0}, {9, 1, 260, 0}, {9, 1, 27, 0}, {9, 1, 26, 0}, {16, 1, 9, 0}, {9, 0, 9, 0} };
const rmt_data_t endbit5[] = { {10, 1, 34, 0}, {9, 1, 8, 0}, {9, 1, 614, 0}, {8, 0, 8, 0},  {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 442, 0}, {9, 1, 18, 0}, {9, 1, 260, 0}, {9, 1, 27, 0}, {9, 1, 18, 0}, {9, 1, 9, 0}, {9, 0, 9, 0} };
const rmt_data_t endbit6[] = { {9, 1, 35, 0}, {9, 1, 8, 0}, {9, 1, 9, 0}, {8, 1, 612, 0},  {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 442, 0}, {9, 1, 18, 0}, {9, 1, 260, 0}, {9, 1, 27, 0}, {9, 1, 18, 0}, {9, 1, 10, 0}, {9, 1, 9, 0} };
const rmt_data_t endbit7[] = { {10, 1, 35, 0}, {9, 1, 8, 0}, {16, 1, 614, 0}, {8, 0, 8, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 256, 0}, {88,  1, 442, 0}, {9, 1, 18, 0}, {9, 1, 260, 0}, {9, 1, 27, 0}, {9, 1, 18, 0}, {16, 1, 9, 0}, {9, 0, 9, 0} };



rmt_data_t* led_data;

rmt_obj_t* rmt_send = NULL;

void setup() {
  Serial.begin(115200);
  if ((rmt_send = rmtInit(18, true, RMT_MEM_64)) == NULL)
  {
    Serial.println("init sender failed\n");
  }
  float realTick = rmtSetTick(rmt_send, 25);
  Serial.printf("real tick set to: %fns\n", realTick);

  led_data = (rmt_data_t*) malloc(sizeof(rmt_data_t)*DATA_SIZE);
}

//each packet of data is 1ms long, followed by a low pulse of 1.5ms
int led_index = 0;

void loop() {
  int led;
  for(led=0; led < DATA_SEG; led++)
  {
    //we need to pulse the led for 3us
    // high should be 2.16us high, period 2,94
    // low should be 0.43us high, period 2.94us
    led_data[START_SEG + led].level0 = 1;
    led_data[START_SEG + led].duration0 = 86;
    led_data[START_SEG + led].level1 = 0;
    led_data[START_SEG + led].duration1 = 32;
  }
  
  led_data[START_SEG + DATA_SEG - 1].level0 = 1;
  led_data[START_SEG + DATA_SEG - 1].duration0 = 86;
  led_data[START_SEG + DATA_SEG - 1].level1 = 0;
  led_data[START_SEG + DATA_SEG - 1].duration1 = 600;



  memcpy(led_data, startbit1, sizeof(rmt_data_t)*START_SEG);
  memcpy(led_data + (DATA_SIZE - END_SEG), endbit1, sizeof(rmt_data_t)*(END_SEG));
  rmtWrite(rmt_send, led_data, DATA_SIZE);
  delayMicroseconds(1400);
  
  memcpy(led_data, startbit2, sizeof(rmt_data_t)*START_SEG);
  memcpy(led_data + (DATA_SIZE - END_SEG), endbit2, sizeof(rmt_data_t)*(END_SEG));
  rmtWrite(rmt_send, led_data, DATA_SIZE);
  delayMicroseconds(1400);

  memcpy(led_data, startbit3, sizeof(rmt_data_t)*START_SEG);
  memcpy(led_data + (DATA_SIZE - END_SEG), endbit3, sizeof(rmt_data_t)*(END_SEG));
  rmtWrite(rmt_send, led_data, DATA_SIZE);
  delayMicroseconds(1400);

  memcpy(led_data, startbit4, sizeof(rmt_data_t)*START_SEG);
  memcpy(led_data + (DATA_SIZE - END_SEG), endbit4, sizeof(rmt_data_t)*(END_SEG));
  rmtWrite(rmt_send, led_data, DATA_SIZE);
  delayMicroseconds(1400);

  memcpy(led_data, startbit5, sizeof(rmt_data_t)*START_SEG);
  memcpy(led_data + (DATA_SIZE - END_SEG), endbit5, sizeof(rmt_data_t)*(END_SEG));
  rmtWrite(rmt_send, led_data, DATA_SIZE);
  delayMicroseconds(1400);

  memcpy(led_data, startbit6, sizeof(rmt_data_t)*START_SEG);
  memcpy(led_data + (DATA_SIZE - END_SEG), endbit6, sizeof(rmt_data_t)*(END_SEG));
  rmtWrite(rmt_send, led_data, DATA_SIZE);
  delayMicroseconds(1400);

  memcpy(led_data, startbit7, sizeof(rmt_data_t)*START_SEG);
  memcpy(led_data + (DATA_SIZE - END_SEG), endbit7, sizeof(rmt_data_t)*(END_SEG));
  rmtWrite(rmt_send, led_data, DATA_SIZE);
  delayMicroseconds(1400);
 
  
  //Serial.printf("data written to RMT: %s (%d)\n", dataWritten ? "YES":"NO", sizeof(rmt_data_t)*START_SEG);
}

