#include <stdio.h>
#include <stdlib.h>

typedef struct adventureGame {
    char command[1000];// Command typed by the user
    int room; // The room the user is in. Initialized to start in room#0
    char buf[1000];
    char lookArray[13][200];
    char moveArray[13][4][40];
    int moveToArray[13][4];
    int roomStatus[13];
    char monsterArray[13][20];
    int monsterStatusArray[13];
    int monsterFlag[13];
    int damageBase;
    int damageVampire;
    int damageWerewolf;
    int N_artifact;
    char artifact[9][16];
    int artifactLoc[9];
    int artifactStatus[9];
    int room10Status[2];
    int playerHP;
    int maxHP;
    int XP;
    int winFlag;
} adventureGame;


int processCommand(adventureGame *ag);
void processStart();
