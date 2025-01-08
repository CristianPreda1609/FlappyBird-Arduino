#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <melody.h>
#include <consts.h>
#include <graphics.h>
#include <game_config.h>
#include <game_logic.h>


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Game configuration

int birdY = 32;                // Bird's Y position
int birdVelocity = 0;          // Bird's vertical speed
const float gravity = 1;       // Gravity affecting the bird
const int jumpPower = -5;      // Bird's jump power
int obstacleX = SCREEN_WIDTH;  // Initial position of the obstacle
int score = 0;                 // Player's score
bool gameOver = false;         // Game state
bool passedObstacle = false;   // Tracks if the bird has passed the current obstacle
int centerGapY = 0;            // CenterGapY for the obstacle
float obstacleSpeed = 5;        // Speed of the obstacle
int character1PozArray = 1;    // Bird position
int character2PozArray = 2;    // Bird position
bool gameStarted = false;      // Game state
int gap = 14;                  // Gap between the pipes
int xValue = 0;                // Joystick input
int yValue = 0;                // Joystick input
enum Difficulty dif = EASY;            // Selected difficulty
int inMeniuValue = 0;
bool select = 0;
unsigned long lastSpeedIncreaseTime = millis();
unsigned long last_interrupt_time = 0;
unsigned int debounce_delay = 200;
unsigned long last_select_time = 0;
bool soundOn = true;

// Menu configuration
bool inMenu = false;            // Menu state
int menuSelection = 0;         // Current menu selection
enum subMenu subMenuSelection = NONE;         // Current submenu selection
extern const int epd_bitmap_allDifficulties_LEN;


void musicCycle() {
  if (soundOn)
    playMelody();
  else
    noTone(BUZZER_PIN);
}
void handleButtonPress() {
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounce_delay) 
  {
    if (!inMenu) {
      inMenu = true; // Enter the menu
    }
    else {
      if(subMenuSelection == NONE){   
        inMenu = false;
      }else{
        subMenuSelection = NONE;
      }
    }
  }
  last_interrupt_time = interrupt_time;
}

void menu() {
  display.clearDisplay();
  display.setTextSize(1);
  if(subMenuSelection == NONE){
    if (menuSelection == 0) {
      drawMeniu1();
    } else if (menuSelection == 1) {
      drawMeniu2();
    } else if (menuSelection == 2) {
      drawMeniu3();
    }
  }else{
    if(subMenuSelection == MENU1){
      if(inMeniuValue%epd_bitmap_allDifficulties_LEN == 0){
        drawDifficultyEasy();
        if(select){
          dif = EASY;
          setupGame();
          subMenuSelection = NONE;
          select = false;
        }
      }else if(inMeniuValue%epd_bitmap_allDifficulties_LEN == 1){
        drawDifficultyMedium();
        if(select){
          dif = MEDIUM;
          setupGame();
          subMenuSelection = NONE;
          select = false;
        }
      }else if(inMeniuValue%epd_bitmap_allDifficulties_LEN == 2){
        drawDifficultyHard();
        if(select){
          dif = HARD;
          setupGame();
          subMenuSelection = NONE;
          select = false;
        }
      }
    }else if(subMenuSelection == MENU2){
      Serial.println(subMenuSelection);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(20, 5);
      display.print("Character");
      drawBitmap(55, 25, graphics[inMeniuValue]);
      // Debug prints for analog readings
      int vrxValue = analogRead(VRX_PIN);
      int vryValue = analogRead(VRY_PIN);
      Serial.print("VRX: ");
      Serial.println(vrxValue);
      Serial.print("VRY: ");
      Serial.println(vryValue);
      if(select){
        character1PozArray = inMeniuValue;
        character2PozArray = inMeniuValue+1;
        subMenuSelection = NONE;
        select = false;
      }
    }else if(subMenuSelection == MENU3){
      if (soundOn) {
        if(inMeniuValue%2 == 0){
          drawmusic1();
        }else{
          drawmusic3();
        }
      } else {
        if(inMeniuValue%2 == 0)
          drawmusic2();
        else
          drawmusic4();
      }
      if(select && inMeniuValue%2 == 1){
        soundOn = !soundOn;
        select = false;
        subMenuSelection = NONE;
      }


    }
  }

  display.display();
}
void menuLogic(){
    lastSpeedIncreaseTime = millis();
    musicCycle();
    menu();
    xValue = analogRead(VRX_PIN);
    yValue = analogRead(VRY_PIN);
    if(subMenuSelection == NONE){
      inMeniuValue = 0;
      if (xValue < lowerTrigger) {
        if (menuSelection == 0) {
          menuSelection = 2; 
        } else menuSelection--;
      }
      if(xValue > upperTrigger) {
        if (menuSelection == 2) {
          menuSelection = 0;
        } else menuSelection++;
      }
      if(yValue < lowerTrigger){
        switch(menuSelection){
          case 0:
            subMenuSelection = MENU1;
            break;
          case 1:
            subMenuSelection = MENU2;
            inMeniuValue++;
            break;
          case 2:
            subMenuSelection = MENU3;
            break;
        }

      }
    }else{
      if (yValue > upperTrigger) {
        if(subMenuSelection == MENU1){
          inMeniuValue++;
          delay(debounce_delay);
        }
        if(subMenuSelection == MENU2){
          if(inMeniuValue != graphicsLength - 1)
            inMeniuValue+=2;
          else inMeniuValue = 1;
          delay(debounce_delay);

        }
        if(subMenuSelection == MENU3){
          inMeniuValue++;
          delay(debounce_delay);

        }
      }
      if (yValue <= lowerTrigger) {
        if (millis() - last_select_time >= ONESEC) {
          select = true;
          last_select_time = millis();
        }
      }
      
    }
    
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
  pinMode(SW_PIN, INPUT_PULLUP); // Set switch pin as input
  attachInterrupt(digitalPinToInterrupt(SW_PIN), handleButtonPress, FALLING);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
  randomSeed(analogRead(5));
  centerGapY = random(10,40);
}


void loop(){
  if (inMenu) {
   menuLogic();
  } else {
    musicCycle();
    gameLogic();
  }
}