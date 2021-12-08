#include "file.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
int checkIfFileExists(char* filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 1;
    }

    return 0;
}

int checkMatchFile(char * filename) // Checking matches file (If it's correct, if it's not changed rows or anything string for int)
{
    int   inEnd, ids[6];
    char  buffer[128];
    FILE * file = fopen(filename, "r");

    
    while(!(feof(file)))
    {
            if((fscanf(file, "%5s", buffer)) != 1)
        {
            fclose(file);
            return 0;
        }
        if(strcmp(buffer, "match") != 0)
        {
            fclose(file);
            return 0;
        }
        if((fscanf(file, "%d,%d,%d", &ids[0], &ids[1], &ids[2])) != 3)
        {
            fclose(file);
            return 0;
        }
        if(ids[0] == ids[1] || ids[0] == ids[2] || ids[1] == ids[2])
        {
            fclose(file);
            return 0;
        }
        if((fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd)) != 9)
        {
            fclose(file);
            return 0;
        }
        if((fscanf(file, "%d,%d,%d", &ids[3], &ids[4], &ids[5])) != 3)
        {
            fclose(file);
            return 0;
        }
        if(ids[3] == ids[4] || ids[3] == ids[5] || ids[4] == ids[5])
        {
            fclose(file);
            return 0;
        }
        if(ids[0] == ids[3] || ids[0] == ids[4] || ids[0] == ids[5] || ids[1] == ids[3] || ids[1] == ids[4] || ids[1] == ids[5] || ids[2] == ids[3] || ids[2] == ids[4] || ids[2] == ids[5])
        {
            fclose(file);
            return 0;
        }
        if((fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd)) != 9)
        {
            fclose(file);
            return 0;
        }
        if((fscanf(file, "%5s", buffer)) != 1)
        {
            fclose(file);
            return 0;
        }
        if(strcmp(buffer, "red") != 0 && strcmp(buffer, "blue") != 0)
        {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}
int checkPlayersFile(char * filename)
{
    int   inEnd;
    char  buffer[128];
    FILE * file = fopen(filename, "r");
        
    while(!(feof(file)))
    {
        if((fscanf(file, "%d,%s",&inEnd, buffer)) != 2)
        {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

int getCountOfPlayers(char * filename)
{
    int count = 0, inEnd;
    char buffer[128];
    FILE * file = fopen(filename, "r");
    while(!(feof(file)))
    {
        if(fscanf(file, "%d,%s",&inEnd, buffer) == 2)
        {
            if(strlen(buffer) > 16 || strlen(buffer) < 3)
            {
                fclose(file);
                return -1;
            }
            count++;
        }
    }
    fclose(file);
    return count;
}
int getCountOfMatches(char * filename)
{
    int count = 0;
    char buffer[128];
    FILE* file = fopen(filename, "r");
    while(!(feof(file)))
    {
        if(fscanf(file, "%s", buffer) == 1)
        {
            if(!((strcmp(buffer, "match")) != 0))
            {
                count++;
            }
        }
    }
    fclose(file);
    return count;
}

int decideId(int id, PLAYER * players, int countOfPlayers)
{
    for(int i = 0; i < countOfPlayers; i++)
    {
        if(players[i].id == id)
            return 1;
    }
    return 0;
}

int controlMatches(char * filename, PLAYER * players, int countOfPlayers)
{
    KDA kda[6];
    int ids[6], inEnd = 0, outEnd = 0;
    char buffer[128];
    FILE* file = fopen(filename, "r");
    while(!(feof(file)))
    {
        fscanf(file, "%5s", buffer);
        fscanf(file, "%d,%d,%d", &ids[0], &ids[1], &ids[2]);
        fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &kda[0].kills, &kda[0].deaths, &kda[0].assists, &kda[1].kills, &kda[1].deaths, &kda[1].assists, &kda[2].kills, &kda[2].deaths, &kda[2].assists);
        fscanf(file, "%d,%d,%d", &ids[3], &ids[4], &ids[5]);
        for(int i = 0; i < 6; i++)
        {   
            if(!(decideId(ids[i], players, countOfPlayers)))
            {
                return -1;
            }
        }
        fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &kda[3].kills, &kda[3].deaths, &kda[3].assists, &kda[4].kills, &kda[4].deaths, &kda[4].assists, &kda[5].kills, &kda[5].deaths, &kda[5].assists);
        fscanf(file, "%5s", buffer);
    }
    return 0;

}

void initMatches(char * filename, MATCH * matches, PLAYER * players, int countOfmatches)
{
    KDA kda[6];
    int ids[6];
    char buffer[128];
    FILE * file = fopen(filename, "r");

    for(int i = 0; i < countOfmatches; i++)
    {
        fscanf(file, "%5s", buffer);
        fscanf(file, "%d,%d,%d", &ids[0], &ids[1], &ids[2]);
        fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &kda[0].kills, &kda[0].deaths, &kda[0].assists, &kda[1].kills, &kda[1].deaths, &kda[1].assists, &kda[2].kills, &kda[2].deaths, &kda[2].assists);
        fscanf(file, "%d,%d,%d", &ids[3], &ids[4], &ids[5]);
        fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &kda[3].kills, &kda[3].deaths, &kda[3].assists, &kda[4].kills, &kda[4].deaths, &kda[4].assists, &kda[5].kills, &kda[5].deaths, &kda[5].assists);
        fscanf(file, "%5s", buffer);
    }
    fclose(file);

}