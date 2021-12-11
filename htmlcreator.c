#include "structs.h"
#include "htmlcreator.h"


char* getDivision(PLAYER player)
{
    if(player.mmr >= 0 && player.mmr <= 1149)
        return "Bronze";
    else if(player.mmr >= 1150 && player.mmr <= 1499)
            return "Silver";
        else if(player.mmr >= 1500 && player.mmr <= 1849)
                    return "Gold";
                else if(player.mmr >= 1900 && 2199)
                        return "Platinum";
                        else return "Diamond";
}
void createHtml(char * filename, PLAYER * players, int countOfPlayers)
{
    FILE * file = fopen(filename, "w+");
    fprintf(file, "<!DOCTYPE html> \n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css\">\n<title>League of legend - Elo rating</title>\n</head>\n<body>\n");
    fprintf(file, "<table class=\"table table-striped table-bordered table-hover table-sm\">\n<thead class=\"thead-dark\">\n<tr>\n<th>#</th>\n<th>Summoner name</th>\n<th>MMR (Rating)</th>\n<th>Division</th>\n<th>K/A/D (KAD)</th>\n<th>Average KAD</th>\n<th>Matches won/played</th>\n<th>Winrate</th>\n</tr>\n</thead>\n");
    fprintf(file, "<tbody>\n");
    for(int i = 0; i < countOfPlayers; i++)
    {
        fprintf(file, "<tr>\n");
        fprintf(file, "<td>%d</td>\n", players[i].id);
        fprintf(file, "<td>%s</td>\n", players[i].summonerName);
        fprintf(file, "<td>%d</td>\n", players[i].mmr);
        fprintf(file, "<td>%s</td>\n", getDivision(players[i]));
        fprintf(file, "<td>%d/%d/%d</td>\n", players[i].kda.kills, players[i].kda.assists, players[i].kda.deaths);
        fprintf(file, "<td>%.2f:%d</td>\n", ((players[i].kda.kills + players[i].kda.assists)/(float)players[i].kda.deaths), players[i].gamePlayed);
        fprintf(file, "<td>%d/%d</td>\n", players[i].gameWon, players[i].gamePlayed);
        fprintf(file, "<td>%.0f</td>\n",(players[i].gameWon/(float)players[i].gamePlayed)*100);
        fprintf(file, "</tr>\n");
    }
    fprintf(file, "</tbody>\n</table>\n</body>\n</html>\n");
}