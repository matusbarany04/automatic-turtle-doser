#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(10, 11, 16, 12, 17);



// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16



void blink(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);     
}


void initDisplay(){
    display.clearDisplay();

    display.display();
}

void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
  }    
  display.display();
}

String description = "Hello this is a test";
String leftButtontext =  "<-";
String middleButtontext =  "O";
String rightButtontext =  "->";

void drawMenu(void) {
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);


  int yPosition = 35;  // Vertical position of the horizontal line
  display.drawLine(0, yPosition, display.width(), yPosition, BLACK);

  int bottom = display.height() -1 ;  // Vertical position of the horizontal line
  display.drawLine(0, bottom, display.width(), bottom, BLACK);


  // Draw a vertical line at the start of the display
  display.drawLine(0, yPosition, 0, display.height(), BLACK);

  // Draw a vertical line in the first third of the display
  int centerX1 = display.width() / 3;  // X position of the vertical line in the center
  display.drawLine(centerX1, yPosition, centerX1, display.height(), BLACK);

  // Draw a vertical line in the second third of the display
  int centerX2 = display.width() / 3 * 2;  // X position of the vertical line in the center
  display.drawLine(centerX2, yPosition, centerX2, display.height(), BLACK);


  // Draw a vertical line at the right of the display
  int bottomX = display.width() - 1;  // X position of the vertical line at the right edge
  display.drawLine(bottomX, yPosition, bottomX, display.height(), BLACK);

  // for (uint8_t i=0; i < 168; i++) {
    // if (i == '\n') continue;
  display.print(description);
  
  // Print text inside each box
  int sectionWidth = display.width() / 3; 
  
  // Left button text
  display.setCursor(2, yPosition + 3);  // Slightly offset to ensure it's inside the box
  display.print(leftButtontext);

  // Middle button text
  display.setCursor(display.width()/2  - 2, yPosition + 3);  // Offset to fit in the middle box
  display.print(middleButtontext);

  // Right button text
  display.setCursor(sectionWidth * 2 + 13, yPosition + 3);  // Offset to fit in the right box
  display.print(rightButtontext);

  // Update the display with the drawn content
  display.display();


}

void renderDisplay(){
   display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(75);

  // display.display(); // show splashscreen

  drawMenu();
  
  delay(2000);

  display.clearDisplay(); 
}
