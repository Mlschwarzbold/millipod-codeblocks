#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "definitions.h"
#include "raylib.h"

int LeRankingTexto(JOGADOR lista[], char nomearq[]);

JOGADOR stringToJogador(char buffer[]);

int InsereJog(JOGADOR lista[], JOGADOR Jog);

//void ChecaDuplicata (JOGADOR lista[], JOGADOR Jog);

void sortPlayers(JOGADOR jogadores[], int n_jogadores);

void ordenaJogadores(JOGADOR * jogador);

int save_ranking(JOGADOR lista[], char nomearq[]);

void imprimeRanking(JOGADOR jogadores[]);


#endif
