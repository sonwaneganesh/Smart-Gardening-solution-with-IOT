// Adafruit IO Temperature & Humidity Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-temperature-and-humidity
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016-2017 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here ******************************
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
*/
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
// #define moist_dpin 0    // Moisture pinn
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 

const int moist_dpin = A0; // sensor input at Analog pin A0
int value = 0;
// set up the 'temperature' and 'humidity' feeds
AdafruitIO_Feed *temperature = io.feed("temperature");
AdafruitIO_Feed *humidity = io.feed("humidity");
AdafruitIO_Feed *moisture = io.feed("moisture");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // initialize dht22
  dht.begin();

  //setup moisture sensor
  //pinMode(moist_dpin, INPUT);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

    float hum = dht.readHumidity();
    float temp = dht.readTemperature(); 
    float moist = (100.0 - ((analogRead(moist_dpin)/1023.00) * 100.0 ));
  Serial.print("celsius: ");
  Serial.print(temp);
  Serial.println("C");

  // save fahrenheit (or celsius) to Adafruit IO
  temperature->save(temp);

  Serial.print("humidity: ");
  Serial.print(hum);
  Serial.println("%");

  // save moisture to Adafruit IO
  humidity->save(hum);

   Serial.print("moisture: ");
  Serial.print(moist);
  Serial.println("%\n");

  // save humidity to Adafruit IO
  moisture->save(moist);

  // wait 5 seconds (5000 milliseconds == 5 seconds)
  delay(10000);

}
