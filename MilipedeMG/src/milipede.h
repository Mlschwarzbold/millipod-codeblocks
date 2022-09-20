
#ifndef MILIPEDE_H
#define MILIPEDE_H

#include "definitions.h"
#include "raylib.h"


void initializeMilipede(GAMESTATE * gamestate);

void initializeMilipedeSegment(MILIPEDE_SEGMENT * segment);

void updateMilipede(MILIPEDE_HEAD * milipede, GAMESTATE * gamestate);

int testMilipedeNextFrameCollision(MILIPEDE_HEAD milipede, GAMESTATE * gamestate);

int milipedeBorderCollision(Vector2 position);

int milipedeCogumeloCollides(MILIPEDE_HEAD milipede, COGUMELO cogumelo);

int milipedeCogumeloCollidesAll(MILIPEDE_HEAD milipede, COGUMELO cogumelos[]);

void killMilipede(GAMESTATE * gamestate);

void drawMilipede(MILIPEDE_HEAD milipede);

#endif

