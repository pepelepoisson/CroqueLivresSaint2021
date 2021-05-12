// To do:
// I2C clock
// Allow use of international characters when printing text (accents)
// Measure battery level

// Done - now in trial mode:
// Code to handle access point and station mode wifi
// Store number of code execution in persistent memory
// Handle new epaper type
// Handle reading different text content at every execution
// Improve wake-up hardware and detect when door is open
// Control duration of LED animatins and sleep start based on door status

// Main examples used to build this secondes
// Basic SPIFFS write/read example: https://github.com/G6EJD/SPIFFS-Examples/blob/master/ESP8266_SPIFFS_Example.ino
// Uploading a file to SPIFFS from browser: https://www.esp8266.com/viewtopic.php?t=5779&start=10#

// Wonderfull online true type to gfx fonts conversion tool: https://rop.nl/truetype2gfx/

#include <Arduino.h>
#include <GxEPD2.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <FS.h> //spiff file system
#include <ArduinoJson.h>

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#define LOW_BRIGHTNESS          20
#define FRAMES_PER_SECOND   60 // 125 frames/sec <=> 8 milli/frame
#define NUM_LEDS  48
#define DATA_PIN    5
#define MOSFET_GATE  12
#define LED_ANIMATIONS_DURATION 60000 // Duration of LED animations (Milliseconds)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint16_t brightness=LOW_BRIGHTNESS;
long start_time=0;
int updated_code_run_counter=0;
int updated_current_citation=0;
int number_of_citations=0;
bool doorOpen=false;

const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;  // value read from the ADC0

#define ENABLE_GxEPD2_GFX 1

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
//#include "Audiowide_Regular9pt7b.h"
//#include <Fonts/TomThumb.h>
//#include "bitmaps/Bitmaps200x200.h" // 1.54" b/w
#include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
//#include "project_bitmaps.h"

#define RST_PIN 0 // D3(0)
#define CS_1 SS // CS = D8(15)
#define BUSY_H_x 4 // BUSY = D2(4)

GxEPD2_BW<GxEPD2_290_M06, GxEPD2_290_M06::HEIGHT> display1(GxEPD2_290_M06(/*CS=*/ CS_1, /*DC=D3*/ 0, /*RST=*/ -1, /*BUSY=*/ BUSY_H_x)); // GDEW029M06

//char* ssid="Laketanou";
//char* ssid="DERYtelecom_80188671";
//char* password="?bici77ROMA?lsabedb";
//char* password="peka8876";
char* mySsid = "croque-livre";
char* myPassword = "PapasInventeurs";
IPAddress local_ip(192,168,11,4);
IPAddress gateway(192,168,11,1);
IPAddress netmask(255,255,255,0);

char webpage[] PROGMEM = R"=====(
<html>
<meta charset="UTF-8">
<head>
</head>
<body>
  <form>
  <h1 style="font-size:60px;color:blue;" title="Croque-Livres">Croque-Livres Saint-Gérard</h1>
    <fieldset>
    <legend style="color:blue;">Paramètres pour la connexion à un réseau WiFi existant:</legend>
      <div>
        <label for="ssid">SSID</label>
        <input value="" id="ssid" placeholder="SSID">
      </div>
      <div>
        <label for="password">PASSWORD</label>
        <input type="password" value="" id="password" placeholder="PASSWORD">
      </div>
      <div>
        <button class="primary" id="savebtn" type="button" onclick="myFunction()">SAVE</button>
      </div>
    </fieldset>
  </form>
  <form method='POST' action='/update' enctype='multipart/form-data'>
    <fieldset>
    <legend style="color:blue;">Mise à jour du fichier des citations:</legend>
      <input type='file' name='update'>
      <input type='submit' value='Update'>
    </fieldset>
  </form>
</body>
<script>
function myFunction()
{
  console.log("button was clicked!");

  var ssid = document.getElementById("ssid").value;
  var password = document.getElementById("password").value;
  var data = {ssid:ssid, password:password};

  var xhr = new XMLHttpRequest();
  var url = "/settings";

  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      // Typical action to be performed when the document is ready:
      if(xhr.responseText != null){
        console.log(xhr.responseText);
      }
    }
  };

  xhr.open("POST", url, true);
  xhr.send(JSON.stringify(data));
};

