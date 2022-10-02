#ifndef FAZENDEIRO_H
#define FAZENDEIRO_H

#include "definitions.h"
#include "raylib.h"

// Initializes the player
void initializeFazendeiro(FAZENDEIRO *fazendeiro, Vector2 position, char name[]);

// Updates the player position
void updateFazendeiroPosition(FAZENDEIRO *fazendeiro, Vector2 movimento);

// Updates the direction at which the player is looking
void updateFazendeiroDirection(FAZENDEIRO *fazendeiro, Vector2 mousePosition);

// Updates the firing delay
void updateFazendeiroFiringDelay(FAZENDEIRO *fazendeiro);

// Updates the invulnerability frames counter
void updateFazendeiroI_Frames(FAZENDEIRO *fazendeiro);

// Draws and animates the player
void drawFazendeiro(FAZENDEIRO fazendeiro, int currentFrame, Texture2D texture);

// remedies the player if he eats enough mushrooms
void ateCogumelo(FAZENDEIRO * fazendeiro);

#endif
