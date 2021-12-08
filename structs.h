#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    BLUE = 0,
    RED
}team;

typedef struct 
{
    int kills;
    int deaths;
    int assists;
}KDA;

typedef struct 
{
    int id;
    char summonerName[16];
    int gamePlayed;
    int gameWon;
    int mmr;
    KDA kda;
}PLAYER;

typedef struct 
{
    int idMatch;
    PLAYER redPlayers[3];
    PLAYER bluePlayers[3];
    team winnerTeam;
    int blueMmr;
    int redMmr;

}MATCH;


void freePlayers(PLAYER * players);

void freeMatches(MATCH * matches);

int  initPlayers(char * filename, PLAYER * players, int countOfPlayers);