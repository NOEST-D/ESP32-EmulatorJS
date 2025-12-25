#include <M5Cardputer.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SD.h>
#include <Ticker.h>

AsyncWebServer server(80);

// Screen blanking Ticker variables
Ticker blankTicker;
bool screenBlanked = false;

// Global Wi-Fi credentials
String STA_SSID;
String STA_PASS;
String AP_SSID;
String AP_PASS;
String AP_CH;

// Function to load Wi-Fi credentials from SD card
void loadWiFiCreds() {
  File f = SD.open("/ESP32EJS/creds.txt");
  if (!f) {
    M5.Lcd.println("WiFi: FAILED (no creds.txt)\nExecution stopped.");
    while (true) delay(1000);
  }

  while (f.available()) {
    String line = f.readStringUntil('\n');
    line.trim();
    if (line.startsWith("STA_SSID=")) STA_SSID = line.substring(9);
    else if (line.startsWith("STA_PASS=")) STA_PASS = line.substring(9);
    else if (line.startsWith("AP_SSID=")) AP_SSID = line.substring(8);
    else if (line.startsWith("AP_PASS=")) AP_PASS = line.substring(8);
    else if (line.startsWith("AP_CH=")) AP_CH = line.substring(6);
  }

  f.close();
  if (STA_SSID.length() == 0 || STA_PASS.length() == 0 || AP_SSID.length() == 0 || AP_PASS.length() == 0 || AP_CH.length() == 0) {
    M5.Lcd.println("WiFi: FAILED (incomplete creds.txt)\nExecution stopped.");
    while (true) delay(1000);
  } else {
    M5.Lcd.println("WiFi: creds.txt LOADED");
  }
}

// Function to start WiFi mode based on if G0 is pressed
void setupWiFi(bool apMode) {
  if (apMode) {
    // AP MODE
    M5.Lcd.println("WiFi: AP-MODE");
    WiFi.mode(WIFI_AP);
    int channel = AP_CH.toInt();
    if (channel < 1 || channel > 13) channel = 6;  // default channel
    WiFi.softAP(AP_SSID.c_str(), AP_PASS.c_str(), channel);

  } else {
    // STA MODE
    WiFi.mode(WIFI_STA);
    M5.Lcd.println("WiFi: STA-MODE");
    M5.Lcd.print("WiFi: Connecting to ");
    M5.Lcd.print(STA_SSID);

    WiFi.begin(STA_SSID.c_str(), STA_PASS.c_str());
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      M5.Lcd.print(".");
      if (millis() - start > 20000) {
        M5.Lcd.println("\nWiFi: FAILED (connection err)\nExecution stopped.");
        while (true) delay(1000);
      }
    }

    M5.Lcd.println("\nWiFi: SETUP was successful");
  }
}

void setup() {
  M5.begin();
  M5.Lcd.println("Starting up...");

  //Check for 5 seconds if G0 is pressed --> if yes turn on AP MODE
  M5.Lcd.print("Press G0 to start AP-MODE (");
  unsigned long t = millis();
  bool apMode = false;
  bool firstNUM = true;
  int countOldValue = 6;
  while (millis() - t < 6000 && apMode == false && countOldValue != 0) {
    M5.update();
    apMode = M5.BtnA.isPressed();
    int count = (6000 - (millis() - t)) / 1000;
    if (count != countOldValue) {
      countOldValue = count;
      if (!firstNUM) M5.Lcd.print(" ");
      M5.Lcd.print(countOldValue);
      if (countOldValue == 1) countOldValue = 0;
      firstNUM = false;
    }
  }
  M5.Lcd.println(")");

  // Start Ticker for screen StandBy
  blankTicker.once(60, []() {
    screenBlanked = true;
    M5.Lcd.sleep();
  });

  // SD mount
  if (!SD.begin()) {
    M5.Lcd.println("SD: mount FAILED\nExecution stopped.");
    while (true) delay(1000);
  }
  M5.Lcd.println("SD: MOUNTED");

  // Loading creds and setting WiFi up
  loadWiFiCreds();
  setupWiFi(apMode);

  // Serve the main HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SD, "/ESP32EJS/index.html", "text/html");
  });

  // Serve EmulatorJS files
  server.serveStatic("/data", SD, "/ESP32EJS/data");

  // Serve ROMs folder
  server.serveStatic("/roms", SD, "/ESP32EJS/roms");

  // Serve favicon
  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SD, "/ESP32EJS/favicon.ico", "image/x-icon");
  });

  // Serve ROM list as JSON
  server.on("/romlist", HTTP_GET, [](AsyncWebServerRequest *request) {
    File root = SD.open("/ESP32EJS/roms");
    String list = "[";
    bool firstROM = true;
    File file = root.openNextFile();
    while (file) {
      if (!file.isDirectory()) {
        if (!firstROM) list += ",";
        list += "\"" + String(file.name()) + "\"";
        firstROM = false;
      }
      file = root.openNextFile();
    }
    list += "]";
    request->send(200, "application/json", list);
  });

  server.begin();
  M5.Lcd.println("Server started!");
  if (apMode) {
    M5.Lcd.print("\n");

    M5.Lcd.print("SSID: ");
    M5.Lcd.println(AP_SSID);
    M5.Lcd.print("PASS: ");
    M5.Lcd.println(AP_PASS);
    M5.Lcd.print("CH:   ");
    M5.Lcd.println(AP_CH);
    M5.Lcd.print("\n");
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("IP:");
    M5.Lcd.println(WiFi.softAPIP());
  } else {
    M5.Lcd.print("\n");
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("IP:");
    M5.Lcd.println(WiFi.localIP());
  }
}

void loop() {
  M5.update();

  if (screenBlanked && (M5.BtnA.wasPressed())) {
    screenBlanked = false;
    M5.Lcd.wakeup();
    // reset blank timer
    blankTicker.detach();
    blankTicker.once(60, []() {
      screenBlanked = true;
      M5.Lcd.sleep();
    });
  }
}
