#pragma once
#include "structs.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
bool checkIfFileExists(char * filename);
bool checkMatchFile(char * filename);
bool checkPlayersFile(char * filename);

int getCountOfPlayers(char * filename);
int getCountOfMatches(char * filename);
bool idControler(int ids, PLAYER * players, int countOfPlayers);
bool matchControler(char * filename, PLAYER * players, int countOfPlayers);


