#pragma once
#include "structs.h"

int checkIfFileExists(char * filename);
int checkMatchFile(char * filename);
int checkPlayersFile(char * filename);

int getCountOfPlayers(char * filename);
int getCountOfMatches(char * filename);
int decideId(int ids, PLAYER * players, int countOfPlayers);
int controlMatches(char * filename, PLAYER * players, int countOfPlayers);


void initMatches(char * filename, MATCH * matches, PLAYER * players, int countOfmatches);
void initOneMatch(char * filename, MATCH match, PLAYER * players, int * idPlayers, KDA* kda);
