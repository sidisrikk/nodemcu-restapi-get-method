/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;


// ****** CONFIG ******
String API_ADDR = "https://www.mocky.io/v2/5d0dd5913400004d00ca4a8e";
char * WIFI_NAME = "wifiname1234";
char * WIFI_PASS = "password1234";
// ****** END CONFIG ******



void setup() {

    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP(WIFI_NAME, WIFI_PASS);

}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        http.begin(API_ADDR); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
}