</script>
</html>
)=====";

char current_filename [] = "/data/citations.txt";

String filename;
ESP8266WebServer server(80);
//holds the current upload
File UploadFile;

void updateSPIFFS()
{
  const char * _code_run_counter = "", *_current_citation = "";
  if(SPIFFS.exists("/log.json")){
    Serial.println("Found /log.json file");
    File logFile = SPIFFS.open("/log.json", "r");
    if(logFile){
      size_t size = logFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      logFile.readBytes(buf.get(), size);
      logFile.close();

      DynamicJsonBuffer logjsonBuffer;
      JsonObject& logjObject = logjsonBuffer.parseObject(buf.get());
      if(logjObject.success())
      {
        _code_run_counter = logjObject["code_run_counter"];
        _current_citation = logjObject["current_citation"];
        //Serial.print("code_run_counter: "); Serial.print(_code_run_counter); Serial.print(" current_citation: ");Serial.println(_current_citation);
      }
    }
  }
  else {_code_run_counter = "1";  _current_citation = "1";}

  // Convert counters from char to integer then add one.
  updated_code_run_counter=atoi(_code_run_counter);
  updated_current_citation=atoi(_current_citation);

  String logData = "{code_run_counter:"+String(updated_code_run_counter)+", current_citation:"+String(updated_current_citation)+", number_of_citations:"+String(number_of_citations)+"}";
  //String logData = "{code_run_counter:10, current_citation:5}";
  DynamicJsonBuffer logjBuffer;
  JsonObject& logjObject = logjBuffer.parseObject(logData);
  File logFile = SPIFFS.open("/log.json", "w");
  logjObject.printTo(logFile);
  logFile.close();
  Serial.println(logData);

}

void FileRead() {
  String NewLine;
  int number_of_lines=0;
  Serial.println("reading...");
  Serial.println("/data/" + filename);

  if (SPIFFS.exists("/data/" + filename)) {
    File FileRead = SPIFFS.open("/data/" + filename, "r");
    Serial.print("output: ");
    Serial.println();
    while (FileRead.available() > 0) {
      char In = FileRead.read();
      NewLine += In;

      if (In == '\n') {
        Serial.print(NewLine);
        NewLine = "";
        number_of_lines=number_of_lines+1;
      }
    }

    FileRead.close();
    Serial.print("Number of lines in file: "); Serial.println(number_of_lines);
    if (filename=="citations.txt"){
      number_of_citations=number_of_lines;
      updateSPIFFS();
    }
  }
}

//format bytes - Used to format file size when displaying SPIFFS file content
String formatBytes(size_t bytes){
  if (bytes < 1024){
    return String(bytes)+"B";
  } else if(bytes < (1024 * 1024)){
    return String(bytes/1024.0)+"KB";
  } else if(bytes < (1024 * 1024 * 1024)){
    return String(bytes/1024.0/1024.0)+"MB";
  } else {
    return String(bytes/1024.0/1024.0/1024.0)+"GB";
  }
}

void print_string(GxEPD2_GFX& display, String message)
{
  display.setRotation(3);
  display.setFont(&FreeMonoBold9pt7b);
  //display.setFont(&Audiowide_Regular9pt7b);
  //display.setFont(&TomThumb);
  display.setTextColor(GxEPD_BLACK);
  uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() / 2;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    //display.setCursor(x, y);
    display.setCursor(5, 10);
    display.println(message);
  }
  while (display.nextPage());
}

void drawBitmaps128x296(GxEPD2_GFX& display){
  const unsigned char* bitmaps[] = {AventuriersSaintGerard,PapasInventeursEtJeunes_128x296};
  bool m = display.mirror(true);
  for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++){
    display.firstPage();
    do {
      Serial.println(i);
      display.fillScreen(GxEPD_WHITE);
      display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
    }
    while (display.nextPage());
    delay(2000);
  }
  display.mirror(m);
}


void drawBitmaps(GxEPD2_GFX& display){
  display.setFullWindow();
  display.setRotation(0);
  drawBitmaps128x296(display);
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
}

