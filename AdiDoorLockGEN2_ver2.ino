#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include <SD.h>
#include "SoftwareSerial.h"                                    
#include <DFPlayerMini_Fast.h>
#include <AnimatedGIF.h>
#include <FastLED.h>
#include <ESP32Servo.h>
#include <ArduinoHA.h>
#include <WiFiClient.h>

#include "definitions.h"
#define ESP32_RTOS

CRGB leds[NUM_LEDS];

CRGB Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

#include "OTA.h"
//#include "gif.h"


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046_Touchscreen ts(TOUCH_CS);
SoftwareSerial mySoftwareSerial(DF_RX, DF_TX); // RX, TX
DFPlayerMini_Fast myDFPlayer;
//AnimatedGIF gif;
//File f;
Servo myservo;
HADevice device;
WiFiClient client;
HAMqtt mqtt(client, device);

HAButton unlock("Unlock");

void onButtonCommand(HAButton* sender) {
  unlocked = true;
  myservo.write(0);
  for (int i = 0; i < NUM_LEDS; i++) 
  {        
    leds[i].setRGB(0, 255, 0);
  }
  FastLED.show();
  sine_effect = false;
  breath_effect = true;
  rainbow = false;
}

void setup_mqtt(){

  byte mac[MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);
  device.setUniqueId(mac, sizeof(mac));

  device.setName("Doorlock");

  unlock.setName("Unlock");
  unlock.onCommand(onButtonCommand);

  mqtt.begin("192.168.29.141", "homeassistant", "Eiquaek6eeGah1Eomah3JeejahHi4bai4afae6kuaGaaX2aiFo7Ez4ieRehueth7");
}

