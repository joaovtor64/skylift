/*
  S K Y L I F T (Version 1.0)
  Wi-Fi Geolocation Spoofing Device using ESP8266
  Adam Harvey 2016-2018
  Code: https://github.com/adamhrv/skylift
  About: https://ahprojects.com/skylift
  Projects: https://ahprojects.com/datapools
  
  Settings:
  CPU Frequency: 80MHz
  Board: ESP8266 NodeMCU 1.0 (ESP-12E Module)
  Flash size: 4M
*/
// Approximate D-pin mapping for DOIT ESP32 DevKit v1
#define D0  3    // RX0
#define D1  1    // TX0
#define D2  2
#define D3  0
#define D4  4
#define D5  5
#define D6  18
#define D7  19
#define D8  21
#define D9  22
#define D10 23
#define D11 13
#define D12 12
#define D13 14
#define D14 27
#define D15 26
#define D16 25
#define D17 33
#define D18 32
#define D19 35  // Input only
#define D20 34  // Input only
#define D21 39  // Input only (also known as SVP)
#define D22 36  // Input only (also known as SVN)


// START AUTO-GENERATED VARIABLES
const unsigned int NPLACES = 5;
const unsigned int NNETS = 75;
// END AUTO-GENERATED VARIABLES

// Globals
const String DEV_VERSION = "V 1.0";
char* ssids[NNETS];
byte bssids[NNETS][6];
byte channels[NNETS];
byte rssis[NNETS];
unsigned int idx_offsets[NPLACES];
String place_names[NPLACES];
String place_cities[NPLACES];
unsigned int place_idx_cur = 1; // overwritten by EEPROM value
boolean wifi_tx_status = 1; // 1 = ON, 0 = OFF, overwritten by EEPROM value


// include memory, then networks
#include "memory.h" // first
#include "networks.h" // second

// include display, switches, wifi
#include "display.h"
#include "switches.h"
#include "wifi.h"

void setup() {
  setup_memory();
  setup_networks();
//  setup_switches();
//  setup_display();
  setup_wifi();
}

void loop() {
  run_memory();
//  run_switches();
//  run_display();
  run_wifi();
}
