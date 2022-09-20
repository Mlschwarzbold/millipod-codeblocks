#include "aranha.h"

void initializeAranhas(GAMESTATE * gamestate){
    int index;
    for(index=0; index < NUM_ARANHAS; index++){
        gamestate->aranhas[index].position.x = 300;
        gamestate->aranhas[index].position.y = 300;
        gamestate->aranhas[index].velocity.x = 5;
        gamestate->aranhas[index].velocity.y = 5;
    }
}

void updateAllSpiders(ARANHA aranhas[], GAMESTATE * gamestate){
    int index;
    for(index=0; index < NUM_ARANHAS; index++)
    {
        updateSpiderPositionAndMushrooms(&aranhas[index], gamestate);
    }

}


// Updates a single spider`s position and also removes the eaten mushrooms
void updateSpiderPositionAndMushrooms(ARANHA *aranha, GAMESTATE * gamestate){
    // Stop the spider from going out of bounds
    aranha->velocity = Vector2Multiply(aranha->velocity, testAranhaNextFrameCollision(*aranha, gamestate));

    aranha->position = Vector2Add(aranha->position, aranha->velocity);


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
    if(aranha.position.x < 0 || aranha.position.y < 0 || aranha.position.x > SCREEN_WIDTH|| aranha.position.y > SCREEN_HEIGTH)
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

void drawSpiders(ARANHA aranhas[]){
    int index;
    for(index = 0; index < NUM_ARANHAS; index++)
    {
        //DrawText("*", aranhas[index].position.x, aranhas[index].position.y, 40, WHITE);
        DrawCircleV(aranhas[index].position, 30, PURPLE);
    }

}
