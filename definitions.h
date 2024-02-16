#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

const char* ssid = "ssid";
const char* password = "password"; 

#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_SCLK 18

#define SD_CS    12

#define TOUCH_CS  5

#define TFT_CS   4
#define TFT_DC   27

#define DF_RX    26
#define DF_TX    14

#define NUM_LEDS 26
#define DATA_PIN 21

#define SERVO_PIN 22

#define BL_PIN 25

#define PIR_SENSOR 35

//variables

#define MAC_ADDR_LENGTH 6

int X_start = 360;
int X_finish = 3840;
int Y_start = 270;
int Y_finish = 3860;

int pressCol1 = 336;    // start of column 1
int presscol2 = 1420;   //end of column 1 start of column 2
int presscol3 = 2660;   //end of column 2 start of column 3
int presscol4 = 3740;   //right most edge of column 3 keys

int pressrow1 = 950;    // top start point of row 1
int pressrow2 = 1730;   //bottom of row 1 top of row 2
int pressrow3 = 2440;   //bottom of row 2 top of row 3
int pressrow4 = 3190;   //bottom of row 3 start of row 4

#define	BLACK       0x0000
#define	BLUE        0x001F
#define	RED         0xF800
#define	GREEN       0x07E0
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define GREY        0xCE79
#define LIGHTGREY   0xDEDB
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0 
#define DARKGREY    0x7BEF
#define ORANGE      0xFDA0
#define GREENYELLOW 0xB7E0
#define PINK        0xFE19
#define BROWN       0x9A60
#define GOLD        0xFEA0 
#define SILVER      0xC618
#define SKYBLUE     0x867D          
#define VIOLET      0x915C  

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320

unsigned long lastUpdate = 0;
uint8_t gHue = 0;
bool breath_effect = false;
bool sine_effect = false;
bool rainbow = false;
bool idle = false;
bool unlocked = true;

#endif
