#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "definitions.h"
#include "cogumelo.h"

// Makes a shot from the player into its target direction
void shoot(GAMESTATE *gameState);

// Tests and accounts for enemy damaga
void monsterHit(GAMESTATE *gameState);

// Initialize all variables related to the game state
void initializeGameState(GAMESTATE *gameState);

// Draws the game area
void drawGame(GAMESTATE gameState, Texture2D textures[]);

// Updates the frame count used in animations
void updateFrameCount(GAMESTATE *gameState);


// Conditions to kill the fazendeiro
void killFazendeiro(GAMESTATE *gameState);


#endif
