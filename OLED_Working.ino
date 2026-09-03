// Add the Modules required
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Dealing with date and WiFi
#include <WiFi.h>
#include "time.h"

// Non-volatile storage
#include <Preferences.h>

// Determining the screen size
#define WIDTH 128
#define HEIGHT 64

// Declaration for SSD1306 display using I2C
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

// WiFi credentials
const char* ssid = "wifi-username";
const char* password = "wifi-password";

// NTP Server and Timezone
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;        // Standard GMT offset in seconds
const int daylightOffset_sec = 3600;  // Daylight savings offset in seconds

// Uptime variables
Preferences preferences;
unsigned long historicalUptime = 0; // Cumulative uptime from previous boots in seconds
unsigned long lastSaveTime = 0; // tracking interval saves
const unsigned long SAVE_INTERVAL = 600000; // 10 minutes

void settingsDisplay();
void settingsWiFi();
void settings();
void getNetworkTime();
void updateUpTime();
unsigned long getTotalUptimeSeconds();

void setup() {
  Serial.begin(115200);

  // Load saved uptime from memory
  preferences.begin("uptime", false);
  historicalUptime = preferences.getULong("total_sec", 0);
  settings();
}

void loop() {
  getNetworkTime();
  delay(10000); // Update display every 10 seconds
}

void settings() {
  settingsDisplay();
  settingsWiFi();
}

// setting up display options
void settingsDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Do not proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Display Initialized");
  display.display();
  delay(1000);
}

// setting up wifi options
void settingsWiFi() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Connecting to WiFi");
  display.display();

  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    display.print(".");
    display.display();
    attempts++;
  }

  display.clearDisplay();
  display.setCursor(0, 0);

  if (WiFi.status() == WL_CONNECTED) {
    display.println("WiFi Connected!");
    display.display();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  } else {
    display.println("Connection Failed!");
    display.display();
  }
  delay(2000);
}

void updateUptime(){
  unsigned long currentMillis = millis();

  // Save to flash every minute
  if (currentMillis - lastSaveTime >= SAVE_INTERVAL) {
    // Add 600 seconds to historical uptime
    historicalUptime += (SAVE_INTERVAL / 1000);
    preferences.putULong("total_sec", historicalUptime);

    lastSaveTime = currentMillis;
    }
}

unsigned long getTotalUptimeSeconds() {
  unsigned long currentMillis = millis();
  unsigned long unsavedSec = (currentMillis - lastSaveTime) / 1000;

  return historicalUptime + unsavedSec;
}

// calling the network to discover the time
void getNetworkTime() {
  struct tm timeinfo;

  display.clearDisplay();
  display.setCursor(0, 0);

  if (!getLocalTime(&timeinfo)) {
    display.println("Failed to obtain time");
    display.display();
    return;
  }

  // Format date and time onto separate lines to fit 128x64 pixels
  char dateStr[20];
  char timeStr[10];

  strftime(dateStr, sizeof(dateStr), "%a, %b %d %Y", &timeinfo);
  strftime(timeStr, sizeof(timeStr), "%H:%M", &timeinfo);

  // controls the date
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(dateStr);

  // centered time
  display.setCursor(35, 24);
  display.setTextSize(2); // Larger font for clock
  display.println(timeStr);

  // Total calculated cumulative operational time
  unsigned long totalSec = getTotalUptimeSeconds();
  unsigned long days = totalSec / 86400;
  unsigned long hours = (totalSec % 86400) / 3600;
  unsigned long minutes = (totalSec % 3600) / 60;

  // Display total Uptime at the bottom
  display.setTextSize(1);
  display.setCursor(15, 48);
  display.printf("Up: %lu d %lu h %lu m", days, hours, minutes);

  display.display(); // Push buffer to physical screen
}

