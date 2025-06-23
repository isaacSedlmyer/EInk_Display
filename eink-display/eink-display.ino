#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "bitmap.h"

#define ENABLE_GxEPD2_GFX 0

// Pinout definitions
// VCC = 3.3V
// GND = GND
// SDA(MOSI) = GPIO23
// SCL(SCK) = GPIO18
// CS(SS) = GPIO5
// DC = GPIO4
// RES = GPIO2
// BUSY = GPIO15

#define CS 5
#define DC 4
#define RES 2
#define BUSY 15

GxEPD2_BW<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT> display(GxEPD2_213_Z98c(CS, DC, RES, BUSY)); // 250x122


void setup()
{
  display.init(115200, true, 50, false);

  // Try out these functions!
  // nameTag();
  //displayImage();
  displayNameTagWithLogo();

  display.hibernate();
}

void displayImage() {
  // for some reason the image displays with inverted colors
  // when creating your bitmap check "invert image colors" for it to display correctly
  int imgWidth = 250;
  int imgHeight = 122;
  int x = 0;
  int y = 0;

  display.setRotation(1);
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(x, y, psuieee, imgWidth, imgHeight, GxEPD_BLACK);
  } while (display.nextPage());
}

void nameTag()
{
  const char name[] PROGMEM = "John Doe";
  const char major[] PROGMEM = "Electrical Engineering";
  display.setRotation(1);
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextColor(GxEPD_BLACK);
  
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(name, 0, 0, &tbx, &tby, &tbw, &tbh); // get width and height for centering text
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y-tbh);
    display.print(name);
    display.setFont(&FreeMonoBold9pt7b);
    display.getTextBounds(major, 0, 0, &tbx, &tby, &tbw, &tbh); // get width and height for centering text
    x = ((display.width() - tbw) / 2) - tbx;
    display.setCursor(x, y+tbh);
    display.print(major);
  }
  while (display.nextPage());
}

void displayNameTagWithLogo() {
  const char name1[] PROGMEM = "Isaac";
  const char name2[] PROGMEM = "Sedlmyer"; //use year if your name is short enough
  const char majorLine1[] PROGMEM = "Electrical";
  const char majorLine2[] PROGMEM = "Engineering";

  const int logoWidth = 100;
  const int logoHeight = 100;

  display.setRotation(1);
  display.setFullWindow();
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    int16_t x1, y1;
    uint16_t w, h;
    int lineHeight = 22; // vertical spacing between lines
    int totalLines = 4;
    int textBlockHeight = lineHeight * totalLines;
    int startY = 16 + ((display.height() - textBlockHeight) / 2);

    const char* lines[] = { name1, name2, majorLine1, majorLine2 };

    for (int i = 0; i < totalLines; ++i) {
      display.getTextBounds(lines[i], 0, 0, &x1, &y1, &w, &h);
      int centerX = (display.width() - logoWidth) / 2 - w / 2;
      int y = startY + i * lineHeight;
      display.setCursor(centerX, y);
      display.print(lines[i]);
    }

    // Draw logo on the right side
    int logoX = display.width() - logoWidth - 6;
    int logoY = (display.height() - logoHeight) / 2;
    display.drawBitmap(logoX, logoY, pennStateLogo, logoWidth, logoHeight, GxEPD_BLACK);

  } while (display.nextPage());
}



void loop() {
}
