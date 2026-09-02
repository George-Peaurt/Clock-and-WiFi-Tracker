// Add the Modules required
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Dealing with date and WiFi
#include <WiFi.h>
#include "time.h"

// Determining the screen size
#define WIDTH 128
#define HEIGHT 64

// Declaration for SSD1306 display using I2C
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

// WiFi credentials
const char* ssid = "VM8259023_EXT";
const char* password = "bcdUMetpbyf5brx6";

// NTP Server and Timezone
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;        // Standard GMT offset in seconds
const int daylightOffset_sec = 3600;  // Daylight savings offset in seconds

void settingsDisplay();
void settingsWiFi();
void settings();
void getNetworkTime();

void setup() {
  Serial.begin(115200);
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

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(dateStr);

  display.setCursor(0, 24);
  display.setTextSize(2); // Larger font for clock
  display.println(timeStr);

  display.display(); // Push buffer to physical screen
}