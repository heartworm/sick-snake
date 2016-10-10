#ifndef INTERFACE_H
#define INTERFACE_H

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define NONE 4

#include <stdlib.h>
#include <String.h>

#include "switches.h"
#include "graphics.h"
#include "main.h"

typedef uint8_t numbool;

struct BodyPart {
	int x;
	int y;
	struct BodyPart *next;
} head;

struct {
	int x;
	int y;
} fruit;

struct Hitbox {
	int x1, y1, x2, y2;
} statBox, wall1, wall2, wall3;

int flashCounter;
int lives;
int score;
int direction;
numbool growSnake;
numbool gameOver;
numbool wallsOn;


void drawBodyParts();
void drawFruit();
void drawStats();
void drawGame();

void initGame(numbool reset);
void stepGame();
void handleButton(uint8_t buttonState);
void moveSnake();
void addSnek(int x, int y, struct BodyPart* tail);
void dockLife();

numbool snekCollision(struct Hitbox a, numbool noHead);
numbool checkCollision(struct Hitbox a, struct Hitbox b);
void moveFruit();

struct Hitbox get3Hitbox(int x, int y);
//bool isColliding();


#endif