void rainbow() {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle() {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
  }
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {rainbowCycle};
char* SimplePatternNames[]={"rainbowCycle" };

void nextPattern(){
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void LED(String pattern){

  if (pattern=="deco"){
    digitalWrite(MOSFET_GATE,HIGH);
    //gPatterns[gCurrentPatternNumber]();
    rainbowCycle();
    //colorWipe(strip.Color(0, 0, 255));
  }

  if (pattern=="off"){
    //for (int i = NUM_LEDS; i >=0; i--) {leds[i].nscale8(230);}
    digitalWrite(MOSFET_GATE,LOW);
  }

  // send the 'leds' array out to the actual LED strip
  strip.show();
  // insert a delay to keep the framerate modest
  delay(1000/FRAMES_PER_SECOND);
}

void wifiConnect()
{
  //reset networking
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(1000);
  //check for stored credentials
  if(SPIFFS.exists("/config.json")){
    Serial.println("Found /config.json file");
    const char * _ssid = "", *_pass = "";
    File configFile = SPIFFS.open("/config.json", "r");
    if(configFile){
      size_t size = configFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      configFile.readBytes(buf.get(), size);
      configFile.close();

      DynamicJsonBuffer jsonBuffer;
      JsonObject& jObject = jsonBuffer.parseObject(buf.get());
      if(jObject.success())
      {
        _ssid = jObject["ssid"];
        _pass = jObject["password"];
        //Serial.print(_ssid); Serial.println(_pass);
        WiFi.mode(WIFI_STA);
        WiFi.begin(_ssid, _pass);
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          Serial.print(".");
          if ((unsigned long)(millis() - startTime) >= 10000) break;
        }
      }
    }
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, netmask);
    WiFi.softAP(mySsid, myPassword);
    Serial.println("Unable to connect to a known wifi network - Starting ESP as Access Point.");
  }
  else {Serial.println(""); Serial.println("ESP now connected in STAtion mode to known network.");}
  //Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  //WiFi.printDiag(Serial);

}

void handleSettingsUpdate()
{
  String data = server.arg("plain");
  DynamicJsonBuffer jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);

  File configFile = SPIFFS.open("/config.json", "w");
  jObject.printTo(configFile);
  configFile.close();

  server.send(200, "application/json", "{\"status\" : \"ok\"}");
  delay(500);

  wifiConnect();
}


