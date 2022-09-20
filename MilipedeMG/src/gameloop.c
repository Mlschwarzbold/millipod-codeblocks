#include "gameloop.h"



void onFrame(GAMESTATE * gamestate, PLAYERINPUT * playerInput, Texture2D textures){

        updateFrameCount(gamestate);

        getInputFromKeyboard(playerInput);

        updateFazendeiroPosition( &gamestate->fazendeiro, playerInput->movement);

        updateFazendeiroDirection(&gamestate->fazendeiro, playerInput->mousePosition);

        updateFazendeiroFiringDelay(&gamestate->fazendeiro);

        BeginDrawing();

        if (playerInput->shooting && gamestate->fazendeiro.firing_delay_frames == 0) {
            shoot(gamestate);
        }


        updateAllSpiders(gamestate->aranhas, gamestate);

        updateMilipede(&gamestate->milipede, gamestate);




      // Draw
      drawGame(*gamestate, textures);

      EndDrawing();

}
