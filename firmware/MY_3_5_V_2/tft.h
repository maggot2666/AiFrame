#pragma once
#include "SPI.h"

#include <TFT_eSPI.h> //***  
   
#include "gen.h"
/*   Подключение Wemos MINI R1 к TFT iLi9488
 * 
 * ESP8266(Wemos MINI) |      iLi9488
 * -------------------   --------------------   
 *  MISO  D6  GPIO 12  ->   SDO  (MISO)
 *             +3,3 V  ->   BL   (LED)
 *   SCK  D5  GPIO 14  ->   SCK
 *  MOSI  D7  GPIO 13  ->   SDI  (MOSI) 
 *        D4  GPIO 2   ->   D/C
 *        D3 or +3,3 V ->   RST  (RESET)
 *    SS  D8  GPIO15   ->   CS
 *                GND  ->   GND
 *               +5 V  ->   VCC
 * -------------------------------------------            
 */
#define TFT_CS   PIN_D8
#define TFT_DC   PIN_D4
#define TFT_RST  PIN_D3

TFT_eSPI tft = TFT_eSPI();                                 //***

void tft_render(int x, int y, int w, int h, uint8_t* buf) {


//    tft.pushRect(x, y, w, h,(uint16_t*)buf);  //*** на ili9488 работает, но цвета кривые RGB -> BRG
    tft.pushRect_SW(x, y, w, h,(uint16_t*)buf);  //***  РАБОТАЕТ!!! Вручную добавил  pushRect с параметром "swap=true" TFT-eSPI


}

void tft_init() {
    SPI.setFrequency(6000000ul);
    tft.begin();
    tft.setRotation(2);	//***	//*** разворот изображения на 180* (0,1,2,3,4)
    tft.invertDisplay(false);  //*** инверсия цвета (для ili9488 3.5")
    tft.fillScreen(0x0000);
    tft.setTextColor(0x07E0);
    tft.setTextSize(2);       //***
    gen.onRender(tft_render);
}
