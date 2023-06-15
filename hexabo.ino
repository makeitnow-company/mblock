#define BLYNK_TEMPLATE_ID "TMPL7c5cpsrX"
#define BLYNK_TEMPLATE_NAME "START"
#define BLYNK_AUTH_TOKEN "s8stKUc_seJBt8A7yvKbwzfaA8ybV-Zv"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include "BlynkSimpleShieldEsp8266.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KT_GiGA_2G_makeitnow";
char pass[] = "makeitnow1";

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(7, 8); // RX, TX

#define ESP8266_BAUD 38400

ESP8266 wifi(&EspSerial);

void setup()
{
  Serial.begin(9600);

  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass, "blynk.cloud", 80);
}

void loop()
{
  Blynk.run();
}
