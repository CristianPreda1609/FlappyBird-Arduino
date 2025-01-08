#ifndef CONSTS_H
#define CONSTS_H
#include <Arduino.h>
// Bitmaps stored in PROGMEM
const uint8_t graphics[][8] PROGMEM = {
  { B00000000, B00000000, B00000000, B00000000, B00000000, B11111111, B11111111, B11111111 },  // Ground
  { B00000000, B00000000, B00011100, B00110110, B01111110, B00111100, B00001000, B00000000 }, // Bird 1
  { B00000000, B00000000, B00011100, B00111110, B01111110, B00111100, B00001000, B00000000 }, // Bird 2
  { 0b00000000, 0b10001100, 0b11011010, 0b11111111, 0b11111111, 0b11011110, 0b10001100, 0b00000000 }, // Fish 1
  { 0b00000000, 0b00101100, 0b00111010, 0b00111111, 0b00110011, 0b00111110, 0b00101100, 0b00000000 }, // Fish 2
  {   0b00000111,
  0b00000011,
  0b00000101,
  0b00001000,
  0b00010000,
  0b11100000,
  0b11100000,
  0b01100000 }, // Arrow Up
  {   0b01100000,
  0b11100000,
  0b11100000,
  0b00010000,
  0b00001000,
  0b00000101,
  0b00000011,
  0b00000111 }, // Arrow Down
  { B00000000, B01100110, B11111111, B11111111, B01111110, B00111100, B00011000, B00000000 }, // Heart Full
  { B00000000, B01100110, B11111111, B01111110, B00111100, B00011000, B00000000, B00000000 }, // Heart Half
  {   0b00011000,
  0b01111110,
  0b01111110,
  0b11111111,
  0b11111111,
  0b01111110,
  0b01111110,
  0b00011000 }, // Star
  { 0b11100111,
  0b10000001,
  0b10000001,
  0b00000000,
  0b00000000,
  0b10000001,
  0b10000001,
  0b11100111 }, // Outer Star
  { B00000000, B00111100, B01000010, B10100101, B10000001, B10100101, B01000010, B00111100 }, // Smiley Face
  { B00000000, B00111100, B01000010, B10011001, B10100101, B10011001, B01000010, B00111100 }, // Winking Face
  { 0b00000000, 0b10000100, 0b01111110, 0b10111111, 0b01111110, 0b10000100, 0b00000000, 0b00000000 }, // Spaceship 1
  { 0b10000000, 0b01000100, 0b10111110, 0b01111111, 0b10111110, 0b01000100, 0b10000000, 0b00000000 }, // Spaceship 2
};
const int graphicsLength = sizeof(graphics) / 8;

int const groundPozArray = 0;      // Ground position
const int birdWidth = 8;   // Bird's width
const int birdHeight = 8;  // Bird's height
const int birdX = 30;          // Bird's X position
const int lowerTrigger = 1;  // Lower trigger for joystick input
const int upperTrigger = 800;  // Upper trigger for joystick input
const int epd_bitmap_allDifficulties_LEN = 3;


enum Difficulty {
  EASY = 1,
  MEDIUM = 2,
  HARD = 3
};
enum subMenu {
  NONE = 0,
  MENU1 = 1,
  MENU2 = 2,
  MENU3 = 3
};


// Screen configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Joystick configuration
#define VRX_PIN A0
#define VRY_PIN A1
#define SW_PIN 2

// Buzzer configuration
#define BUZZER_PIN 6 // PWM-capable pin for the buzzer
#define ONESEC 1000
#endif // CONSTS_H