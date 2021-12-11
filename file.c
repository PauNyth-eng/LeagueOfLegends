#include "structs.h"
#include "file.h"

/**
 *   @brief Function: checkIfFIleExist -> Checking file if it exist.
 *   @param fileName -> String - Name of file
 *   @return bool -> false - if file not exist / true - if file exists
 */    
bool checkIfFileExists(char* filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return true;
    }

    return false;
}
/**
 *   @brief Function: checkMatchFile -> Checking file called matches if it's correctly written.
 *   @param filename -> String - Name of file
 *   @return bool -> true - If file is written correctly. / false - If file is not written correctly.
 */
bool checkMatchFile(char * filename) // Checking matches file 
{
    int   inEnd, ids[6], lane = 1;
    char  buffer[128];
    FILE * file = fopen(filename, "r");

    
    while(!(feof(file)))
    {
        if((fscanf(file, "%s", buffer)) != 1)
        {
            printf("Something went wrong on lane %d", lane);
            fclose(file);
            return false;
        }
        if(strcmp(buffer, "match") != 0)
        {
            printf("On line %d, your word is different from predicted word \"match\" ", lane);
            fclose(file);
            return false;
        }
        lane++;
        if((fscanf(file, "%d,%d,%d", &ids[0], &ids[1], &ids[2])) != 3)
        {
            printf("Something went wrong on lane %d", lane);
            fclose(file);
            return false;
        }
        if(ids[0] == ids[1] || ids[0] == ids[2] || ids[1] == ids[2])
        {
            printf("you have 2 or more IDs same in one team on line %d", lane);
            fclose(file);
            return false;
        }
        lane++;
        if((fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd)) != 9)
        {
            printf("Something went wrong on lane %d", lane);
            fclose(file);
            return false;
        }
        lane++;
        if((fscanf(file, "%d,%d,%d", &ids[3], &ids[4], &ids[5])) != 3)
        {
            printf("Something went wrong on lane %d", lane);
            fclose(file);
            return false;
        }
        if(ids[3] == ids[4] || ids[3] == ids[5] || ids[4] == ids[5])
        {
            printf("you have 2 or more IDs same in one team on line %d", lane);
            fclose(file);
            return false;
        }
        if(ids[0] == ids[3] || ids[0] == ids[4] || ids[0] == ids[5] || ids[1] == ids[3] || ids[1] == ids[4] || ids[1] == ids[5] || ids[2] == ids[3] || ids[2] == ids[4] || ids[2] == ids[5])
        {
            printf("You have 2 or more IDs same in teams on lines %d and %d", lane, lane-2);
            fclose(file);
            return false;
        }
        lane++;
        if((fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd, &inEnd)) != 9)
        {
            printf("Something went wrong on lane %d", lane);
            fclose(file);
            return false;
        }
        lane++;
        if((fscanf(file, "%5s", buffer)) != 1)
        {
            printf("Something went wrong on lane %d", lane);
            fclose(file);
            return false;
        }
        if(strcmp(buffer, "red") != 0 && strcmp(buffer, "blue") != 0)
        {
            printf("On line %d, your word is different from predicted words \"red\" or \"blue\" ", lane);
            fclose(file);
            return false;
        }
    }
    fclose(file);
    return true;
}

/**
 *   @brief Function: checkPlayersFile -> Checking file called players if it's correctly written.
 *   @param filename -> String - Name of file
 *   @return bool ->  true - If file is written correctly. / false - If file is not written correctly.
 */
bool checkPlayersFile(char * filename) // Checking players file 
{
    int   inEnd, decide;
    char  buffer[128];
    FILE * file = fopen(filename, "r");
        
    while(!(feof(file)))
    {
        decide = fscanf(file, "%d,%s",&inEnd, buffer);

        if(strlen(buffer) > 16 || strlen(buffer) < 3)
        {
            fclose(file);
            return false;
        }
        if(decide == -1)
        {
            if((feof(file)))
                break;
            fclose(file);
            return true;
        }
        
        if(decide != 2)
        {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return true;
}

/**
 *   @brief Function: getCountOfPlayers -> Functions which counts number of players in "players" file.
 *   @param filename -> String - Name of file
 *   @return Int -> count - number of players in file
 */
int getCountOfPlayers(char * filename)
{
    int count = 0, inEnd;
    char buffer[128];
    FILE * file = fopen(filename, "r");
    while(!(feof(file)))
    {
        if(fscanf(file, "%d,%s",&inEnd, buffer) == 2)
        {           
            count++;
        }
    }
    fclose(file);
    return count;
}
/**
    @brief Function: getCountOfMatches -> Functions which counts number of matches in "matches" file.
    @param filename -> String - Name of file
    @return Int -> count - number of matches in file
**/
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
/**
 *   @brief Function: idControler ->  Function checks id of players in one mach if you there aren't same ids
 *   @param id -> Int - id of player
 *   @param players -> PLAYERS* - list of all players
 *   @param countOfPlayers -> Int - Count of players
 *   @return bool -> false - ID not exist / true - ID exists
 */
bool idControler(int id, PLAYER * players, int countOfPlayers)
{
    for(int i = 0; i < countOfPlayers; i++)
    {
        if(players[i].id == id)
            return true;
    }
    return false;
}
/**
 * @brief Function matchControler -> Controling file if exist ID in match and in players
 * 
 * @param filename -> String - Name of file
 * @param players -> PLAYERS* - list of all players
 * @param countOfPlayers -> Int - Count of players
 * @return bool -> True if IDs are different / false if at least 2 are same
 */
bool matchControler(char * filename, PLAYER * players, int countOfPlayers)
{
    KDA kda[6];
    int ids[6], inEnd = 0, outEnd = 0;
    char buffer[128];
    FILE* file = fopen(filename, "r");
    while(!(feof(file)))
    {
        fscanf(file, "%5s", buffer);
        fscanf(file, "%d,%d,%d", &ids[0], &ids[1], &ids[2]);
        fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &kda[0].kills, &kda[0].assists, &kda[0].deaths, &kda[1].kills, &kda[1].assists, &kda[1].deaths, &kda[2].kills, &kda[2].assists, &kda[2].deaths);
        fscanf(file, "%d,%d,%d", &ids[3], &ids[4], &ids[5]);
        for(int i = 0; i < 6; i++)
        {   
            if(!(idControler(ids[i], players, countOfPlayers)))
            {
                printf("You have an ID of player, who doesn't exist");
                return false;
            }
        }
        fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &kda[3].kills, &kda[3].assists, &kda[3].deaths   , &kda[4].kills, &kda[4].assists, &kda[4].deaths, &kda[5].kills, &kda[5].assists, &kda[5].deaths);
        fscanf(file, "%5s", buffer);
    }
    return  true;

}

