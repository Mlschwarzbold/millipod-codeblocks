
#ifndef MILIPEDE_H
#define MILIPEDE_H

#include "definitions.h"
#include "raylib.h"
#include "cogumelo.h"

void initializeMilipede(MILIPEDE_HEAD * milipede);

void initializeMilipedeSegment(MILIPEDE_SEGMENT * segment);

void updateMilipede(MILIPEDE_HEAD * milipede, GAMESTATE * gamestate);

int testMilipedeNextFrameCollision(MILIPEDE_HEAD *milipede, GAMESTATE * gamestate);

int milipedeBorderCollision(Vector2 position);

int milipedeCogumeloCollides(MILIPEDE_HEAD milipede, COGUMELO cogumelo);

int milipedeCogumeloCollidesAll(MILIPEDE_HEAD milipede, MILIPEDE_HEAD * real_milipede, COGUMELO cogumelos[]);

int milipedeFazendeiroCollides(MILIPEDE_HEAD milipede, FAZENDEIRO player);

void segmentFollow(MILIPEDE_SEGMENT * segment, Vector2 prev);

void segmentMoveTo(MILIPEDE_SEGMENT * segment, Vector2 prev);

void updateSegments(MILIPEDE_HEAD * milipede);

void killMilipede(GAMESTATE * gamestate);

void drawMilipede(MILIPEDE_HEAD milipede, int currentFrame, Texture2D texture);

void drawMilipedeSegment(MILIPEDE_SEGMENT segment, int currentFrame, Texture2D texture);

void collideMilipede(FAZENDEIRO fazendeiro, MILIPEDE_HEAD milipede, RAYCOLLISION2D * collision);

int shortenMilipede(MILIPEDE_HEAD * milipede);

void respawnMilipede(MILIPEDE_HEAD * milipede);

// Count the amount of segments the milipede has:
int countSegments(MILIPEDE_HEAD *milipede);

// Increase the number of segments of the milipede by 1
void lengthenMilipede(MILIPEDE_HEAD * milipede);
#endif

