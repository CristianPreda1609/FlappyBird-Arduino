#include "game_logic.h"
#include "game_config.h"
#include "consts.h"
#include "graphics.h"
#include "melody.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;
extern enum Difficulty dif;
void setupGame() {
  switch(dif){
        case EASY:
          obstacleSpeed = 5;
          gap = 14;
          break;
        case MEDIUM:
          obstacleSpeed = 10;
          gap = 10;
          break;
        case HARD:
          obstacleSpeed = 15;
          gap = 6;
          break;
      }
}
// Check for collision
bool checkCollision(int birdX, int birdY, int obstacleX, int gapY) {
  if (birdX + birdWidth > obstacleX && birdX < obstacleX + 8) {
    if (birdY < gapY - gap || birdY + birdHeight > gapY + gap) {
      return true;
    }
  }

  return birdY >= SCREEN_HEIGHT - 8 || birdY <= 0; // Collision with ground or out of bounds
}

void gameLogic() {
  if (!gameStarted) {
    // Display the start screen
    drawStartScreen();
    
    // Check joystick press (any direction) or interrupt to start the game
    xValue = analogRead(VRX_PIN); 
    yValue = analogRead(VRY_PIN);
    if (xValue < lowerTrigger || yValue < lowerTrigger || yValue > upperTrigger || xValue > upperTrigger) {  // Joystick moved
      gameStarted = true;
    }
    
    delay(30);  // Small delay to debounce
  }
  else{
    if (!gameOver) {
      display.clearDisplay();

      // Joystick input for bird control
      xValue = analogRead(VRX_PIN);
      if (xValue < 400) { // Joystick moved up
        birdVelocity = jumpPower;
      }

      // Apply gravity to the bird
      birdVelocity += gravity;
      birdY += birdVelocity;
      // Check if the bird successfully passes the obstacle
      if (!passedObstacle && obstacleX + 8 < birdX) { // Bird's x-position is 30
        score++;            // Increment the score
        passedObstacle = true; // Mark the obstacle as passed
      }
      // Update obstacle position
      obstacleX -= obstacleSpeed;
      if (obstacleX < -8) {
        obstacleX = SCREEN_WIDTH;         
        passedObstacle = false; 
        centerGapY = random(10,40); 
      }
      // Increase obstacle speed every 5 seconds
      unsigned long currentTime = millis();
      if (currentTime - lastSpeedIncreaseTime >= 5000) {
        obstacleSpeed += 0.5;
        lastSpeedIncreaseTime = currentTime;
      }
      // Draw the bird
      animateFlappyBird(birdX, birdY);

      // Draw the ground
      drawGround(SCREEN_HEIGHT - 8);

      // Draw the obstacle
      drawObstacle(obstacleX, centerGapY);

      // Check for collisions
      if (checkCollision(birdX, birdY, obstacleX, centerGapY)) {
        gameOver = true;
      }

      // Display score
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("Score: ");
      display.print(score);

      display.display();
      delay(30);
    } else {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(10, 20);
      display.print("Game Over");

      display.setTextSize(1);
      display.setCursor(10, 50);
      display.print("Score: ");
      display.print(score);

      display.display();

      // Reset game on joystick press
      xValue = analogRead(VRX_PIN);
      yValue = analogRead(VRY_PIN);
      if (xValue < lowerTrigger || yValue < lowerTrigger || yValue > upperTrigger || xValue > upperTrigger) { // Joystick moved up
        centerGapY = random(10,40);
        birdY = 32;
        birdVelocity = 0;
        obstacleX = SCREEN_WIDTH;
        score = 0;
        gameOver = false;
        setupGame();
        lastSpeedIncreaseTime = millis(); // Reset the timer
      }
    }
  }
}
