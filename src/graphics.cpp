#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <graphics.h>
#include <consts.h>
#include <Adafruit_SSD1306.h>
#include <game_config.h>

extern const unsigned char* epd_bitmap_allArray[3];
extern const unsigned char* epd_bitmap_allDifficulties[3];
extern const unsigned char* epd_bitmap_musicarr[4];

extern Adafruit_SSD1306 display;
// Draw a bitmap from PROGMEM
void drawBitmap(int x, int y, const uint8_t* bitmap) {
  for (int i = 0; i < birdHeight; i++) { // 8 rows
    uint8_t row = pgm_read_byte(&(bitmap[i]));
    for (int j = 0; j < birdWidth; j++) { // 8 columns
      if (row & (1 << (7 - j))) {
        display.drawPixel(x + j, y + i, WHITE);
      }
    }
  }
}

// Draw a bitmap from PROGMEM
void drawBitmapScreen(const uint8_t* bitmap) {
  for (int i = 0; i < SCREEN_HEIGHT; i++) { // Iterate over rows
    for (int j = 0; j < SCREEN_WIDTH; j++) { // Iterate over columns
      uint8_t byte = pgm_read_byte(&(bitmap[i * (SCREEN_WIDTH / 8) + (j / 8)]));
      if (byte & (1 << (7 - (j % 8)))) {
        display.drawPixel(j, i, WHITE);
      }
    }
  }
}

// Draw the bird with flapping animation
void animateFlappyBird(int x, int y) {
  static bool toggle = false;
  if (toggle) {
    drawBitmap(x, y, graphics[character1PozArray]); // Bird 1
  } else {
    drawBitmap(x, y, graphics[character2PozArray]); // Bird 2
  }
  toggle = !toggle;
}

// Draw the ground
void drawGround(int y) {
  for (int x = 0; x < SCREEN_WIDTH; x += 8) {
    drawBitmap(x, y, graphics[groundPozArray]); // Ground bitmap
  }
}

// Draw the obstacle
void drawObstacle(int x, int gapY) {
  display.fillRect(x, 0, 8, gapY - gap, WHITE);                // Top pipe
  display.fillRect(x, gapY + gap, 8, SCREEN_HEIGHT - gapY, WHITE); // Bottom pipe
}

void drawStartScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.print("Move Joystick to");
  display.setCursor(55, 10);
  display.print("Start");
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("Character Selected:");
  drawBitmap(64, 40, graphics[character1PozArray]); // Bird 1
  display.display();
}

void drawMeniu1() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_allArray[0]);
  display.display();
}
void drawMeniu2() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_allArray[1]);
  display.display();
}
void drawMeniu3() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_allArray[2]);
  display.display();
}
void drawDifficultyEasy() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_allDifficulties[0]);
  display.display();
}
void drawDifficultyMedium() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_allDifficulties[1]);
  display.display();
}
void drawDifficultyHard() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_allDifficulties[2]);
  display.display();
}

void drawmusic1() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_musicarr[0]);
  display.display();
}
void drawmusic2() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_musicarr[1]);
  display.display();
}
void drawmusic3() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_musicarr[2]);
  display.display();
}
void drawmusic4() {
  display.clearDisplay();
  drawBitmapScreen(epd_bitmap_musicarr[3]);
  display.display();
}
