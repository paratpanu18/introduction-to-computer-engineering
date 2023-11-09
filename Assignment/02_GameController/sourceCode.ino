#include "ST7735_TEE.h"
TEE_ST7735 lcd(9,10,11,12,13); //Arduino  csk,sda,A0,rst,cs

// Variable Init
const int shipSize = 2;
const int bulletSize = 5;
const int enemySize = 5;
const int maxBullet = 15;
bool isGameOver = false;

class Enemy {
public:
  int posX, posY;
  bool status;

  void Init() {
    status = true;
    posX = (rand() %  100) + 10;
    posY = 0;
  };

  void Draw() {
    lcd.fillRect(posX, posY, enemySize, enemySize, RED);
  };

  void Update() {
    if (posY > 160) isGameOver = true;

    if (!status) {
      Init();
    }

    if (status) posY++;
  };

  void Erase() {
    lcd.fillRect(posX, posY, bulletSize, bulletSize, BLACK);
  };

} enemy;

class Bullet {
public:
  bool status = false;
  int posX, posY;
  
  void Draw() {
    lcd.fillRect(posX, posY, bulletSize, bulletSize, WHITE);
  };

  void Update() {
    if (status) posY -= 2;
    if (posY < 0) status = false;

    // Collision Check
    if (posX < enemy.posX + enemySize &&
        posX + bulletSize > enemy.posX &&
        posY + bulletSize > enemy.posY &&
        posY < enemy.posY + enemySize) {
      enemy.status = false;
      this->status = false;
    }
  };

  void Erase() {
    lcd.fillRect(posX, posY, bulletSize, bulletSize, BLACK);
  };


} bullet[maxBullet];


class Player {
public:
  int posX = 10, posY = 10;
  int spd = 1;
  void Draw() {
    lcd.drawChar(posX, posY, 'A', GREEN, shipSize);
  };

  void Erase() {
    lcd.drawChar(posX, posY, 'A', BLACK, shipSize);
  };

  void Update() {
    // Move X
    if (analogRead(0) < 500 && posX - 1 > 0) posX -= spd;
    else if (analogRead(0) > 520 && posX + 13 < 128) posX += spd;

    // Move Y
    if (analogRead(1) < 500 && posY + 15 < 160) posY += spd;
    else if (analogRead(1) > 520 && posY - 1 > 0) posY -= spd;

    // Bullet Shoot
    if (!digitalRead(2)) {
      for (int i = 0; i < maxBullet; i++) {
        if (!bullet[i].status) {
          bullet[i].status = true;
          bullet[i].posX = this->posX;
          bullet[i].posY = this-> posY;
          break;
        }
      }
    }


    if (!digitalRead(3)) {
      this->spd = 3;
    }
    else this->spd = 1;
  };

} ship;



void setup()
{
  Serial.begin(9600);
  // LCD Setup
  lcd.init(lcd.VERTICAL);
  lcd.fillScreen(BLACK);

  // Joystick Setup
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  while (!isGameOver) {
      ship.Erase();
      for (int i = 0; i < maxBullet; i++) {
        bullet[i].Erase();
      }
      enemy.Erase();


      ship.Update();
      for (int i = 0; i < maxBullet; i++) {
        if (bullet[i].status) bullet[i].Update();
      }
      enemy.Update();


      ship.Draw();
      for (int i = 0; i < maxBullet; i++) {
        if (bullet[i].status) bullet[i].Draw();
      }
      enemy.Draw();
  }

  // Game Over Handle
  lcd.fillScreen(BLACK);
  while (true) {
    lcd.drawString(10, 70, "Game Over", GREEN, 2);
  }
}


