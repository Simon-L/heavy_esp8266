#include <i2s.h>
#include <i2s_reg.h>
#include <ESP8266WiFi.h>
#include "Heavy_esp8266.h"

#define SAMPLERATE 16000

float outBuffers[256];
int blockSize = 256; // should be a multiple of 8
HeavyContextInterface *context;
long start;

// Non-blocking I2S write for left and right 16-bit PCM
bool ICACHE_FLASH_ATTR i2s_write_lr_nb(int16_t left, int16_t right){
  int sample = right & 0xFFFF;
  sample = sample << 16;
  sample |= left & 0xFFFF;
  return i2s_write_sample_nb(sample);
}

int bufferlen = -1;
int buffer_index = 0;
void audio_loop()
{
  bool i2s_full = false;

  while (!i2s_full) {
    while (buffer_index < bufferlen) {
      int16_t pcm = (int16_t)(outBuffers[buffer_index] * 32768.0);
      if (i2s_write_lr_nb(pcm, pcm)) {
        buffer_index++;
      }
      else {
        i2s_full = true;
        break;
      }
      if ((buffer_index & 0x3F) == 0) yield();
    }
    if (i2s_full) break;

    start = micros();
    int s = hv_processInline(context, NULL, outBuffers, blockSize);
    Serial.println(micros() - start);
    if (s > 0) {
      bufferlen = s;
      buffer_index = 0;
    }
    else {
      break;
    }
  }
}

void setup()
{
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
  Serial.begin(1000000);Serial.println();


  double sampleRate = (double)(SAMPLERATE);

  context = hv_esp8266_new(sampleRate);

  i2s_begin();
  i2s_set_rate(SAMPLERATE);
}

void loop()
{
  audio_loop();
}
