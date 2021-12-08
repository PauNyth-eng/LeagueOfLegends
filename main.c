//Incluading headers
#include <stdio.h>
#include <malloc.h>
//Incluading my headers
#include "file.h"
#include "structs.h"

int main(int argc, char** argv)
{ 
    if(argc < 4)
    {
        printf("Not enough arguments");
        return -1; // Not enough arguments
    }

    for(int i = 1; i <=2; i++)
    {
        if(!(checkIfFileExists(argv[i])))
        {
            printf("One of the 2 files doesn't exist");
            return -1; // One of the 2 files doesn't exist
        }
    }

    if(!(checkMatchFile(argv[1])))
    {
        return -1 ;// in match file is something wrong
    }
    if(!(checkPlayersFile(argv[2])))
    {
        return -1; // in players file is something wrong
    }

    int countOfPlayers = getCountOfPlayers(argv[2]);
    if(countOfPlayers == -1)
    {
        return -1; // One of the names do not following LoL rules (Having less than 3 or more than 16 symbols
    }
    int countOfMatches = getCountOfMatches(argv[1]);
    PLAYER *players = malloc(sizeof(PLAYER) * countOfPlayers);
    MATCH *matches = malloc(sizeof(MATCH) * countOfMatches);
    int playersFailure = initPlayers(argv[2],players, countOfPlayers);
    if(playersFailure == -1)
    {
        printf("Something went wrong");
        freeMatches(matches);
        freePlayers(players);
        return -1;
    }
    if(controlMatches(argv[1], players, countOfPlayers) == -1)
    {
        printf("Something went wrong 2");
        freeMatches(matches);
        freePlayers(players);
        return -1;
    }


    freePlayers(players);
    freeMatches(matches);

    return 0;
}