void keypad() {

  tft.fillScreen(BLACK);                   //clear screen

  tft.drawRect(0, 0, 240, 320, WHITE);     //outline frame of keypad

  tft.drawRect(5, 5, 230, 40, WHITE);      //frame for "user code" and display first 4 keys pressed

  tft.setTextColor(WHITE);                 //write "user code" text into box
  tft.setCursor(10, 15);
  tft.setTextSize(2);
  tft.println("User code:");

  myDFPlayer.volume(15);

  int codeArray[4] = {0, 0, 0, 0};  // this is where the first 4 key presses will be saved

  int keyPosX = 5;      //set left hand start point for left column of keys
  int keySpaceX = 5;    //set horizontal space between keys
  int keyPosY = 48;     //set the top most start point for the top row of keys
  int keySpaceY = -5;   //set vertical space between keys (currently not working prpperly for some reason)
  int keyWidth = 73;    //set width of keys
  int keyHieght = 63;   //set hight of keys

  int colum1 = keyPosX;                                   //human readable left start point for left column of keys
  int colum2 = keyPosX + keySpaceX + keyWidth;            //human readable left start point for second column of keys
  int colum3 = keyPosX + (keySpaceX * 2) + (keyWidth * 2);//human readable left start point for third column of keys

  int row1 = keyPosY;                                     //human readable top start point for top row of keys
  int row2 = keyPosY + keySpaceY + keyWidth;              //human readable top start point for second row of keys
  int row3 = keyPosY + (keySpaceY * 2) + (keyWidth * 2);  //human readable top start point for third row of keys
  int row4 = keyPosY + (keySpaceY * 3) + (keyWidth * 3);  //human readable top start point for fourth row of keys


  //================================== draw keys =========================================
  //-----------------------------------key 1 -----------------------------------------
  tft.drawRect(colum1, keyPosY, keyWidth, keyHieght, BLUE); //key 1    draw key
  tft.setTextColor(BLUE);
  tft.setCursor(keyPosX + 25, keyPosY + 15);
  tft.setTextSize(5);
  tft.println("1");
  //-----------------------------------key 2 ----------------------------------------

  tft.drawRect(colum2, keyPosY, keyWidth, keyHieght, BLUE); //key 2
  tft.setTextColor(BLUE);
  tft.setCursor(colum2 + 25, keyPosY + 15);
  tft.setTextSize(5);
  tft.println("2");
  //-----------------------------------key 3 -----------------------------------------

  tft.drawRect(colum3, keyPosY, keyWidth, keyHieght, BLUE); //key 3
  tft.setTextColor(BLUE);
  tft.setCursor(colum3 + 25, keyPosY + 15);
  tft.setTextSize(5);
  tft.println("3");

  //-----------------------------------key 4 --------------------------------------

  tft.drawRect(colum1, row2, keyWidth, keyHieght, BLUE); //key 4
  tft.setTextColor(BLUE);
  tft.setCursor(colum1 + 25, row2 + 15);
  tft.setTextSize(5);
  tft.println("4");

  //-----------------------------------key 5 ------------------------------------

  tft.drawRect(colum2, row2, keyWidth, keyHieght, BLUE); //key 5
  tft.setTextColor(BLUE);
  tft.setCursor(colum2 + 25, row2 + 15);
  tft.setTextSize(5);
  tft.println("5");

  //-----------------------------------key 6 -----------------------------------

  tft.drawRect(colum3, row2, keyWidth, keyHieght, BLUE); //key 6
  tft.setTextColor(BLUE);
  tft.setCursor(colum3 + 25, row2 + 15);
  tft.setTextSize(5);
  tft.println("6");

  //-----------------------------------key 7 ------------------------------------

  tft.drawRect(colum1, row3, keyWidth, keyHieght, BLUE); //key 7
  tft.setTextColor(BLUE);
  tft.setCursor(colum1 + 25, row3 + 15);
  tft.setTextSize(5);
  tft.println("7");

  //-----------------------------------key 8 ----------------------------------

  tft.drawRect(colum2, row3, keyWidth, keyHieght, BLUE); //key 8
  tft.setTextColor(BLUE);
  tft.setCursor(colum2 + 25, row3 + 15);
  tft.setTextSize(5);
  tft.println("8");

  //-----------------------------------key 9 --------------------------------

  tft.drawRect(colum3, row3, keyWidth, keyHieght, BLUE); //key 9
  tft.setTextColor(BLUE);
  tft.setCursor(colum3 + 25, row3 + 15);
  tft.setTextSize(5);
  tft.println("9");

  //-----------------------------------key C -------------------------------

  tft.drawRect(colum1, row4, keyWidth, keyHieght, BLUE); //key C
  tft.setTextColor(BLUE);
  tft.setCursor(colum1 + 25, row4 + 15);
  tft.setTextSize(5);
  tft.println("C");

  //-----------------------------------key 0 -------------------------------

  tft.drawRect(colum2, row4, keyWidth, keyHieght, BLUE); //key 0
  tft.setTextColor(BLUE);
  tft.setCursor(colum2 + 25, row4 + 15);
  tft.setTextSize(5);
  tft.println("0");

  //-----------------------------------key E -------------------------------

  tft.drawRect(colum3, row4, keyWidth, keyHieght, BLUE); //key E
  tft.setTextColor(BLUE);
  tft.setCursor(colum3 + 25, row4 + 15);
  tft.setTextSize(5);
  tft.println("E");


  //========================= key press ================================



  int keypress = 55;       //declare integer to store key pressed set at 55 so will only read if a valid number


  //  set human readable touch point limits for key detection

  int pressCol1 = 336;    // start of column 1
  int presscol2 = 1420;   //end of column 1 start of column 2
  int presscol3 = 2660;   //end of column 2 start of column 3
  int presscol4 = 3740;   //right most edge of column 3 keys

  int pressrow1 = 950;    // top start point of row 1
  int pressrow2 = 1730;   //bottom of row 1 top of row 2
  int pressrow3 = 2440;   //bottom of row 2 top of row 3
  int pressrow4 = 3190;   //bottom of row 3 start of row 4

  int keypressIndex = 0;      //array index number

  for (int i = 0; i < NUM_LEDS; i++) 
  {        
    leds[i].setRGB(0, 0, 255);
  }
  FastLED.show();
  sine_effect = true;
  breath_effect = false;
  rainbow = false;

  tft.fillRect(130, 10, 75, 30, BLACK); // clear keypress displayed

  //keypad key read loop

  myDFPlayer.volume(15);

  while (!unlocked) {

    check_for_motion();
    mqtt.loop();

    if (ts.touched()) {

      TS_Point p = ts.getPoint();

      //store pressed key number in 'keypress'

      if (p.x > pressrow1 && p.x < pressrow2 && p.y < presscol2) keypress = 9;
      if (p.x > pressrow1 && p.x < pressrow2 && p.y > presscol2 && p.y < presscol3) keypress = 8;
      if (p.x > pressrow1 && p.x < pressrow2 && p.y > presscol3 && p.y < presscol4) keypress = 7;
      if (p.x > pressrow2 && p.x < pressrow3 && p.y < presscol2) keypress = 6;
      if (p.x > pressrow2 && p.x < pressrow3 && p.y > presscol2 && p.y < presscol3) keypress = 5;
      if (p.x > pressrow2 && p.x < pressrow3 && p.y > presscol3 && p.y < presscol4) keypress = 4;
      if (p.x > pressrow3 && p.x < pressrow4 && p.y < presscol2) keypress = 3;
      if (p.x > pressrow3 && p.x < pressrow4 && p.y > presscol2 && p.y < presscol3) keypress = 2;
      if (p.x > pressrow3 && p.x < pressrow4 && p.y > presscol3 && p.y < presscol4) keypress = 1;
      if (p.x >  pressrow4 && p.y > presscol2 && p.y < presscol3) keypress = 0;

      if (keypress != 55) codeArray[keypressIndex] = keypress;

      //------------------------- clear code -----------------------------------------------

      if (p.x >  pressrow4 && p.y < presscol2) {// clear key
        tft.fillRect(130, 10, 100, 30, BLACK); // clear keypress displayed;
        keypressIndex = 0;
        keypress = 55;
        codeArray[0] = 0;
        codeArray[1] = 0;
        codeArray[2] = 0;
        codeArray[3] = 0;
      }


      //----------------------------- display keypress ----------------------------------------------

      //dipslays the 4 digit code on the screen

      if (keypressIndex == 0) { //display first digit


        tft.setTextColor(BLUE);
        tft.setCursor(130, 10);
        tft.setTextSize(4);
        tft.println(codeArray[0]);

      }

      if (keypressIndex == 1) { //display second digit

        tft.setTextColor(BLUE);
        tft.setCursor(155, 10);
        tft.setTextSize(4);
        tft.println(codeArray[1]);

      }

      if (keypressIndex == 2) { // display third digit

        tft.setTextColor(BLUE);
        tft.setCursor(180, 10);
        tft.setTextSize(4);
        tft.println(codeArray[2]);

      }

      if (keypressIndex == 3) { //display forth digit

        tft.setTextColor(BLUE);
        tft.setCursor(205, 10);
        tft.setTextSize(4);
        tft.println(codeArray[3]);

      }


      keypressIndex++; 

      delay(50);
      
      myDFPlayer.playAdvertisement(7);

      delay(300);

      if(keypressIndex == 4)
      {
        if (codeArray[0] == 6 && codeArray[1] == 9 && codeArray[2] == 6 && codeArray[3] == 9)
        {
          delay(500);
          myDFPlayer.playAdvertisement(16);
          delay(500);
          while(true)
          {
            if(ts.touched())
            {
              myDFPlayer.stopAdvertisement();
              break;
            }
          }
        }
        else if (codeArray[0] == 1 && codeArray[1] == 9 && codeArray[2] == 8 && codeArray[3] == 5)
        {
          delay(200);
          myDFPlayer.playAdvertisement(3);
          delay(1000);
          myDFPlayer.playAdvertisement(11);
          unlocked = true;
          myservo.write(0);
          keypressIndex = 0;
          keypress = 55;
          codeArray[0] = 0;
          codeArray[1] = 0;
          codeArray[2] = 0;
          codeArray[3] = 0;
          for (int i = 0; i < NUM_LEDS; i++) 
          {        
            leds[i].setRGB(0, 255, 0);
          }
          FastLED.show();
          sine_effect = false;
          breath_effect = true;
          rainbow = false;
          delay(2000);
        }
        else
        {
          delay(200);
          myDFPlayer.playAdvertisement(2);
          delay(1000);
          myDFPlayer.playAdvertisement(12);
          keypressIndex = 0;
          keypress = 55;
          codeArray[0] = 0;
          codeArray[1] = 0;
          codeArray[2] = 0;
          codeArray[3] = 0;

          tft.fillRect(130, 10, 100, 30, BLACK);

          for (int i = 0; i < NUM_LEDS; i++) 
          {        
            leds[i].setRGB(255, 0, 0);
          }
          FastLED.show();
          sine_effect = false;
          breath_effect = true;
          rainbow = false;
          delay(2000);

          for (int i = 0; i < NUM_LEDS; i++) 
          {        
            leds[i].setRGB(0, 0, 255);
          }
          FastLED.show();
          sine_effect = true;
          breath_effect = false;
        }
      }
    }
  }
}

