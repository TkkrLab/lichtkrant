#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "Arduino.h"

#include "esp32-hal.h"

#define NR_OF_LEDS   90*3
#define NR_OF_ROWS  7*3

#define NR_OF_END 14
#define NR_OF_START 4

#define NR_OF_ALL_BITS (NR_OF_START + NR_OF_LEDS + NR_OF_END)

rmt_data_t led_data[NR_OF_ALL_BITS];

rmt_obj_t* rmt_send = NULL;

void setup() {
  Serial.begin(115200);
  if ((rmt_send = rmtInit(18, true, RMT_MEM_64)) == NULL)
  {
    Serial.println("init sender failed\n");
  }
  float realTick = rmtSetTick(rmt_send, 100);
  Serial.printf("real tick set to: %fns\n", realTick);
}

//each packet of data is 1ms long, followed by a low pulse of 1.5ms
int led_index = 0;

void loop() {
  int led;
  //writing start
  
  writeStart();

  for(led=0; led < NR_OF_LEDS; led+=2)
  {
    //we need to pulse the led for 3us
    // high should be 2.2us high, 0.8us low
    // low should be 0.5us high, 2.5us low
    led_data[NR_OF_START + led].level0 = 1;
    led_data[NR_OF_START + led].duration0 = 22;
    led_data[NR_OF_START + led].level1 = 0;
    led_data[NR_OF_START + led].duration1 = 8;

    led_data[NR_OF_START + led + 1].level0 = 1;
    led_data[NR_OF_START + led + 1].duration0 = 4;
    led_data[NR_OF_START + led + 1].level1 = 0;
    led_data[NR_OF_START + led + 1].duration1 = 28;
  }
  
  led_data[NR_OF_START + NR_OF_LEDS - 1].level0 = 1;
  led_data[NR_OF_START + NR_OF_LEDS - 1].duration0 = 22;
  led_data[NR_OF_START + NR_OF_LEDS - 1].level1 = 0;
  led_data[NR_OF_START + NR_OF_LEDS - 1].duration1 = 168;
  
  

  writeEnd();

  bool dataWritten = rmtWrite(rmt_send, led_data, NR_OF_ALL_BITS);
  delayMicroseconds(1400);
  Serial.printf("data 1written to RMT: %d\n", dataWritten);
}

void writeStart()
{
  
  //1e bit
  led_data[0].level0 = 1;
  led_data[0].duration0 = 2;
  led_data[0].level1 = 0;
  led_data[0].duration1 = 15;

  //1e bit
  led_data[1].level0 = 1;
  led_data[1].duration0 = 2;
  led_data[1].level1 = 0;
  led_data[1].duration1 = 415;

  //1e bit
  led_data[2].level0 = 1;
  led_data[2].duration0 = 2;
  led_data[2].level1 = 0;
  led_data[2].duration1 = 15;

  //1e bit
  led_data[3].level0 = 1;
  led_data[3].duration0 = 2;
  led_data[3].level1 = 0;
  led_data[3].duration1 = 60; //could be 61

/*
  //1e bit
  led_data[4].level0 = 1;
  led_data[4].duration0 = 5;
  led_data[4].level1 = 0;
  led_data[4].duration1 = 27;

  //1e bit
  led_data[5].level0 = 1;
  led_data[5].duration0 = 4;
  led_data[5].level1 = 0;
  led_data[5].duration1 = 26;
  */
}

void writeEnd()
{
  int offset = NR_OF_START + NR_OF_LEDS;
  led_data[offset+0].level0 = 1;
  led_data[offset+0].duration0 = 2;
  led_data[offset+0].level1 = 0;
  led_data[offset+0].duration1 = 9;
  
  led_data[offset+1].level0 = 1;
  led_data[offset+1].duration0 = 2;
  led_data[offset+1].level1 = 0;
  led_data[offset+1].duration1 = 2;
  
  led_data[offset+2].level0 = 1;
  led_data[offset+2].duration0 = 2;
  led_data[offset+2].level1 = 0;
  led_data[offset+2].duration1 = 2;
  
  led_data[offset+3].level0 = 1;
  led_data[offset+3].duration0 = 2;
  led_data[offset+3].level1 = 0;
  led_data[offset+3].duration1 = 147;
  
  led_data[offset+4].level0 = 1;
  led_data[offset+4].duration0 = 4;
  led_data[offset+4].level1 = 0;
  led_data[offset+4].duration1 = 82;
  
  led_data[offset+5].level0 = 1;
  led_data[offset+5].duration0 = 4;
  led_data[offset+5].level1 = 0;
  led_data[offset+5].duration1 = 82;
  
  led_data[offset+6].level0 = 1;
  led_data[offset+6].duration0 = 4;
  led_data[offset+6].level1 = 0;
  led_data[offset+6].duration1 = 82;
  
  led_data[offset+7].level0 = 1;
  led_data[offset+7].duration0 = 4;
  led_data[offset+7].level1 = 0;
  led_data[offset+7].duration1 = 128;
  
  led_data[offset+8].level0 = 1;
  led_data[offset+8].duration0 = 2;
  led_data[offset+8].level1 = 0;
  led_data[offset+8].duration1 = 5;
  
  led_data[offset+9].level0 = 1;
  led_data[offset+9].duration0 = 2;
  led_data[offset+9].level1 = 0;
  led_data[offset+9].duration1 = 65;
  
  led_data[offset+10].level0 = 1;
  led_data[offset+10].duration0 = 2;
  led_data[offset+10].level1 = 0;
  led_data[offset+10].duration1 = 7;
  
  led_data[offset+11].level0 = 1;
  led_data[offset+11].duration0 = 2;
  led_data[offset+11].level1 = 0;
  led_data[offset+11].duration1 = 4;
  
  led_data[offset+12].level0 = 1;
  led_data[offset+12].duration0 = 2;
  led_data[offset+12].level1 = 0;
  led_data[offset+12].duration1 = 2;
  
  led_data[offset+13].level0 = 1;
  led_data[offset+13].duration0 = 2;
  led_data[offset+13].level1 = 0;
  led_data[offset+13].duration1 = 10;
}

