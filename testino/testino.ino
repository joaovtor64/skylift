/*
  PARALLEL ARTIFACTS
  https://ahprojects.com/parallel-artifacts
  Adam Harvey 2022
*/

// Auto-generated from: wtf
#define DEBUG 1
#include "display.h"

byte bssid[6] = {};        // store next bssid
uint8_t ncounter = 0;      // network counter
uint8_t ch_counter = 0;    // channel increment counter
uint8_t loop_counter = 0;  // loop counter interval for changing channel
uint8_t ssid_len = 0;      // holder for ssid length
uint8_t channel_pre = 0;
uint8_t packet_length = 0;

// beacon interval is 100.24 milliseconds (0x64)
unsigned long beacon_interval_us = 1024;
unsigned long last_beacon_us = 0;
char* hidden_ssid = "\x00";  // 0-length SSID (Network name unavailable)
#define NUM_TS_PLACES 8
byte time_packet[NUM_TS_PLACES];  // placeholder for timestamp data#define NUM_TS_PLACES 8
char cc[2];                       // placeholer for timestamp data




float WIFI_POWER_DBM = 19.5;  // ESP8266 only




// ---------------------------------------------------------
// START template data
// ---------------------------------------------------------
#define ESP32 1

#ifdef ESP32
#include "WiFi.h"
extern "C" {
#include "esp_wifi.h"
  esp_err_t esp_wifi_set_channel(uint8_t primary, wifi_second_chan_t second);
  esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void* buffer, int len, bool en_sys_seq);
}
#else
#include <ESP8266WiFi.h>
extern "C" {
#include "user_interface.h"
}
#endif

// #define USE_HIDDEN_SSIDS

#define NN 40
char* ssids[NN] = {
	"Rede de Peixe", 
	"Ruth", 
	"Joao Baltazar ", 
	"Ana Beatriz 2G", 
	"#NET-CLARO-WIFI", 
	"#NET-CLARO-WIFI", 
	"BAND2.4", 
	"Rossana", 
	"nao", 
	"sanhudo", 
	"#NET-CLARO-WIFI", 
	"MOXA_2", 
	"00:12:0E:97:CE:22", 
	"TP-LINK", 
	"linksys", 
	"dlink", 
	"Ana ", 
	"Armagedon", 
	"atanaka", 
	"wi-fi home", 
	"FAMILIA", 
	"Gabi Viveiro Net", 
	"Galaxy A03s6b9e", 
	"silvana", 
	"ricardo", 
	"MOTOROLA-5F34A", 
	"PacovÃ¡", 
	"Trojan_2014", 
	"BRUNO", 
	"#NET-CLARO-WIFI", 
	"baltazarjoao", 
	"ENGENHARIA_CURY", 
	"#NET-CLARO-WIFI", 
	"INTELBRAS", 
	"DOBI", 
	"Paludetti", 
	"SEM_BARULHO", 
	"2G_PESSOTTI", 
	"Thom_D017943", 
	"Neguinho", 
};

uint8_t ssid_lengths[NN] = {
	13, 
	4, 
	14, 
	14, 
	15, 
	15, 
	7, 
	7, 
	3, 
	7, 
	15, 
	6, 
	17, 
	7, 
	7, 
	5, 
	4, 
	9, 
	7, 
	10, 
	7, 
	16, 
	15, 
	7, 
	7, 
	14, 
	7, 
	11, 
	5, 
	15, 
	12, 
	15, 
	15, 
	9, 
	4, 
	9, 
	11, 
	11, 
	12, 
	8, 
};

