#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H
#include <Arduino.h>
#include <consts.h>
// Game configuration
extern int birdY;                // Bird's Y position
extern int birdVelocity;         // Bird's vertical speed
extern const float gravity;      // Gravity affecting the bird
extern const int jumpPower;      // Bird's jump power
extern int obstacleX;            // Initial position of the obstacle
extern int score;                // Player's score
extern bool gameOver;            // Game state
extern bool passedObstacle;      // Tracks if the bird has passed the current obstacle
extern int centerGapY;           // CenterGapY for the obstacle
extern float obstacleSpeed;        // Speed of the obstacle
extern int character1PozArray;   // Bird position
extern int character2PozArray;   // Bird position
extern bool gameStarted;         // Game state
extern int gap;                  // Gap between the pipes
extern int xValue;               // Joystick input
extern int yValue;               // Joystick input
extern unsigned long lastSpeedIncreaseTime;

// Menu configuration
extern bool inMenu;              // Menu state
extern int menuSelection;        // Current menu selection
extern int difficulty;           // Selected difficulty
extern int character;            // Selected character


#endif // GAME_CONFIG_H