#include "milipede.h"

void initializeMilipede(MILIPEDE_HEAD * milipede){
    int index;

    milipede->position.x = 50 + (rand() % SCREEN_WIDTH) * 0.6;
    milipede->position.y = -50;
    milipede->direction = 1;
    milipede->state = ATIVO;
    milipede->descendFrames = 30;
    for(index=0; index < NUM_MAX_SEGMENTOS; index++)
    {
        initializeMilipedeSegment(&milipede->segments[index]);
    }

}

void initializeMilipedeSegment(MILIPEDE_SEGMENT * segment){
    segment->state = ATIVO;
    segment->position.x = -100;
    segment->position.y = -100;
}
void updateMilipede(MILIPEDE_HEAD * milipede, GAMESTATE * gamestate){
    if(milipede->state == INATIVO)
        return;

    //test collision on next frame
    if(testMilipedeNextFrameCollision(milipede, gamestate))
    {
        if(milipede->descendFrames == 0) milipede->direction *= -1;
        milipede->descendFrames = MILIPEDE_DESCENT_FRAMES;

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

    updateSegments(milipede);

    // Kills the milipede if it goes below the screen
    if(milipede->position.y > SCREEN_HEIGTH)
        milipede->state = INATIVO;
}

void updateSegments(MILIPEDE_HEAD * milipede){
    int index = 1;

    segmentFollow(&milipede->segments[0], milipede->position);

    while(index < NUM_MAX_SEGMENTOS){
        segmentFollow(&milipede->segments[index], milipede->segments[index - 1].position);
        index++;
    }

}


int testMilipedeNextFrameCollision(MILIPEDE_HEAD * milipede, GAMESTATE * gamestate){
    //Generate the next frame position
    MILIPEDE_HEAD nextFrameMilipede = *milipede;

    if(milipede->descendFrames > 0){
        //descend
        nextFrameMilipede.position.y += MILIPEDE_DESCENT_SPEED;
    }
    else {
        //move normally
        nextFrameMilipede.position.x += milipede->direction * MILIPEDE_SPEED;

    }

    if(milipedeBorderCollision(nextFrameMilipede.position) || milipedeCogumeloCollidesAll(nextFrameMilipede, milipede, gamestate->cogumelos))
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
int milipedeCogumeloCollidesAll(MILIPEDE_HEAD milipede, MILIPEDE_HEAD * real_milipede, COGUMELO cogumelos[]){
    int index;

    for(index=0; index < NUM_COGUMELOS; index++)
    {
        if(milipedeCogumeloCollides(milipede, cogumelos[index])){

            lengthenMilipede(real_milipede);
            destroyCogumelo(cogumelos, index);
            return 1;
            }
    }
    return 0;

}

void killMilipede(GAMESTATE * gamestate){
    gamestate->milipede.state = 0;

}


int milipedeFazendeiroCollides(MILIPEDE_HEAD milipede, FAZENDEIRO player){
    Rectangle hitbox_milipede;
    Rectangle hitbox_player;

    // establishing the correct hitbox for the milipede
    hitbox_milipede.x = milipede.position.x;
    hitbox_milipede.y = milipede.position.y;
    hitbox_milipede.height = MILIPEDE_HITBOX_HEIGHT;
    hitbox_milipede.width = MILIPEDE_HITBOX_WIDTH;

    // establishing the correct hitbox for the fazendeiro
    hitbox_player.x = player.position.x;
    hitbox_player.y = player.position.y;
    hitbox_player.height = FAZENDEIRO_HITBOX_HEIGHT;
    hitbox_player.width = FAZENDEIRO_HITBOX_WIDTH;

    if(milipede.state == INATIVO) // cannot collide with inactive/destroyed milipede
        return 0;

    if(CheckCollisionRecs(hitbox_milipede, hitbox_player))
        return 1;
    else
        return 0;


}

void segmentFollow(MILIPEDE_SEGMENT * segment, Vector2 prev){
    if( Vector2Distance(segment->position, prev) > MILIPEDE_FOLLOW_DISTANCE){
        segmentMoveTo(segment, prev);
    }
}

void segmentMoveTo(MILIPEDE_SEGMENT * segment, Vector2 prev){
    // Source for equations at https://www.desmos.com/calculator/0al5rllk9m?lang=pt-BR
    double A = segment->position.x;  // segment X
    double B = prev.x;  // prev X
    double C = segment->position.y;  // segment Y
    double D = prev.y;  // prev Y
    double E =  B - A;  // segment vector x
    //double F = ;  // prev vector x
    double G = D - C;  // segment vector y
    //double H = ;  // prev vector y


    double a = pow(E, 2) + pow(G, 2);
    double b = 2 * (A * E + C * G - B * E - D * G);
    double c = pow(A,2) + pow(B,2) + pow(C,2) + pow(D,2) - 2 * A * B - 2 * D * C - pow(MILIPEDE_FOLLOW_DISTANCE,2);


    // quadratic equation (Bhaskara)
    //
    //       __________
    // -b - V b²-4ac
    // -----------------
    //          2a

    double delta = pow(b, 2) - (4 * a * c);

    double t;

    if(delta < 0) return 0; // Caso algo errado haja acontecido, para a função.

    t = (- b - sqrt( delta )) / (2 * a);

    segment->position.x = A + E * t;
    segment->position.y = C + G * t;

    //segment->position.x = 300;
    //segment->position.y = 300;
}

void drawMilipede(MILIPEDE_HEAD milipede){
    int index = 0;

    if(milipede.state == ATIVO){
    //draw the head
        //DrawText("o", milipede.position.x, milipede.position.y, 80, YELLOW);
        DrawCircleV(milipede.position, 30, YELLOW);

    //draw the body
        while(index < NUM_MAX_SEGMENTOS){
            if(milipede.segments[index].state == ATIVO)
                DrawCircleV(milipede.segments[index].position, 25, YELLOW);
            //else
                //DrawCircleV(milipede.segments[index].position, 25, GRAY);

            index++;
        }
    }

}

void collideMilipede(FAZENDEIRO fazendeiro, MILIPEDE_HEAD milipede, RAYCOLLISION2D * collision){
  Vector2 fazendeiroAimMaxRange = Vector2Add(fazendeiro.position, Vector2Scale(fazendeiro.aimDirection, MAX_DISTANCE));
  float currentDistance,
        minDistance = collision->collisionDistance;
  int i;

    // Check if milipede head is active and in the aim line
    if (milipede.state == ATIVO &&
        CheckCollisionPointLine(milipede.position, fazendeiro.position, fazendeiroAimMaxRange, AIM_RADIUS))
    {
      currentDistance = Vector2Distance(milipede.position, fazendeiro.position);
      // Check if it is closer than the current target
      if (currentDistance < minDistance) {
        // Update the collision, minDistance and the closest target position
        collision->collisionDistance = currentDistance;
        collision->collisionType = milipedeHit;
        collision->targetIndex = -1;

      }
    }

}


int shortenMilipede(MILIPEDE_HEAD * milipede){
    int index = 0;
    if(milipede->segments[0].state == INATIVO){
        milipede->state = INATIVO;
        return 300;
    }
    // Travels the segments until the last one, be that the max number of segments or the last active segment
    while(index < NUM_MAX_SEGMENTOS && milipede->segments[index].state == ATIVO){
        index++;
    }
    milipede->segments[index - 1].state = INATIVO;

    return 250;
}


void respawnMilipede(MILIPEDE_HEAD * milipede){
    if(milipede->state == INATIVO){
        initializeMilipede(milipede);
    }

}

void lengthenMilipede(MILIPEDE_HEAD * milipede){
    int index = 0;
    // Travels the segments until the last one, be that the max number of segments or the last active segment
    while(index < NUM_MAX_SEGMENTOS && milipede->segments[index].state == ATIVO){
        index++;
    }
    milipede->segments[index].state = ATIVO;

    return 250;

}
