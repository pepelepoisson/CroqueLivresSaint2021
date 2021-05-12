// Main examples used to build this secondes
// Basic SPIFFS write/read example: https://github.com/G6EJD/SPIFFS-Examples/blob/master/ESP8266_SPIFFS_Example.ino
// Uploading a file to SPIFFS from browser: https://www.esp8266.com/viewtopic.php?t=5779&start=10#



#include <Arduino.h>
#include <GxEPD2.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <FS.h> //spiff file system

#define NB_TRYWIFI     10             // number of try to connect WiFi
#define durationSleep  10             // secondes
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#define DEBUG_SERIAL 0  // Set to 1 to output detailed data to serial
#define MINIMAL_SERIAL 0 // Set to 1 to output minimal status data to serial
#define LOW_BRIGHTNESS          20
#define HIGH_BRIGHTNESS          255
#define FRAMES_PER_SECOND   60 // 125 frames/sec <=> 8 milli/frame
#define NUM_LEDS  60
#define ESP_LED 2
#define DATA_PIN    5
#define MOSFET_GATE  12
#define LED_ANIMATIONS_DURATION 60000 // Duration of LED animations (Milliseconds)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint16_t brightness=LOW_BRIGHTNESS;
long start_time=0;


#define ENABLE_GxEPD2_GFX 1

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "bitmaps/Bitmaps200x200.h" // 1.54" b/w

#define RST_PIN 0 // D3(0)
#define CS_1 SS // CS = D8(15)
#define BUSY_H_x 4 // BUSY = D2(4)
// select one and adapt to your mapping, can use full buffer size (full HEIGHT)
GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display1(GxEPD2_154(/*CS=*/ CS_1, /*DC=D3*/ 0, /*RST=*/ -1, /*BUSY=*/ BUSY_H_x)); // GDEP015OC1 no longer available

char* ssid="Laketanou";
//char* ssid="DERYtelecom_80188671";
char* password="?bici77ROMA?lsabedb";
//char* password="peka8876";

char current_filename [] = "/data/citations.txt";
//char filename [] = "datalog.txt";

String filename;
ESP8266WebServer server(80);
//holds the current upload
File UploadFile;

const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

void FileRead() {
  String NewLine;
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
      }
    }

    FileRead.close();
  }
}

// outside of the Arduino blocks
#define DBG_OUTPUT_PORT Serial

//format bytes
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
  //Serial.println("helloWorld");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
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

#ifdef _GxBitmaps200x200_H_

void drawBitmaps200x200(GxEPD2_GFX& display);

void drawBitmaps200x200(GxEPD2_GFX& display)
{

  const unsigned char* bitmaps[] =
  {
    GeaiRareDit_200x200
  };

  {
    bool mirror_y = (display.epd2.panel != GxEPD2::GDE0213B1);
    display.clearScreen(); // use default for white
    int16_t x = (int16_t(display.epd2.WIDTH) - 200) / 2;
    int16_t y = (int16_t(display.epd2.HEIGHT) - 200) / 2;
    /*
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawImage(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
      delay(2000);
    }
    */
    // Now inverse and mirror images
    display.setRotation(2);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawImage(bitmaps[i], x, y, 200, 200, true, !mirror_y, true);
      delay(2000);
    }

  }

}
#endif


void drawBitmaps(GxEPD2_GFX& display)
{
  display.setFullWindow();
  display.setRotation(0);

  // show these after the specific bitmaps
#ifdef _GxBitmaps200x200_H_
  drawBitmaps200x200(display);
#endif

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

void setup()
{
  Serial.begin(115200);
  Serial.println("setup");
  SPIFFS.begin();

  // Initialize MOSFET_GATE used to turn LED strip power on/off
  pinMode(MOSFET_GATE, OUTPUT); digitalWrite(MOSFET_GATE, HIGH);

  // Initialize built-in indicator LEDs
  //pinMode(ESP_LED, OUTPUT);
  //digitalWrite(ESP_LED,LOW);

  // Initialize LED strip and set startup pattern
  strip.begin();
  strip.setBrightness(LOW_BRIGHTNESS);
  colorWipe(strip.Color(0, 0, 255));
  strip.show(); // Initialize all pixels to BLUE

  int _try = 0;
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    _try++;
    if ( _try >= NB_TRYWIFI ) {
        Serial.println("Impossible to connect WiFi network, go to deep sleep");
        ESP.deepSleep(durationSleep * 1000000);
    }
    delay(500);
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (WiFi.waitForConnectResult() == WL_CONNECTED) {

    server.on("/", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/html", serverIndex);
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
    server.begin();
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi Failed");
  }

  if (!SPIFFS.begin()) { DBG_OUTPUT_PORT.println("SPIFFS failed");
    } else {
      Dir dir = SPIFFS.openDir("/");
      while (dir.next()) {
        String fileName = dir.fileName();
        size_t fileSize = dir.fileSize();
        DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
        }
      DBG_OUTPUT_PORT.printf("\n");
    }


  // one common reset for all displays
  digitalWrite(RST_PIN, HIGH);
  pinMode(RST_PIN, OUTPUT);
  delay(20);
  digitalWrite(RST_PIN, LOW);
  delay(20);
  digitalWrite(RST_PIN, HIGH);
  delay(200);

  Serial.println("setup done");

  start_time=millis();
}

void loop()
{
  server.handleClient();
  delay(1);

  LED("deco");
  #if MINIMAL_SERIAL
  EVERY_N_MILLISECONDS( 500 ) {
    Serial.println(SimplePatternNames[gCurrentPatternNumber]);
  }
  #endif

  if (millis()-start_time>LED_ANIMATIONS_DURATION){
    LED("off");
    display1.init(115200); // enable diagnostic output on Serial
    drawBitmaps(display1);
    delay(2000);

    String citation;
    File myDataFile = SPIFFS.open(current_filename, "r");              // Open the file again, this time for reading
    if (!myDataFile) Serial.println("file open failed");  // Check for errors
    while (myDataFile.available()) {
      //citation=Serial.write(myDataFile.read());                    // Read all the data from the file and display it
      citation+=(char)myDataFile.read();                    // Read all the data from the file and save it into a string
    }
    myDataFile.close();                                   // Close the file
    print_string(display1,citation);
    delay(500);
    display1.powerOff();
    //digitalWrite(ESP_LED,HIGH);
    Serial.println("Starting deep sleep");
    ESP.deepSleep(0);
  }
}
