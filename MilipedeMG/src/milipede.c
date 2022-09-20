#include "milipede.h"

void initializeMilipede(GAMESTATE * gamestate){
    int index;

    gamestate->milipede.position.x = 300;
    gamestate->milipede.position.y = 0;
    gamestate->milipede.direction = 1;
    gamestate->milipede.state = 1;
    gamestate->milipede.descendFrames = 0;
    for(index=0; index < NUM_MAX_SEGMENTOS; index++)
    {
        initializeMilipedeSegment(&gamestate->milipede.segments[index]);
    }

}

void initializeMilipedeSegment(MILIPEDE_SEGMENT * segment){
    segment->state = 1;
    segment->position.x = -100;
    segment->position.y = -100;
}
void updateMilipede(MILIPEDE_HEAD * milipede, GAMESTATE * gamestate){
    //test collision on next frame
    if(testMilipedeNextFrameCollision(*milipede, gamestate))
    {
        if(milipede->descendFrames == 0) milipede->direction *= -1;
        milipede->descendFrames = 15;

    }
    //update position
    if(milipede->descendFrames > 0){
        //descend
        milipede->position.y += MILIPEDE_DESCENT_SPEED;
        milipede->descendFrames -= 1;
    }
    else {
        //move normally
        milipede->position.x += milipede->direction * MILIPEDE_SPEED;
    }

}

int testMilipedeNextFrameCollision(MILIPEDE_HEAD milipede, GAMESTATE * gamestate){
    //Generate the next frame position
    MILIPEDE_HEAD nextFrameMilipede = milipede;

    if(milipede.descendFrames > 0){
        //descend
        nextFrameMilipede.position.y += MILIPEDE_DESCENT_SPEED;
    }
    else {
        //move normally
        nextFrameMilipede.position.x += milipede.direction * MILIPEDE_SPEED;

    }

    if(milipedeBorderCollision(nextFrameMilipede.position) || milipedeCogumeloCollidesAll(nextFrameMilipede, gamestate->cogumelos))
        return 1;
    else
        return 0;
}

int milipedeBorderCollision(Vector2 position){

    if(position.x < 0 || position.x > SCREEN_WIDTH - 30)
        return 1;
    else
        return 0;

}

int milipedeCogumeloCollides(MILIPEDE_HEAD milipede, COGUMELO cogumelo){

    Rectangle hitbox_milipede;
    Rectangle hitbox_cogumelo;

    // establishing the correct hitbox for the spider
    hitbox_milipede.x = milipede.position.x;
    hitbox_milipede.y = milipede.position.y;
    hitbox_milipede.height = MILIPEDE_HITBOX_HEIGHT;
    hitbox_milipede.width = MILIPEDE_HITBOX_WIDTH;

    // establishing the correct hitbox for the mushroom
    hitbox_cogumelo.x = cogumelo.position.x;
    hitbox_cogumelo.y = cogumelo.position.y;
    hitbox_cogumelo.height = COGUMELO_HITBOX_HEIGHT;
    hitbox_cogumelo.width = COGUMELO_HITBOX_WIDTH;

    if(cogumelo.state == INATIVO) // cannot collide with inactive/destroyed mushroom
        return 0;

    if(CheckCollisionRecs(hitbox_milipede, hitbox_cogumelo))
        return 1;
    else
        return 0;

}

// tests the collision of one spider against all of the mushrooms
int milipedeCogumeloCollidesAll(MILIPEDE_HEAD milipede, COGUMELO cogumelos[]){
    int index;

    for(index=0; index < NUM_COGUMELOS; index++)
    {
        if(milipedeCogumeloCollides(milipede, cogumelos[index])){

            destroyCogumelo(cogumelos, index);
            return 1;
            }
    }
    return 0;

}

void killMilipede(GAMESTATE * gamestate){
    gamestate->milipede.state = 0;

}




void drawMilipede(MILIPEDE_HEAD milipede){

    if(milipede.state == 1){
    //draw the head
        //DrawText("o", milipede.position.x, milipede.position.y, 80, YELLOW);
        DrawCircleV(milipede.position, 30, YELLOW);

    //draw the body
    //while(){}
    }

}
