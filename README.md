# Heavy patches on ESP8266

## How to
Download as zip and extract in your Arduino sketchbook folder, rename and remove "-master" then start the Arduino IDE and open "heavy_esp8266" from the sketchbook menu.  
Set the ESP8266 **core frequency to 160MHz** in the Tools menu.  
Even without an I2S DAC, Serial will print the processing time of one block in microseconds, on every block, you can test performance this way. Note: Serial rate is set at 1000000.

In my case, pinout was as follow:

| Wemos D1 Mini (Pro)  | I2S DAC |
| ------------- | ------------- |
| 5V/3.3V  | Vcc  |
| GND  | GND  |
| RX  | Data  |
| D8  | BCLK |
| D4  | LRCLK/WCK |


#### Aknowledgments:
  * Patch in this sketch is: https://enzienaudio.com/h/FergusL/esp8266/
  * Based on https://github.com/bbx10/SFX-I2S-web-trigger/


As of 05-18-18 this is as far as I have *tried* to push the ESP8266. This patch has random, a few oscillators, noise and even a filter!  
Lots of improvements are still possible.

Good to see this super inexpensive chip can be used for this, as it doesn't even have a floating point unit!

The Heavy code running is exactly as returned by the cloud!

-----------

Powered by ![Powered by Heavy](https://enzienaudio.com/static/img/heavy_logo_prod_wtxt.svg)
