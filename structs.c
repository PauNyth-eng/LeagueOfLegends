#include "file.h"
#include "structs.h"
/**
 * @brief Function freePlayers -> Will free memory in heap of Players
 * 
 * @param players -> PLAYER* - List of players
 */
void freePlayers(PLAYER * players)
{
    free(players);
    players = NULL;
}
/**
 * @brief Function freeMatches -> Will free memory in heap of Matches
 * 
 * @param matches -> MATCH* - list of matches
 */
void freeMatches(MATCH * matches)
{
    free(matches);
    matches = NULL;
}
/**
 * @brief Function: initPlayers -> Will fill list of players with players from file
 * 
 * @param filename -> String - Name of file
 * @param players -> PLAYER* - List of players
 * @param countOfPlayers -> Int - count of players
 */
void initPlayers(char * filename, PLAYER * players, int countOfPlayers)
{
    FILE * file = fopen(filename, "r");
    int inEnd;
    char buffer[16];
    int i = 0;
    for(int i = 0; i < countOfPlayers; i++)
    {
        if((fscanf(file, "%d,%s",&inEnd, buffer)) == 2)
        {
            
            players[i].id = inEnd;
            strcpy(players[i].summonerName, buffer);
            players[i].gameWon = 0;
            players[i].gamePlayed = 0;
            players[i].mmr = 1000;
            players[i].kda.kills = 0;
            players[i].kda.assists = 0;
            players[i].kda.deaths = 0;
        }
    }
}
/**
 * @brief Function: getPlayer -> Will get player with selected id
 * 
 * @param id -> Int - id of player we want
 * @param players -> PLAYER* - List of players
 * @param countOfPlayers -> Int - COunt of players
 * @return player -> Chosen player
 */
PLAYER getPlayer(int id, PLAYER * players, int countOfPlayers)
{
    PLAYER player;

    for(int i = 0; i < countOfPlayers; i++)
    {
        if(id == players[i].id)
        {
            player = players[i];
        }
    }
    return player;
}
/**
 * @brief Function: getPlayersMmr -> Will get mmr of players with specific id
 * 
 * @param id -> Int - id of player
 * @param players -> PLAYER* - List of players
 * @param countOfPlayers -> Int - COunt of players
 * @return int -> mmr of chosen player
 */
int getPlayersMmr(int id, PLAYER * players, int countOfPlayers)
{
    for(int i = 0; i < countOfPlayers; i++)
    {
        if(id == players[i].id)
        {
            return players[i].mmr;
        }
    }
}
/**
 * @brief Function: setNewMmr -> Will set new mmr to the selected player
 * 
 * @param players -> PLAYER* - List of players
 * @param countOfPlayers -> Int - COunt of players
 * @param newMmr -> Int - new mmr
 * @param id -> Int - id if players
 */
void setNewMmr(PLAYER * players, int countOfPlayers, int newMmr, int id)
{
    for(int i = 0; i < countOfPlayers; i++)
    {
        if(id == players[i].id)
        {
            players[i].mmr = newMmr;
        }
    }
}
/**
 * @brief Function: countPlayerMmr -> Will count new mmr for player
 * 
 * @param enemyMmr -> Int - team mmr from enemy team
 * @param countOfPlayers -> Int - COunt of players
 * @param id -> Int - id if players
 * @param players -> PLAYER* - List of players
 * @param winner -> bool - If team of player won
 */
void countPlayerMmr(int enemyMmr, int countOfPlayers, int id, PLAYER * players, bool winner)
{
    float ra = getPlayersMmr(id, players, countOfPlayers);
    float rb = enemyMmr;
    float ea = (1.0/(1 + pow(10.0, (rb-ra)/400)));
    int sa;
    if(winner)
    {
        sa = 1;
    }else{
        sa = 0;
    }
    int newMmr = round(ra + K * (sa-ea));
    setNewMmr(players, countOfPlayers, newMmr, id);

}

void setPlayerMatch(int countOfPlayers, int id, PLAYER * players, bool winner, KDA kda)
{
    for(int i = 0; i < countOfPlayers; i++)
    {
        
        if(id == players[i].id)
        {
            if(winner)
            {
                players[i].gameWon += 1;
            }
            players[i].gamePlayed += 1;
            players[i].kda.kills += kda.kills;
            players[i].kda.deaths += kda.deaths;
            players[i].kda.assists += kda.assists;
        }
    }
}

/**
 * @brief Function: setAllMmr -> Will set new mmr to the whole match
 * 
 * @param filename -> String - Name of file
 * @param countOfMatches -> Int - COunt of matches
 * @param players PLAYER* - List of players
 * @param countOfPlayers -> Int - COunt of players
 */
void setAll(char * filename, int countOfMatches, PLAYER * players, int countOfPlayers)
{
    KDA kda[6];
    int ids[6];
    char buffer[128];
    int redTeamMmr = 0, blueTeamMmr = 0;

    FILE * file = fopen(filename, "r");

    for(int i = 0; i < countOfMatches; i++)
    {
        fscanf(file, "%5s", buffer);
        fscanf(file, "%d,%d,%d", &ids[0], &ids[1], &ids[2]);
        fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &kda[0].kills, &kda[0].assists, &kda[0].deaths, &kda[1].kills, &kda[1].assists, &kda[1].deaths, &kda[2].kills, &kda[2].assists, &kda[2].deaths);
        fscanf(file, "%d,%d,%d", &ids[3], &ids[4], &ids[5]);
        fscanf(file, "%d;%d;%d,%d;%d;%d,%d;%d;%d", &kda[3].kills, &kda[3].assists, &kda[3].deaths, &kda[4].kills, &kda[4].assists, &kda[4].deaths, &kda[5].kills, &kda[5].assists, &kda[5].deaths);
        fscanf(file, "%5s", buffer);
        
        for(int j = 0; j < 3; j++)
            redTeamMmr += getPlayersMmr(ids[j], players, countOfPlayers);
        redTeamMmr = redTeamMmr/3;
        for(int j = 3; j < 6; j++)
            blueTeamMmr += getPlayersMmr(ids[j], players, countOfPlayers);   
        blueTeamMmr = blueTeamMmr/3;
        
        if(strcmp(buffer, "red") == 0)
        {
            for(int j = 0; j < 3; j++)
            {
                countPlayerMmr(blueTeamMmr, countOfPlayers, ids[j], players, true);
                setPlayerMatch(countOfPlayers, ids[j], players, true, kda[j]);
            }
            for(int j = 3; j < 6; j++)
            {
                countPlayerMmr(redTeamMmr, countOfPlayers,ids[j], players, false);
                setPlayerMatch(countOfPlayers, ids[j], players, false, kda[j]);
            }
        }
        else
        {
            for(int j = 0; j < 3; j++)
            {
                countPlayerMmr(blueTeamMmr, countOfPlayers, ids[j], players, false);
                setPlayerMatch(countOfPlayers, ids[j], players, false, kda[j]);
            }
            for(int j = 3; j < 6; j++)
            {
                countPlayerMmr(redTeamMmr, countOfPlayers, ids[j], players, true);
                setPlayerMatch(countOfPlayers, ids[j], players, true, kda[j]);
            }
        }
        redTeamMmr = 0;
        blueTeamMmr = 0;

    }
    fclose(file);

}