byte bssids[NN][6] = {
	{0x50, 0xC7, 0xBF, 0xE8, 0xC3, 0x38}, 
	{0x10, 0xBE, 0xF5, 0xD2, 0xA7, 0x3C}, 
	{0x5C, 0xE3, 0x0E, 0x14, 0xCD, 0xDC}, 
	{0x5C, 0xE3, 0x0E, 0x12, 0x3E, 0x0E}, 
	{0x5E, 0xE3, 0x0E, 0x22, 0x3E, 0x0E}, 
	{0x5E, 0xE3, 0x0E, 0x25, 0x55, 0xE1}, 
	{0x14, 0xCC, 0x20, 0x51, 0x01, 0x47}, 
	{0x38, 0x6B, 0xBB, 0x46, 0x65, 0x1D}, 
	{0x52, 0x92, 0xB9, 0xE3, 0x08, 0x82}, 
	{0x28, 0x32, 0xC5, 0x1B, 0x6F, 0xB0}, 
	{0x4E, 0xD0, 0x8A, 0x1F, 0x6C, 0xF9}, 
	{0x46, 0x90, 0xE8, 0x4B, 0x79, 0x63}, 
	{0x00, 0x12, 0x0E, 0x97, 0xCE, 0x22}, 
	{0x00, 0x14, 0x78, 0x52, 0x27, 0x42}, 
	{0x00, 0x16, 0xB6, 0xA6, 0xE5, 0x26}, 
	{0x00, 0x19, 0x5B, 0xD6, 0x78, 0x82}, 
	{0x00, 0x19, 0xE0, 0xA4, 0x9C, 0x2E}, 
	{0x00, 0x25, 0x86, 0xDC, 0x71, 0x56}, 
	{0x20, 0xAA, 0x4B, 0x42, 0x5F, 0x8B}, 
	{0x1C, 0x7E, 0xE5, 0x41, 0x64, 0x86}, 
	{0x40, 0x75, 0xC3, 0xB7, 0x6C, 0x20}, 
	{0x00, 0x1D, 0xD4, 0xD7, 0x77, 0xD0}, 
	{0x12, 0x57, 0x3A, 0x56, 0x75, 0x90}, 
	{0x00, 0x24, 0x01, 0x17, 0x36, 0x67}, 
	{0x28, 0xBE, 0x9B, 0x6F, 0xAD, 0xEF}, 
	{0x40, 0xB7, 0xF3, 0xF9, 0xE9, 0x09}, 
	{0x72, 0xC9, 0xE3, 0x49, 0xC8, 0xE4}, 
	{0x10, 0xFE, 0xED, 0x31, 0x72, 0xD8}, 
	{0x78, 0x91, 0xE9, 0x05, 0x70, 0xD1}, 
	{0x5E, 0xE3, 0x0E, 0x28, 0x83, 0xE3}, 
	{0x00, 0x1D, 0xD4, 0xDC, 0x2B, 0x60}, 
	{0x54, 0xAF, 0x97, 0xE3, 0x25, 0x42}, 
	{0x5E, 0xE3, 0x0E, 0x22, 0xF1, 0x61}, 
	{0x44, 0x3B, 0x32, 0x70, 0x31, 0x6F}, 
	{0x5C, 0x57, 0x1A, 0xDE, 0xAE, 0xB0}, 
	{0x00, 0x24, 0xB2, 0xBA, 0x00, 0x30}, 
	{0x00, 0x1A, 0x3F, 0x4B, 0xE3, 0xF2}, 
	{0x18, 0x34, 0xAF, 0x27, 0x56, 0x68}, 
	{0x28, 0xBE, 0x9B, 0x8E, 0x53, 0xE4}, 
	{0x44, 0x89, 0x6D, 0x1C, 0x29, 0xBF}, 
};
int powers[NN] = {
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	-4, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
	8, 
};
#define N_CHANNELS 40
byte channels[N_CHANNELS] = {8, 11, 6, 6, 6, 6, 1, 11, 11, 11, 11, 11, 9, 6, 6, 6, 11, 6, 1, 2, 1, 11, 6, 2, 6, 11, 3, 6, 1, 8, 6, 6, 6, 11, 11, 1, 11, 1, 6, 11};


// ---------------------------------------------------------
// END template data
// ---------------------------------------------------------


// Variables referencing templated data
uint8_t channel = channels[0];  // Transmit on this channel
unsigned long ap_epochs[NN];

// Beacon frame packet structure
uint8_t packet[128] = {
  /*0*/ 0x80, 0x00,                                       // Frame Control
  /*2*/ 0x00, 0x00,                                       // Duration
  /*4*/ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,               // Destination address
  /*10*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,              // Source address - overwritten later
  /*16*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,              // BSSID - overwritten to the same as the source address
  /*22*/ 0xc0, 0x6c,                                      // Seq-ctl
  /*24*/ 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,  // Timestamp - the number of microseconds the AP has been active
  /*32*/ 0x64, 0x00,                                      // Beacon interval = 0.102400 seconds
                                                          // /*34*/ 0x01, 0x04,                                    // Capability info
  /*34*/ 0x31, 0x14,                                      // Capability inf
  /*36*/ 0x00
  /* SSID is added after here */
};

uint8_t packet_tail[13] = {
  0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c,  // supported rate
  0x03, 0x01, 0x04                                             // DSSS (Current Channel)
};


