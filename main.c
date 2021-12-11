#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "file.h"
#include "structs.h"
#include "htmlcreator.h"
int main(int argc, char** argv)
{ 
    if(argc < 4) // Controling if I have enough arguments
    {
        printf("Not enough arguments");
        return -1; // Not enough arguments
    }

    for(int i = 1; i <=2; i++) 
    {
        if(!(checkIfFileExists(argv[i]))) // Controling if both files exist
        {
            printf("One of the 2 files doesn't exist");
            return -1; // One of the 2 files doesn't exist
        }
    }
    if(!(checkPlayersFile(argv[2])))
    {
        return -1; // in players file is something wrong
    }
    if(!(checkMatchFile(argv[1])))
    {
        return -1 ;// in match file is something wrong
    }

    int countOfPlayers = getCountOfPlayers(argv[2]);

    int countOfMatches = getCountOfMatches(argv[1]);
    
    PLAYER *players = malloc(sizeof(PLAYER) * countOfPlayers);
    MATCH *matches = malloc(sizeof(MATCH) * countOfMatches);


    initPlayers(argv[2], players, countOfPlayers);
    if(!(matchControler(argv[1], players, countOfPlayers)))
    {
        freeMatches(matches);
        freePlayers(players);
        return -1;
    }

    setAll(argv[1], countOfMatches, players, countOfPlayers);
    for(int i = 0; i < countOfPlayers; i++)
    createHtml(argv[3], players, countOfPlayers);
    freePlayers(players);
    freeMatches(matches);

    return 0;
}