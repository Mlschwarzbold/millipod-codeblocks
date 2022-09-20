#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "raylib.h"
#include "raymath.h"

#define SPRITE_SIZE 64
#define ANIMATION_FPS 8.0f
#define TEXTURE_SCALE 1.5f

#define SCREEN_WIDTH 800
#define SCREEN_HEIGTH 900
#define MAX_DISTANCE SCREEN_WIDTH + SCREEN_HEIGTH

#define NUM_COGUMELOS 30
#define NUM_ARANHAS 2
#define NUM_MAX_SEGMENTOS 10


#define NUM_TEXTURES 2
#define NUM_ANIMATION_FRAMES 2
#define AIM_RADIUS SPRITE_SIZE*TEXTURE_SCALE/2
#define COGUMELO_COLLECT_DISTANCE SCREEN_WIDTH + SCREEN_HEIGTH

#define ARANHA_SPEED 5
#define MILIPEDE_SPEED 4
#define MILIPEDE_DESCENT_SPEED 2

#define MILIPEDE_HITBOX_WIDTH 50
#define MILIPEDE_HITBOX_HEIGHT 60

#define ARANHA_HITBOX_WIDTH 40
#define ARANHA_HITBOX_HEIGHT 40

#define COGUMELO_HITBOX_WIDTH 50
#define COGUMELO_HITBOX_HEIGHT 50

#define TAM_NOME 64
#define MAX_NUM_SCORES 5
#define BUFFER_SIZE TAM_NOME + 32

#define FIRING_DELAY 15

typedef enum RenderOrder {FAZENDEIRO_INDEX, COGUMELO_INDEX, NUM_RENDER_LAYERS}RENDERINDEX;
typedef enum RenderDirections {BAIXO, CIMA, ESQUERDA, DIREITA, NUM_DIRECOES}RENDERDIRECTION;
typedef enum CogumeloStates {ATIVO, INATIVO}COGUMELOSTATE;
typedef enum HitTypes {nothing = -1, cogumeloHit, milipedeHit, aranhaHit}HITTYPE;

typedef struct {
    char nome[TAM_NOME];
    int pontuacao;
} JOGADOR;

typedef struct {
  Vector2 position;
  int doente;
  float speed;
  int direction;
  Vector2 aimDirection;
  char name[12];
  int score;
  int firing_delay_frames;
} FAZENDEIRO;


typedef struct {
  Vector2 position;
  int state;
} COGUMELO;

typedef struct {
  Vector2 position;
  Vector2 velocity;
} ARANHA;

typedef struct {
  Vector2 position;
  int state;
} MILIPEDE_SEGMENT;


typedef struct {
  Vector2 position;
  int direction;
  int descendFrames;
  int state;
  MILIPEDE_SEGMENT segments[NUM_MAX_SEGMENTOS];
} MILIPEDE_HEAD;


typedef struct {
  FAZENDEIRO fazendeiro;
  COGUMELO cogumelos[NUM_COGUMELOS];
  ARANHA aranhas[NUM_ARANHAS];
  MILIPEDE_HEAD milipede;
  float currentTime;
  int currentAnimationFrame;
} GAMESTATE;

typedef struct {
  Vector2 movement;
  Vector2 mousePosition;
  int shooting;
} PLAYERINPUT;

typedef struct {
  float collisionDistance;
  int targetIndex;
  HITTYPE collisionType;
} RAYCOLLISION2D;


#endif
