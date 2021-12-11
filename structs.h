#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define K 30


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
void  initPlayers(char * filename, PLAYER * players, int countOfPlayers);
PLAYER getPlayer(int id, PLAYER * players, int countOfPlayers);
int getPlayersMmr(int id, PLAYER * players, int countOfPlayers);
int countTeamMmr(PLAYER * players);


void countPlayerMmr(int enemyMmr, int countOfPlayers, int id, PLAYER * players, bool winner);
void setPlayerMatch(int countOfPlayers, int id, PLAYER * players, bool winner, KDA kda);
void setAll(char * filename, int countOfMatches, PLAYER * players, int countOfPlayers);