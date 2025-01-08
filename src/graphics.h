#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <Arduino.h>


void drawBitmap(int x, int y, const uint8_t* bitmap);
void animateFlappyBird(int x, int y);
void drawGround(int y);
void drawObstacle(int x, int gapY);
void drawStartScreen();
void drawMeniu1();
void drawMeniu2();
void drawMeniu3();
void drawDifficultyEasy();
void drawDifficultyMedium();
void drawDifficultyHard();   
void drawmusic1();
void drawmusic2();
void drawmusic3();
void drawmusic4();

#endif // GRAPHICS_H