#ifndef ARANHA_H
#define ARANHA_H

#include "definitions.h"
#include "raylib.h"


void initializeAranhas(GAMESTATE * gamestate);

void updateAllSpiders(ARANHA aranhas[], GAMESTATE * gamestate);

//updates
void updateSpiderPositionAndMushrooms(ARANHA *aranha, GAMESTATE * gamestate);

Vector2 testAranhaNextFrameCollision(ARANHA aranha, GAMESTATE * gamestate);

int aranhaBorderCollides(ARANHA aranha);


int aranhaCogumeloCollides(ARANHA aranha, COGUMELO cogumelo);

int aranhaCogumeloCollidesAll(ARANHA aranha, COGUMELO cogumelos[]);

void drawSpiders(ARANHA aranhas[]);

#endif

