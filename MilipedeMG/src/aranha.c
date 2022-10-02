#include "aranha.h"


void initializeAranhas(GAMESTATE * gamestate){
    int index;
    for(index=0; index < NUM_ARANHAS; index++){
        initializeAranha(&gamestate->aranhas[index]);
    }
}

void initializeAranha(ARANHA * aranha){
        aranha->position.x = 50 + (rand() % SCREEN_WIDTH) * 0.6;
        aranha->position.y = -300 - (rand() & 300);
        if(rand() % 2)
            aranha->velocity.x = 5;
        else
            aranha->velocity.x = -5;
        aranha->velocity.y = 5;
        aranha->state = ATIVO;
}

void respawnAranha(ARANHA aranhas[]){
    int index = 0;

    // Travels the aranhas until the last one, be that the max number of aranhas or the last active aranha.
    while(index < NUM_ARANHAS && aranhas[index].state == ATIVO){
        index++;
    }

    if(index < NUM_ARANHAS){
        initializeAranha(&aranhas[index]);
    }

}



void updateAllSpiders(ARANHA aranhas[], GAMESTATE * gamestate){
    int index;
    for(index=0; index < NUM_ARANHAS; index++)
    {
        if(aranhas[index].state == ATIVO)
            updateSpiderPositionAndMushrooms(&aranhas[index], gamestate);
    }

}


// Updates a single spider`s position and also removes the eaten mushrooms
void updateSpiderPositionAndMushrooms(ARANHA *aranha, GAMESTATE * gamestate){
    // Stop the spider from going out of bounds
    aranha->velocity = Vector2Multiply(aranha->velocity, testAranhaNextFrameCollision(*aranha, gamestate));

    aranha->position = Vector2Add(aranha->position, aranha->velocity);

    // Kills the spider if it goes below the screen
    if(aranha->position.y > SCREEN_HEIGTH)
        aranha->state = INATIVO;


}

Vector2 testAranhaNextFrameCollision(ARANHA aranha, GAMESTATE * gamestate){
    // Takes the entire gamestate, tests for all possible spider collisions, and returns a vector 2 with 1 for no collision in x and y, and -1 for future collision.
    Vector2 output;
    //creates the next-frame positions for x and y movement
    Vector2 nextFrameXPos = {aranha.position.x + aranha.velocity.x, aranha.position.y};
    Vector2 nextFrameYPos = {aranha.position.x, aranha.position.y + aranha.velocity.y};

    //tests for collision on x-axis
    aranha.position = nextFrameXPos;
    if( aranhaBorderCollides(aranha) || aranhaCogumeloCollidesAll(aranha, gamestate->cogumelos)){
        output.x = -1;
    } else {
        output.x = 1;
    }

    //tests for collision on y-axis
    aranha.position = nextFrameYPos;
    if( aranhaBorderCollides(aranha) || aranhaCogumeloCollidesAll(aranha, gamestate->cogumelos)){
        output.y = -1;
    } else {
        output.y = 1;
    }

    return output;

}




int aranhaBorderCollides(ARANHA aranha)
{
    if(aranha.position.x < 0 || (aranha.position.y < 0 && aranha.velocity.y < 0) || aranha.position.x > SCREEN_WIDTH)
        return 1;
    else
        return 0;

}

int aranhaCogumeloCollides(ARANHA aranha, COGUMELO cogumelo){

    Rectangle hitbox_aranha;
    Rectangle hitbox_cogumelo;

    // establishing the correct hitbox for the spider
    hitbox_aranha.x = aranha.position.x;
    hitbox_aranha.y = aranha.position.y;
    hitbox_aranha.height = ARANHA_HITBOX_WIDTH;
    hitbox_aranha.width = ARANHA_HITBOX_WIDTH;

    // establishing the correct hitbox for the mushroom
    hitbox_cogumelo.x = cogumelo.position.x;
    hitbox_cogumelo.y = cogumelo.position.y;
    hitbox_cogumelo.height = COGUMELO_HITBOX_HEIGHT;
    hitbox_cogumelo.width = COGUMELO_HITBOX_WIDTH;

    if(cogumelo.state == INATIVO) // cannot collide with inactive/destroyed mushroom
        return 0;

    if(CheckCollisionRecs(hitbox_aranha, hitbox_cogumelo))
        return 1;
    else
        return 0;

}

// tests the collision of one spider against all of the mushrooms
int aranhaCogumeloCollidesAll(ARANHA aranha, COGUMELO cogumelos[]){
    int index;

    for(index=0; index < NUM_COGUMELOS; index++)
    {
        if(aranhaCogumeloCollides(aranha, cogumelos[index])){

            destroyCogumelo(cogumelos, index);
            return 1;
            }
    }
    return 0;

}

int aranhaFazendeiroCollides(ARANHA aranha, FAZENDEIRO player){
    Rectangle hitbox_aranha;
    Rectangle hitbox_player;

    // establishing the correct hitbox for the spider
    hitbox_aranha.x = aranha.position.x;
    hitbox_aranha.y = aranha.position.y;
    hitbox_aranha.height = ARANHA_HITBOX_HEIGHT;
    hitbox_aranha.width = ARANHA_HITBOX_WIDTH;

    // establishing the correct hitbox for the fazendeiro
    hitbox_player.x = player.position.x;
    hitbox_player.y = player.position.y;
    hitbox_player.height = FAZENDEIRO_HITBOX_HEIGHT;
    hitbox_player.width = FAZENDEIRO_HITBOX_WIDTH;

    if(aranha.state == INATIVO) // cannot collide with inactive/destroyed spider
        return 0;

    if(CheckCollisionRecs(hitbox_aranha, hitbox_player))
        return 1;
    else
        return 0;


}

// tests the collision of all the spiders against the player
int aranhaFazendeiroCollidesAll(ARANHA aranhas[], FAZENDEIRO player){
    int index;

    for(index=0; index < NUM_ARANHAS; index++)
    {
        if(aranhaFazendeiroCollides(aranhas[index], player) && aranhas[index].state == ATIVO){
            return 1;
            }
    }
    return 0;
}




void drawSpiders(ARANHA aranhas[]){
    int index;
    for(index = 0; index < NUM_ARANHAS; index++)
    {
        //DrawText("*", aranhas[index].position.x, aranhas[index].position.y, 40, WHITE);
        if(aranhas[index].state == ATIVO)
            DrawCircleV(aranhas[index].position, 30, PURPLE);
    }

}


void collideAranhas(FAZENDEIRO fazendeiro, ARANHA aranhas[], RAYCOLLISION2D * collision){
  Vector2 fazendeiroAimMaxRange = Vector2Add(fazendeiro.position, Vector2Scale(fazendeiro.aimDirection, MAX_DISTANCE));
  float currentDistance,
        minDistance = collision->collisionDistance;
  int i;

  for (i = 0; i < NUM_ARANHAS; i++) {
    // Check if spider is active and in the aim line
    if (aranhas[i].state == ATIVO &&
        CheckCollisionPointLine(aranhas[i].position, fazendeiro.position, fazendeiroAimMaxRange, AIM_RADIUS))
    {
      currentDistance = Vector2Distance(aranhas[i].position, fazendeiro.position);
      // Check if it is closer than the current target
      if (currentDistance < minDistance) {
        // Update the collision, minDistance and the closest target position
        collision->collisionDistance = currentDistance;
        collision->collisionType = aranhaHit;
        collision->targetIndex = i;

      }
    }
  }
}
