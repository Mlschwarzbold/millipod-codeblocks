#include "scoreboard.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

JOGADOR stringToJogador(char buffer[]){
    JOGADOR jogador;
    char *token;

    token = strtok(buffer, ";");

    strcpy(jogador.nome, token);

    token = strtok(NULL, ";");


    jogador.pontuacao = atoi(token);

    return jogador;
}


int LeRankingTexto(JOGADOR lista[], char nomearq[]){
    int index;
    FILE *fp;
    char buffer[BUFFER_SIZE];

    //nomearq = strcat("./scoreboard/", nomearq);

    if ((fp = fopen(nomearq, "r")) == NULL){
        printf("erro na leitura do arquivo------------------\n");
        return 0;
    }
    else
    {
        index = 0;
        while (fgets(buffer, sizeof(buffer), fp) && index < MAX_NUM_SCORES){
                lista[index] = stringToJogador(buffer);
                index++;
        }
        fclose (fp);
    }
    return index;
}

int InsereJog(JOGADOR lista[], JOGADOR Jog){
    int index = 0;
    int encontrado = 0;

    while(index < MAX_NUM_SCORES && lista[index].nome[0]){

        index++;

    }

    if(!encontrado){
        lista[index] = Jog;
    }

    return index;
}

void sortPlayers(JOGADOR jogadores[], int n_jogadores)
{
    JOGADOR tmp;
    int index = 1;

    // Gnome sort time

    while(index < n_jogadores)
    {
        if(jogadores[index].pontuacao > jogadores[index-1].pontuacao)
        {
            tmp = jogadores[index];
            jogadores[index] = jogadores[index-1];
            jogadores[index-1] = tmp;
            if(index > 1) index--;
        } else
            index++;

    }

}

void ordenaJogadores(JOGADOR jogadores[])
{
    sortPlayers(jogadores, MAX_NUM_SCORES + 1);
}

int save_ranking(JOGADOR lista[], char nomearq[]){
    int index;
    FILE *fp;

    if ((fp = fopen(nomearq, "w")) == NULL){
        printf("erro na escrita do arquivo------------------\n");
        return 0;
    }

    index = 0;
    while(index < MAX_NUM_SCORES && lista[index].nome[0]){
        //printf("%d\n", index);

        fprintf(fp, "%s;%d\n", lista[index].nome, lista[index].pontuacao);
        index++;
    }



    fclose(fp);
    return 1;

}

void imprimeRanking(JOGADOR jogadores[])
{
    int index = 0;
    while(index < MAX_NUM_SCORES && jogadores[index].nome[0])
    {
        printf("%d  -- %5d -- %s\n", index+1, jogadores[index].pontuacao, jogadores[index].nome);
        index++;
    }
}

