#include "structs.h"

void freePlayers(PLAYER * players)
{
    free(players);
    players = NULL;
}

void freeMatches(MATCH * matches)
{
    free(matches);
    matches = NULL;
}

int initPlayers(char * filename, PLAYER * players, int countOfPlayers)
{
    FILE * file = fopen(filename, "r");
    int inEnd;
    char buffer[16];
    int i = 0;
    while(!(feof(file)))
    {
        if((fscanf(file, "%d,%s",&inEnd, buffer)) == 2)
        {
            for(int j = 0; j < countOfPlayers; j++)
            {
                if(inEnd == players[j].id)
                {
                    return -1; // You can have more same players with same ID
                }
            }
            players[i].id = inEnd;
            strcpy(players[i].summonerName, buffer);
            players[i].gameWon = 0;
            players[i].gamePlayed = 0;
            players[i].mmr = 1000;
            players[i].kda.kills = 0;
            players[i].kda.assists = 0;
            players[i].kda.deaths = 0;
        }

        i++;
    }
    return 0;
}