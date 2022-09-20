#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "fazendeiro.h"
#include "playerControl.h"
#include "cogumelo.h"
#include "gamestate.h"
#include "milipede.h"
#include "aranha.h"

// Load Textures
void initializeTextures (Texture2D textures[]) {
  textures[FAZENDEIRO_INDEX] = LoadTexture("./src/sprites/fazendeiro.png");
  textures[COGUMELO_INDEX] = LoadTexture("./src/sprites/cogumelo.png");
}

int main(void)
{


    // Initialization
    //--------------------------------------------------------------------------------------
    PLAYERINPUT playerInput = {{0, 0}, 0};
    Texture2D textures[NUM_TEXTURES];
    GAMESTATE currentGameState;

    // Init window first, otherwise we get a segfault for trying to load textures before the GPU is ready
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGTH, "Mili-pede");

    // Initialize variables
    initializeTextures(textures);
    initializeGameState(&currentGameState);

    initializeAranhas(&currentGameState);
    initializeMilipede(&currentGameState);

    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        onFrame(&currentGameState, &playerInput, textures);
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
