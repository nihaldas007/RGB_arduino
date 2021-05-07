#define PxMATRIX_COLOR_DEPTH 1
#include "RTClib.h"
#include <SPI.h>
#include <DS3231.h>
//#define PxMATRIX_SPI_FREQUENCY 40000000

//#include <Adafruit_GFX.h>    // Core graphics library
#include <PxMatrix.h> // Hardware-specific library
#include <Fonts/Font5x7FixedMono.h>
#include <Fonts/kongtext4pt7b.h>
#include <avr/pgmspace.h>
// Pins for LED MATRIX
#define P_A 2
#define P_B 3
#define P_LAT 7
#define P_OE 9
RTC_DS1307 rtc;
// CLK connect to 13
// R0 connect to 11

PxMATRIX display(32, 16, P_LAT, P_OE, P_A, P_B);

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);
uint16_t myORANGE = display.color565(255, 100, 0);
int _day, _month, _year, _hour12, _hour24, _minute, _second, _dtw;
int hr24;
String st;
char hr_24 [3];
String str_hr_24;
char mn [3];
String str_mn;
char sc [3];
String str_sc;
char dy [3];
String str_dy;
char mo [3];
String str_mo;

uint16_t TimeC = myCYAN;
char WeakC = myORANGE;

char myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};
uint16_t start_time = 0;
void setup() {
  Serial.begin(9600);
  display.begin(4);
  display.setScanPattern(ZAGZIG);
  display.setBrightness(255);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");

    //         rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//      rtc.adjust(DateTime(2021, 2, 8, 8, 30, 0));
  }
//              rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //         rtc.adjust(DateTime(2021, 2, 11, _hour24, 02, 0));
}


void loop() {
  while (1) {
    display.clearDisplay();


    GetDateTime(); //-> Retrieve time and date data from DS1307

//    display.setFont(&Font5x7FixedMono);

    str_hr_24 = String(_hour24);
    str_hr_24.toCharArray(hr_24, 3);

    if (_hour24 < 10) {
      display.setTextColor(TimeC);
      display.setCursor(2, 0);
      display.print("0");
      display.setTextColor(TimeC);
      display.setCursor(8, 0);
      display.print(hr_24);
    }
    else {
      display.setTextColor(TimeC);
      display.setCursor(2, 0);
      display.print(hr_24);
    }
    if (_second % 2 == 0) {
      display.setTextColor(TimeC);
      display.setCursor(13, 0);
      display.print(":");
    }
    else {
      display.setTextColor(TimeC);
      display.setCursor(14, 0);
      display.print(" ");
    }
    str_mn = String(_minute);
    str_mn.toCharArray(mn, 3);

    if (_minute < 10) {
      display.setTextColor(TimeC);
      display.setCursor(18, 0);
      display.print("0");
      display.setTextColor(TimeC);
      display.setCursor(24, 0);
      display.print(mn);
    }
    else {
      display.setTextColor(TimeC);
      display.setCursor(18, 0);
      display.print(mn);
    }

    GetDateTime();
    DateTime now = rtc.now();
    switch (_dtw)
    {
      case 0:
        display.setTextColor(myMAGENTA);
        display.setCursor(1, 9);
        display.print("SUN");
      break;  case 1:
        display.setTextColor(myMAGENTA);
        display.setCursor(1, 9);
        display.print("MON");
      break;  case 2:
        display.setTextColor(myMAGENTA);
        display.setCursor(1, 9);
        display.print("THI");
      break;  case 3:
        display.setTextColor(myMAGENTA);
        display.setCursor(1, 9);
        display.print("WED");
      break;  case 4:
        display.setTextColor(myMAGENTA);
        display.setCursor(1, 9);
        display.print("THE");
      break;  case 5:
        display.setTextColor(myMAGENTA);
        display.setCursor(1, 9);
        display.print("FRI");
      break;  case 6:
        display.setTextColor(myMAGENTA);
        display.setCursor(1, 9);
        display.print("SAT");
    }


    if (hr24 > 12) {
      display.setTextColor(myYELLOW);
      display.setCursor(20, 9);
      display.print("PM");
//      dmd.drawString(27, 9, "M", 1, GRAPHICS_NORMAL);
    }
    else {
      display.setTextColor(myYELLOW);
      display.setCursor(20, 9);
      display.print("AM");
//      dmd.drawString(27, 9, "M", 1, GRAPHICS_NORMAL);
    }






    //
    //
    //    display.setTextColor(myMAGENTA);
    //    display.setCursor(2, 9);
    //
    //    display.print(hr_24);





//   display.drawLine(20000+16,0,20000+16,5,display.color565(20000*16,0,0));
    display.display(20000);

  }
}