void check_for_motion() {
  if (digitalRead(PIR_SENSOR) == HIGH) 
  {
    digitalWrite(BL_PIN, HIGH);
    idle = false;
  } 
  else 
  {
    digitalWrite(BL_PIN, LOW);
    idle = true;
  }
}

void display_idle_menu() {

  tft.fillScreen(ILI9341_GREEN);

  tft.setTextSize(6);
  tft.setTextColor(ILI9341_BLACK);

  tft.setCursor(50, 160);
  tft.print("LOCK");

  while(true)
  {
    sine_effect = false;
    breath_effect = false;
    rainbow = true;
    check_for_motion();
    mqtt.loop();

    if(ts.touched())
    {
      myDFPlayer.playAdvertisement(10);
      break;
    }
  }

  tft.fillScreen(ILI9341_RED);

  tft.setTextSize(5);
  tft.setTextColor(ILI9341_BLACK);

  tft.setCursor(20, 160);
  tft.print("LOCKING");
  myservo.write(180); 
  unlocked = false;
  delay(2000);
}

void setup() {

  setupOTA("DoorLock", "Adi Home Network", "62826282");

  setup_mqtt();

  pinMode(PIR_SENSOR,INPUT);
  pinMode(BL_PIN,OUTPUT);
  
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);
	myservo.attach(SERVO_PIN, 1000, 2000);
  myservo.write(0);

  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();

  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial, true);
  myDFPlayer.volume(15);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear();

  //SD.begin(SD_CS);

  //gif.begin(LITTLE_ENDIAN_PIXELS);

  delay(500);
  myDFPlayer.volume(15);
  delay(500);
}

void loop() {
  mqtt.loop();
  check_for_motion();
  if(!unlocked) keypad();
  if(unlocked) display_idle_menu();
}