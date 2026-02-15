// ==========================
// Rotary Encoder Wiring
// ==========================
// VCC → 5V
// GND → GND
// CLK → D3
// DT  → D4


int pinA = 22;
int pinB = 24;


int encoderPosCount = 0;
int pinALast;
int aVal;
bool bCW;




// ==========================
// OLED Screen
// ==========================


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32   // change to 64 if your OLED is 128x64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




// ==========================
// Draw Menu Function
// ==========================
void drawMenu() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);


  int m = encoderPosCount % 5;
  if (m < 0) m += 5;   // fix negative modulo


  if (m == 0) display.println("Off");
  if (m == 1) display.println("Genre 1");
  if (m == 2) display.println("Genre 2");
  if (m == 3) display.println("Genre 3");
  if (m == 4) display.println("Genre 4");


  display.display();   // ⭐ push buffer to screen
}




// ==========================
// SETUP
// ==========================
void setup() {


  Serial.begin(9600);
  Serial.println("BEGIN");


  // -------- Rotary --------
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  pinALast = digitalRead(pinA);


  // -------- OLED --------
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED not found");
    while (true);
  }


  // Startup screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Hello");
  display.println("World");
  display.display();
  delay(1500);


  drawMenu();
}




// ==========================
// LOOP
// ==========================
void loop() {


  aVal = digitalRead(pinA);


  if (aVal != pinALast) {
    if (digitalRead(pinB) != aVal) {
      encoderPosCount++;
      bCW = true;
    } else {
      encoderPosCount--;
      bCW = false;
    }


    Serial.print("Direction: ");
    Serial.println(bCW ? "CW" : "CCW");


    Serial.print("Count: ");
    Serial.println(encoderPosCount);


    drawMenu();   // ⭐ update OLED
  }


  pinALast = aVal;
}
