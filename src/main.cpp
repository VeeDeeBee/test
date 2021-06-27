#include <Adafruit_SSD1327.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <constants.h>

ESP8266WebServer server(80);

// Used for I2C or SPI
#define OLED_RESET -1


// software SPI
//Adafruit_SSD1305 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// hardware SPI
//Adafruit_SSD1327 display(128, 128, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// I2C
Adafruit_SSD1327 display(128, 128, &Wire, OLED_RESET, 1000000);

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}


void setup()   {                
  Serial.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int i = 0;

  while ( i < 60 && WiFi.status() != WL_CONNECTED ) 
  {
    Serial.print(".");
    delay(500);
    i++;
  }

  Serial.println();

  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("[WARNING] Connection timed out, offline mode enabled.");
  } 
  else
  {
    Serial.print("Connected! IP address: ");
    String ip = IpAddress2String(WiFi.localIP());
    Serial.println(ip);
  }

  //while (! Serial) delay(100);
  Serial.println("SSD1327 OLED test");
  
  if ( ! display.begin(0x3C) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }
  display.clearDisplay();
  display.display();

  // display.setTextSize(10);
  // display.setTextWrap(false);
  // display.setTextColor(0xF);
  // display.setCursor(0,0);
  // display.write("Ruben");
  // display.display();


  char * header;
  char * screen1header;
  char * screen1value;
  char * screen2header;
  char * screen2value;
  char * screen3header;
  char * screen3value;
  char * screen4header;
  char * screen4value;
  char * footer;

  header = "Solar";
  screen1header = "Current";
  screen1value = "123";
  screen2header = "Max today";
  screen2value = "456";
  screen3header = "This month";
  screen3value = "789";
  screen4header = "This year";
  screen4value = "abc";
  footer = "Last update: ";

  display.setTextSize(2);
  display.setTextWrap(false);
  display.setTextColor(0xF);
  display.setCursor(0,10);
  display.write(header);

  display.drawLine(0, 30, display.width()-1, 30 , 0x5);
  display.drawLine(0, display.height()-20, display.width()-1 , display.height()-20 , 0x5);
  display.drawLine(display.width()/2, 30, display.width()/2, display.height()-20 , 0x2);
  display.drawLine(0, display.height()/2+5, display.width()-1, display.height()/2+5 , 0x5);

  display.setTextSize(1);
  display.setTextColor(0x5);

  display.setCursor(0,32);
  display.write(screen1header);

  display.setCursor(display.width()/2+2,32);
  display.write(screen2header);
  
  display.setCursor(0,display.height()/2+7);
  display.write(screen3header);

  display.setCursor(display.width()/2+2,display.height()/2+7);
  display.write(screen4header);

  display.setCursor(0,display.height()-18);
  display.write(footer);
  
  display.setTextSize(2);
  display.setTextColor(0xF);

  display.setCursor(0,47);
  display.write(screen1value);

  display.setCursor(display.width()/2+2,47);
  display.write(screen2value);
  
  display.setCursor(0,display.height()/2+22);
  display.write(screen3value);

  display.setCursor(display.width()/2+2,display.height()/2+22);
  display.write(screen4value);


  display.display();

  
}


void loop() {
}