void setup()
{
  Serial.begin(115200);

  Serial.println("Start setup.");
  SPIFFS.begin();

  Serial.println("(1) Setup LED strip.");
  // Initialize MOSFET_GATE used to turn LED strip power on/off
  pinMode(MOSFET_GATE, OUTPUT); digitalWrite(MOSFET_GATE, HIGH);

  // Initialize LED strip and set all pixels to BLUE
  strip.begin();
  strip.setBrightness(LOW_BRIGHTNESS);
  colorWipe(strip.Color(0, 0, 255));
  strip.show();

  Serial.println("(2) Setup Wifi.");
  // Connect to wifi, either in Access Point or STAtion mode
  wifiConnect();

  // If connection is established then start webserver
  //if (WiFi.waitForConnectResult() == WL_CONNECTED) {

    server.on("/", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/html", webpage);
    });

    server.onFileUpload([]() {
      if (server.uri() != "/update") return;
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        filename = upload.filename;
        Serial.print("Upload Name: "); Serial.println(filename);
        UploadFile = SPIFFS.open("/data/" + filename, "w");
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (UploadFile)
          UploadFile.write(upload.buf, upload.currentSize);
      } else if (upload.status == UPLOAD_FILE_END) {
        if (UploadFile)
          UploadFile.close();
          FileRead();  // After file downloads, read it
      }

    });

    server.on("/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    });

    server.on("/settings", HTTP_POST, handleSettingsUpdate);

    server.begin();
    Serial.println("Webserver running");
  //} else {
  //  Serial.println("WiFi Failed");
  //}

  Serial.println("(3) Setup SPIFFS file system.");
  if (!SPIFFS.begin()) { Serial.println("SPIFFS failed");
    } else {
      Serial.println("Content of SPIFFS memory:");
      Dir dir = SPIFFS.openDir("/");
      while (dir.next()) {
        String fileName = dir.fileName();
        size_t fileSize = dir.fileSize();
        Serial.printf(" FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
        }
      //Serial.printf("\n");
    }

  Serial.println("(4) Setup ePaper.");
  // ePaper display reset
  digitalWrite(RST_PIN, HIGH);
  pinMode(RST_PIN, OUTPUT);
  delay(20);
  digitalWrite(RST_PIN, LOW);
  delay(20);
  digitalWrite(RST_PIN, HIGH);
  delay(200);

  Serial.println("(5) Read and update execution counters from SPIFFS.");
  // Check for log.json file used to store log counters etc.
  const char * _code_run_counter = "", *_current_citation = "", *_number_of_citations = "";
  if(SPIFFS.exists("/log.json")){
    Serial.println("Found /log.json file");
    File logFile = SPIFFS.open("/log.json", "r");
    if(logFile){
      size_t size = logFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      logFile.readBytes(buf.get(), size);
      logFile.close();

      DynamicJsonBuffer logjsonBuffer;
      JsonObject& logjObject = logjsonBuffer.parseObject(buf.get());
      if(logjObject.success())
      {
        _code_run_counter = logjObject["code_run_counter"];
        _current_citation = logjObject["current_citation"];
        _number_of_citations = logjObject["number_of_citations"];
        Serial.print("code_run_counter: "); Serial.print(_code_run_counter); Serial.print(" current_citation: ");Serial.print(_current_citation);Serial.print(" number_of_citations: ");Serial.println(_number_of_citations);
      }
    }
  }
  else {
    _code_run_counter = "1";
    _current_citation = "1";
    _number_of_citations="1";
  Serial.print("reset to default"); Serial.print("code_run_counter: "); Serial.print(_code_run_counter); Serial.print(" current_citation: ");Serial.print(_current_citation);Serial.print(" number_of_citations: ");Serial.println(_number_of_citations);
}

  // Must add code to handle exceptions when log.json is empty or invalid!!!!!!!!!
  // Convert counters from char to integer then add one.
  updated_code_run_counter=atoi(_code_run_counter)+1;
  updated_current_citation=atoi(_current_citation)+1;
  number_of_citations=atoi(_number_of_citations);

  String logData = "{code_run_counter:"+String(updated_code_run_counter)+", current_citation:"+String(updated_current_citation)+", number_of_citations:"+String(_number_of_citations)+"}";
  //String logData = "{code_run_counter:10, current_citation:5}";
  DynamicJsonBuffer logjBuffer;
  JsonObject& logjObject = logjBuffer.parseObject(logData);
  File logFile = SPIFFS.open("/log.json", "w");
  logjObject.printTo(logFile);
  logFile.close();

  Serial.println("Setup done.");

  start_time=millis();
}

void loop()
{
  server.handleClient();
  delay(1);

  LED("deco");
  // read the analog in value
  sensorValue = analogRead(analogInPin);

  if (sensorValue>100){
    doorOpen=true;
    //Serial.print("Door is open!");
    // print the readings in the Serial Monitor
    //Serial.print("sensor = ");
    //Serial.println(sensorValue);
  }
  else {
    doorOpen=false;
    //Serial.println("Door is closed.");
  }


  if ((millis()-start_time>LED_ANIMATIONS_DURATION)||!doorOpen){
    LED("off");
    display1.init(115200); // enable diagnostic output on Serial
    drawBitmaps(display1);
    delay(2000);

    String citation;
    File myDataFile = SPIFFS.open(current_filename, "r");              // Open the file again, this time for reading
    if (!myDataFile) Serial.println("file open failed");  // Check for errors
    int entry=0;
    /*while (myDataFile.available()) {
      citation+=(char)myDataFile.read();                   // Read all the data from the file and save it into a string
    }*/
    //updated_current_citation=3;
    //int target_citation=updated_current_citation%number_of_citations;
    //Serial.println(number_of_citations);
    //Serial.println(updated_current_citation);
    int target_citation=updated_current_citation%number_of_citations;
    Serial.print("target_citation: ");Serial.println(target_citation);
    while (entry<=target_citation){
      entry=entry+1;
      if(myDataFile.available()){citation=myDataFile.readStringUntil('\n');}
    }
    myDataFile.close();                                   // Close the file
    print_string(display1,citation);
    delay(500);
    display1.powerOff();

    Serial.println("Starting deep sleep");
    ESP.deepSleep(0);
  }
}