// ---------------------------------------------------------------
// Convert milliseconds to timestamp for beacon frame
// ---------------------------------------------------------------
void get_timestamp(char* times) {

  long t = micros();
  unsigned int tlen = 8;
  String time_hex_forward = String(t, HEX);

  while (time_hex_forward.length() < tlen * 2) time_hex_forward = "0" + time_hex_forward;
  String time_hex_rev = time_hex_forward;  // reversed
  for (int i = tlen; i > 0; i--) {
    time_hex_rev[(tlen * 2) - (i * 2)] = time_hex_forward.charAt((i * 2) - 2);      // 1
    time_hex_rev[(tlen * 2) - (i * 2) + 1] = time_hex_forward.charAt((i * 2) - 1);  // 2
  }
  // convert to 8-length byte array
  for (int i = 0; i < tlen; i++) {

    cc[0] = time_hex_rev.charAt(i * 2);
    cc[1] = time_hex_rev.charAt((i * 2) + 1);
    long hex_val = strtol(cc, NULL, 16);
    times[i] = hex_val;
  }
}

void set_timestamp(byte* p, byte n) {
  // return time in reverse order as byte array pointer
  long t = millis() + ap_epochs[n];  // random start time
  p[0] = (t & 0x00000000000000FF);
  p[1] = (t & 0x000000000000FF00) >> 8;
  p[2] = (t & 0x0000000000FF0000) >> 16;
  p[3] = (t & 0x00000000FF000000) >> 24;
  p[4] = (t & 0x000000FF00000000) >> 32;
  p[5] = (t & 0x0000FF0000000000) >> 40;
  p[6] = (t & 0x00FF000000000000) >> 48;
  p[7] = (t & 0x00FF000000000000) >> 56;
}


long strtol(const char* __nptr, char** __endptr, int __base);  // additional function for string to long conversion


// ---------------------------------------------------------------
// Send the beacon frame
// ---------------------------------------------------------------
void send_beacon_frame(uint8_t i, uint8_t c) {
  WiFi.setTxPower((wifi_power_t)powers[i]);
  // Set BSSID
  memcpy(&bssid, bssids[i], 6);
  memcpy(&packet[10], bssid, 6);
  memcpy(&packet[16], bssid, 6);

  // Set SSID
  ssid_len = ssid_lengths[i];
  packet[37] = ssid_len;
  memcpy(&packet[38], ssids[i], ssid_len);
  memcpy(&packet[38 + ssid_len], packet_tail, 13);
  packet[50 + ssid_len] = channels[c];

  // store new packet length
  packet_length = 51 + ssid_len;
  #ifdef DEBUG
  Serial.print( ssids[i]);
  Serial.print( ", Channel: ");
  Serial.println(channels[c]);
  #endif
  // Send the packet
#ifdef ESP32
  esp_wifi_80211_tx(WIFI_IF_STA, packet, packet_length, 0);  // esp32
#else
  wifi_send_pkt_freedom(packet, packet_length, 0);  // esp8266
#endif
}


void change_channel(uint8_t i) {
#ifdef ESP32
  // esp_wifi_set_promiscuous(false);
  esp_wifi_set_channel(channels[i], WIFI_SECOND_CHAN_NONE);  // esp32
  // esp_wifi_set_promiscuous(true);
#else
  wifi_set_channel(channels[i]);                    // esp8266
#endif
}


// ---------------------------------------------------------------
// Initialize the ESP8266
// Set max power and put into promiscious mode
// ---------------------------------------------------------------
void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
    pinMode(2,OUTPUT);
    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
    delay(10000);

  #endif

  //setup_display();
#ifdef ESP32
  WiFi.mode(WIFI_MODE_STA);
  WiFi.setTxPower(WIFI_POWER_21dBm);
  esp_wifi_set_channel(channels[0], WIFI_SECOND_CHAN_NONE);
#else
  WiFi.setOutputPower(WIFI_POWER_DBM);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
#endif
}

// ---------------------------------------------------------------
// Transmit Beacon Frame
// ---------------------------------------------------------------
void loop() {
  
  // Limit to every 100ms
  if (micros() - last_beacon_us < beacon_interval_us) {
    //return;
  }

  // change channel every loop
  loop_counter += 1;
  if (loop_counter > 10) {
    ch_counter = (ch_counter + 1) % N_CHANNELS;
    
    loop_counter = 0;
  }
  
  // Send all ssid packets
  for (int i = 0; i < NN; i++) {
    change_channel(i);
    send_beacon_frame(i, i);
    delay(1);
  }

  // update time of broadcast
  last_beacon_us = micros();

  // display
  //run_display();
}