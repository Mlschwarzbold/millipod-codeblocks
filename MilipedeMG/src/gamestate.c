#include "gamestate.h"

// Makes a shot from the player into its target direction
void shoot(GAMESTATE *gameState) {
  RAYCOLLISION2D shotCollision;

  // Make a shot
  shotCollision = collideCogumelos(gameState->fazendeiro, gameState->cogumelos);
  collideAranhas(gameState->fazendeiro, gameState->aranhas, &shotCollision);
  collideMilipede(gameState->fazendeiro, gameState->milipede, &shotCollision);
  // See if the shot actually hit something
  if (shotCollision.collisionType == cogumeloHit) {
    gameState->cogumelos[shotCollision.targetIndex].state = INATIVO;
    gameState->fazendeiro.score += 100;

    //decrease the to_eat counter
    ateCogumelo(&gameState->fazendeiro);

  }

  if (shotCollision.collisionType == aranhaHit) {
    gameState->aranhas[shotCollision.targetIndex].state = INATIVO;
    gameState->fazendeiro.score += 150;
  }

if (shotCollision.collisionType == milipedeHit) {
    gameState->fazendeiro.score += shortenMilipede(&gameState->milipede);
  }

  // Draw the shot
  DrawLineV(gameState->fazendeiro.position, Vector2Add(gameState->fazendeiro.position, Vector2Scale(gameState->fazendeiro.aimDirection, MAX_DISTANCE)), MAGENTA);

  // Reset the firing delay
  gameState->fazendeiro.firing_delay_frames = FIRING_DELAY;


}

// Initializer all variables related to the game state
void initializeGameState(GAMESTATE *gameState) {
  Vector2 playerStartingPos = {200.0f, 200.0f};
  Rectangle cogumeloSpawnArea = {SPRITE_SIZE, SPRITE_SIZE, SCREEN_WIDTH - 2 * SPRITE_SIZE, SCREEN_HEIGTH - 2 * SPRITE_SIZE - 100};

  initializeFazendeiro(&gameState->fazendeiro, playerStartingPos, "Wanderley");
  initializeCogumelos(gameState->cogumelos, cogumeloSpawnArea);

  SetRandomSeed(time(0));
}

// Draws the game area
void drawGame(GAMESTATE gameState, Texture2D textures[]) {
  ClearBackground(DARKPURPLE);
  DrawText(TextFormat("Nome: %s | Pontuacao: %d", gameState.fazendeiro.name, gameState.fazendeiro.score), 0, 0, 40, WHITE);
  drawSpiders(gameState.aranhas);
  drawMilipede(gameState.milipede);
  drawCogumelos(gameState.cogumelos, gameState.currentAnimationFrame, textures[COGUMELO_INDEX]);
  drawFazendeiro(gameState.fazendeiro, gameState.currentAnimationFrame, textures[FAZENDEIRO_INDEX]);
}

// Updates the frame count used in animations
void updateFrameCount(GAMESTATE *gameState)
{
	  // Update
        gameState->currentTime += GetFrameTime();
        // update current animation frames every 1/fps seconds
        if (gameState->currentTime > 1 / ANIMATION_FPS) {
          if (gameState->currentAnimationFrame < NUM_ANIMATION_FRAMES-1)
            gameState->currentAnimationFrame++;
          else gameState->currentAnimationFrame = 0;
          gameState->currentTime = 0;
        }

}


void monsterHit(GAMESTATE *gameState){
    //If the fazendeiro is invulnerable, ignore monster collisions
    if(gameState->fazendeiro.i_frames==0){
        //test hit against spiders
        if( aranhaFazendeiroCollidesAll(gameState->aranhas, gameState->fazendeiro)){
            gameState->fazendeiro.doente += 1;
            gameState->fazendeiro.i_frames = I_FRAMES;
            gameState->fazendeiro.to_eat = COGUMELOS_TO_EAT -1;
        }
        //test hit against milipede
        if( milipedeFazendeiroCollides(gameState->milipede, gameState->fazendeiro)){
            gameState->fazendeiro.doente += 1;
            gameState->fazendeiro.i_frames = I_FRAMES;
            gameState->fazendeiro.to_eat = COGUMELOS_TO_EAT -1;
        }
    }
}

void killFazendeiro(GAMESTATE *gameState){
    if(gameState->fazendeiro.doente == 2){
        CloseWindow();
    }
}
