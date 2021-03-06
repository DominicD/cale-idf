#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// Only for parallel epaper displays driven by I2S DataBus (No SPI)
// NOTE: This needs Epdiy component https://github.com/vroland/epdiy
// Run idf.py menuconfig-> Component Config -> E-Paper driver and select:
// Display type: LILIGO 4.7 ED047TC1
// Board: LILIGO T5-4.7 Epaper
// In the same section Component Config -> ESP32 Specifics -> Enable PSRAM
#include "parallel/ED047TC1.h"
Ed047TC1 display;

// Include a font
#include <Fonts/ubuntu/Ubuntu_M24pt8b.h>
#include <Fonts/ubuntu/Ubuntu_M36pt7b.h>

extern "C"
{
   void app_main();
}

void delay(uint32_t millis) { vTaskDelay(millis / portTICK_PERIOD_MS); }

void app_main(void)
{
   display.init(true);
   //display.setRotation(1); // Rotate screen °90

   // Clear all screen to white
   display.clearScreen();
   
   delay(1000);

   // Fillscreen with gray
   display.fillScreen(230);
   display.update();
   delay(1000);

   // Draw some rectangles
   for (int x = 0; x < 200; x++) {

      for (int y = 0; y < 400; y++) {
         display.drawPixel(x, y, 0);
         display.drawPixel(x+200, y, 80);
         display.drawPixel(x+400, y, 160);
         display.drawPixel(x+600, y, 200);
         display.drawPixel(x+760, y, 230);
      }
   }

   // Working!
   display.setTextColor(255);
   display.setCursor(30,200);
   display.setFont(&Ubuntu_M36pt7b);
   display.println("Hello world");
   display.setCursor(30,250);
   display.setFont(&Ubuntu_M24pt8b);
   display.println("This is a TTGO T5 4.7 inch epaper");
   display.update();
}
