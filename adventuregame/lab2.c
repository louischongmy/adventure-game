#include <string.h>
#include "lab2.h"

void processCalc(adventureGame *ag);

int mandatoryProcess(adventureGame *ag){ // a function that is called when some value inside the game has to be checked on whether it should be changed or not
    //part of the function where it determines the damage the player is going to deal
    //changed back to 2 so that the base is consistent even after dropping sword
    if (ag->artifactLoc[0]==-1) {
        ag->damageBase=4;
        ag->damageVampire=3;
        ag->damageWerewolf=4;
    } else {
        ag->damageBase=2;
        ag->damageVampire=2;
        ag->damageWerewolf=2;
    }
    if (ag->artifactLoc[2]==-1 && ag->artifactLoc[0]==-1){ag->damageVampire=4;}
    if (ag->artifactLoc[3]==-1){ag->damageWerewolf=6;}

    //part of the function where it checks whether the player can access Room 10 (The Courtyard)
    if (ag->monsterStatusArray[4]==0) {ag->room10Status[1]=1;}
    if (ag->room10Status[0]==1 && ag->room10Status[1]==1) {ag->moveToArray[4][1]=9;}

    //part of the function where it checks whether the player is dead and exits the program if it is
    //calls the function to calculate the final score
    if (ag->playerHP==0){
        printf("The %s has killed you, game over\n",ag->monsterArray[ag->room]);
        processCalc(ag);
        return (0);
    }

    //part of the function that checks if the respective enemy is dead so the player can pick up the item in the room
    if (ag->monsterStatusArray[6]==0) {ag->artifactStatus[6]=1;}
    if (ag->monsterStatusArray[9]==0) {ag->artifactStatus[2]=1;}
    if (ag->monsterStatusArray[12]==0) {ag->artifactStatus[1]=1;}

    //part of the function that checks if the player has returned to the Dungeon's Entrance with the golden chalice
    //ends the game if so and congratulate the player
    //calls the function to calculate the final score
    if (ag->room==0 && ag->artifactLoc[1]==-1){
        printf("Congratulations, you have returned to the Dungeon's Entrance with the Golden Chalice, you have completed the game\n");
        ag->winFlag=1;
        processCalc(ag);
        return (0);
    }
    return (1);
}

int processLook(adventureGame ag) {
    //create a flag to act if no artifact in room
    int objflag=0;
    printf("room situation:\n");
    printf("%s\n",ag.lookArray[ag.room]);
    // process any monster in the room
    printf("enemy situation:\n");
    if (ag.monsterStatusArray[ag.room]>0) {
        printf("There is a %s here\n",ag.monsterArray[ag.room]);
        printf("The %s is now at %dhp\n",ag.monsterArray[ag.room],ag.monsterStatusArray[ag.room]);
    }
    else if (ag.monsterStatusArray[ag.room]==0) {printf("There is a dead %s here\n",ag.monsterArray[ag.room]);}
    else if (ag.monsterStatusArray[ag.room]==-1) {printf("There are no enemies here you are safe\n");}
    // process any artifact in the room
    printf("item situation:\n");
    //for loop for every item of artifact
    int i;
    for (i=0;i<ag.N_artifact;i++) {
        if (ag.artifactLoc[i]==ag.room) {
            printf("You see %s here\n",ag.artifact[i]);
            //changing flag since there is artifact
            objflag=1;
        }
    }
    if (objflag==0){printf("There are no items in this room\n");}
    return(1);
}

int processMovement(adventureGame *ag) {
    if(strncmp(ag->command,"north",5)==0 || strncmp(ag->command,"n\n",3)==0) {
        if (ag->moveToArray[ag->room][0]!=-1) {
            printf("%s\n",ag->moveArray[ag->room][0]);
            ag->room=ag->moveToArray[ag->room][0];
            processLook(*ag);// Call function to print details of the new room
        } else printf("Unable to move north.\n");
    }
    else if (strncmp(ag->command,"south",5)==0 || strncmp(ag->command,"s\n",3)==0) {
        if (ag->moveToArray[ag->room][1]!=-1) {
            printf("%s\n",ag->moveArray[ag->room][1]);
            ag->room=ag->moveToArray[ag->room][1];
            processLook(*ag);// Call function to print details of the new room
        } else printf("Unable to move south.\n");
    }
    else if(strncmp(ag->command,"east",4)==0 || strncmp(ag->command,"e\n",3)==0) {
        if (ag->moveToArray[ag->room][2]!=-1) {
            printf("%s\n",ag->moveArray[ag->room][2]);
            ag->room=ag->moveToArray[ag->room][2];
            processLook(*ag);// Call function to print details of the new room
        } else printf("Unable to move east.\n");
    }
    else if(strncmp(ag->command,"west",4)==0 || strncmp(ag->command,"w\n",3)==0) {
        if (ag->moveToArray[ag->room][3]!=-1) {
            printf("%s\n",ag->moveArray[ag->room][3]);
            ag->room=ag->moveToArray[ag->room][3];
            processLook(*ag);// Call function to print details of the new room
        } else printf("Unable to move west.\n");
    }
    return(mandatoryProcess(ag));
}

int processKillMonster(adventureGame *ag) {
    if (ag->monsterStatusArray[ag->room]==0) {printf("The %s is already dead\n",ag->monsterArray[ag->room]);}
    if (ag->monsterStatusArray[ag->room]==-1) {printf("There is no enemy here\n");}
    if (ag->monsterStatusArray[ag->room]>=1) {
        if (ag->room==6 || ag->room==10){//vampires
            ag->monsterStatusArray[ag->room]=ag->monsterStatusArray[ag->room]-ag->damageVampire;
            if (ag->monsterStatusArray[ag->room]<0) {ag->monsterStatusArray[ag->room]=0;}
            printf("You dealt %d damage to the %s\n",ag->damageVampire,ag->monsterArray[ag->room]);
        }
        else if (ag->room==4){//werewolf
            ag->monsterStatusArray[ag->room]=ag->monsterStatusArray[ag->room]-ag->damageWerewolf;
            if (ag->monsterStatusArray[ag->room]<0) {ag->monsterStatusArray[ag->room]=0;}
            printf("You dealt %d damage to the %s\n",ag->damageWerewolf,ag->monsterArray[ag->room]);
        }
        else{//basic enemy
            ag->monsterStatusArray[ag->room]=ag->monsterStatusArray[ag->room]-ag->damageBase;
            if (ag->monsterStatusArray[ag->room]<0) {ag->monsterStatusArray[ag->room]=0;}
            printf("You dealt %d damage to the %s\n",ag->damageBase,ag->monsterArray[ag->room]);
        }
    }//Weaken or kill the monster
    if (ag->monsterStatusArray[ag->room]>=1) {printf("The %s is now at %dhp\n",ag->monsterArray[ag->room],ag->monsterStatusArray[ag->room]);}
    if (ag->monsterStatusArray[ag->room]==0 && ag->monsterFlag[ag->room]==0){//use a flag so that the kill message doesnt display more than one time
        printf("You killed the %s\n",ag->monsterArray[ag->room]);
        ag->monsterFlag[ag->room]=1;
    }
    if (ag->monsterStatusArray[ag->room]>=1) {//enemy fighting back dealing 2 damage if not dead after player hit
        ag->playerHP=ag->playerHP-2;
        if (ag->playerHP<0){ag->playerHP=0;}
        printf("The %s dealt 2 damage to you, you are now at %dhp\n",ag->monsterArray[ag->room],ag->playerHP);
    }
    return (mandatoryProcess(ag));//calling the process since need to check if player dies, return 0 if dies
}

int processKillZombie(adventureGame *ag){
    if (ag->room==2){
        if (ag->monsterStatusArray[ag->room]==0) {printf("The %s is already dead\n",ag->monsterArray[ag->room]);}
        if (ag->monsterStatusArray[ag->room]>=1) {
                ag->monsterStatusArray[ag->room]=ag->monsterStatusArray[ag->room]-ag->damageBase;
                if (ag->monsterStatusArray[ag->room]<0) {ag->monsterStatusArray[ag->room]=0;}
                printf("You dealt %d damage to the %s\n",ag->damageBase,ag->monsterArray[ag->room]);
            }

        if (ag->monsterStatusArray[ag->room]>=1) {printf("The %s is now at %dhp\n",ag->monsterArray[ag->room],ag->monsterStatusArray[ag->room]);}
        if (ag->monsterStatusArray[ag->room]==0 && ag->monsterFlag[ag->room]==0){//use a flag so that the kill message doesnt display more than one time
            printf("You killed the %s\n",ag->monsterArray[ag->room]);
            ag->monsterFlag[ag->room]=1;
        }
        if (ag->monsterStatusArray[ag->room]>=1) {//enemy fighting back dealing 2 damage if not dead after player hit
            ag->playerHP=ag->playerHP-2;
            if (ag->playerHP<0){ag->playerHP=0;}
            printf("The %s dealt 2 damage to you, you are now at %dhp\n",ag->monsterArray[ag->room],ag->playerHP);
        }
    }else {printf("There is no zombie here\n");}
    return (mandatoryProcess(ag));//calling the process since need to check if player dies, return 0 if dies
}

int processKillWerewolf(adventureGame *ag){
    if (ag->room==4){
        if (ag->monsterStatusArray[ag->room]==0) {printf("The %s is already dead\n",ag->monsterArray[ag->room]);}
        if (ag->monsterStatusArray[ag->room]>=1) {
                ag->monsterStatusArray[ag->room]=ag->monsterStatusArray[ag->room]-ag->damageWerewolf;
                if (ag->monsterStatusArray[ag->room]<0) {ag->monsterStatusArray[ag->room]=0;}
                printf("You dealt %d damage to the %s\n",ag->damageWerewolf,ag->monsterArray[ag->room]);
            }

        if (ag->monsterStatusArray[ag->room]>=1) {printf("The %s is now at %dhp\n",ag->monsterArray[ag->room],ag->monsterStatusArray[ag->room]);}
        if (ag->monsterStatusArray[ag->room]==0 && ag->monsterFlag[ag->room]==0){//use a flag so that the kill message doesnt display more than one time
            printf("You killed the %s\n",ag->monsterArray[ag->room]);
            ag->monsterFlag[ag->room]=1;
        }
        if (ag->monsterStatusArray[ag->room]>=1) {//enemy fighting back dealing 2 damage if not dead after player hit
            ag->playerHP=ag->playerHP-2;
            if (ag->playerHP<0){ag->playerHP=0;}
            printf("The %s dealt 2 damage to you, you are now at %dhp\n",ag->monsterArray[ag->room],ag->playerHP);
        }
    }else {printf("There is no werewolf here\n");}
    return (mandatoryProcess(ag));//calling the process since need to check if player dies, return 0 if dies
}

int processKillDragon(adventureGame *ag){
    if (ag->room==12){
        if (ag->monsterStatusArray[ag->room]==0) {printf("The %s is already dead\n",ag->monsterArray[ag->room]);}
        if (ag->monsterStatusArray[ag->room]>=1) {
                ag->monsterStatusArray[ag->room]=ag->monsterStatusArray[ag->room]-ag->damageBase;
                if (ag->monsterStatusArray[ag->room]<0) {ag->monsterStatusArray[ag->room]=0;}
                printf("You dealt %d damage to the %s\n",ag->damageBase,ag->monsterArray[ag->room]);
            }

        if (ag->monsterStatusArray[ag->room]>=1) {printf("The %s is now at %dhp\n",ag->monsterArray[ag->room],ag->monsterStatusArray[ag->room]);}
        if (ag->monsterStatusArray[ag->room]==0 && ag->monsterFlag[ag->room]==0){//use a flag so that the kill message doesnt display more than one time
            printf("You killed the %s\n",ag->monsterArray[ag->room]);
            ag->monsterFlag[ag->room]=1;
        }
        if (ag->monsterStatusArray[ag->room]>=1) {//enemy fighting back dealing 2 damage if not dead after player hit
            ag->playerHP=ag->playerHP-2;
            if (ag->playerHP<0){ag->playerHP=0;}
            printf("The %s dealt 2 damage to you, you are now at %dhp\n",ag->monsterArray[ag->room],ag->playerHP);
        }
    }else {printf("There is no dragon here\n");}
    return (mandatoryProcess(ag));//calling the process since need to check if player dies, return 0 if dies
}

void convertToLower(char *string){
    int i;
    for (i=0; string[i]!='\0';i++){
        if (string[i]>='A'&&string[i]<='Z')
            string[i]=string[i]-'A'+'a';
    }
}

int noArtPlayerCarrying(adventureGame ag){
    int i,N;
    for (i=0,N=0;i<ag.N_artifact;i++){
        if (ag.artifactLoc[i]==-1) N++;
    }
    return (N);
}

void convertToCap(char *string){
    int i,first;
    for (i=0,first=1;string[i]!='\0';i++){
        if (string[i]>='a' && string[i]<='z' && first==1){
            string[i]=string[i]+'A'-'a';
            first=0;
        }
        if ((string[i]>='A' && string[i]<='Z')|| (string[i]>='a' && string[i]<='z'))
            first=0;
        if (string[i]==' ')first=1;
    }
}

void printInventory(adventureGame ag) {
    int i,j;
    printf("You are carrying:\n");
    for (i=0,j=0;i<ag.N_artifact;i++){
        convertToCap(ag.artifact[i]);
        if (ag.artifactLoc[i]==-1)printf("%2d. %s\n",++j,ag.artifact[i]);
    }
    if (j==0) printf("Nothing\n");
}

int processGet(char *object, adventureGame *ag){
    int i;
    convertToLower(object);
    object[strcspn(object,"\n")]=0;
    for (i=0;i<ag->N_artifact;i++){
        convertToLower(ag->artifact[i]);
        if (strncmp(object,ag->artifact[i],strlen(ag->artifact[i]))==0){
            if (ag->artifactLoc[i]==ag->room) {
                if (noArtPlayerCarrying(*ag)<3) {
                    if(ag->artifactStatus[i]==1){//only able to pick up the artifact if corresponding status is 1 else means there is enemy stopping it
                        printf("You pick up the %s\n",object);
                        ag->artifactLoc[i]=-1;
                        mandatoryProcess(ag);
                        return(1);
                    }else {
                        printf("The %s is preventing you from picking up the %s,\n",ag->monsterArray[ag->room],ag->artifact[i]);
                        return (1);
                    }

                }else {
                printf("You are overloaded, you must drop another object first\n");
                printInventory(*ag);
                return(1);
                }
            }
        }
    }
    printf("There is no %s here\n",object);
    return (1);
}

int processDrop(char *object, adventureGame *ag){
    int i;
    convertToLower(object);
    object[strcspn(object,"\n")]=0;
    for (i=0;i<ag->N_artifact;i++){
        convertToLower(ag->artifact[i]);
        if (strncmp(object,ag->artifact[i],strlen(ag->artifact[i]))==0){
                if (ag->artifactLoc[i]==-1){
                    printf("You dropped the %s\n",object);
                    ag->artifactLoc[i]=ag->room;
                    mandatoryProcess(ag);
                    return(1);
                }
        }
    }printf("you have no %s to drop\n",object);
    return (1);
}

int processUnlock (adventureGame *ag){
    if (ag->room==4 || ag->room==11){//ensuring the player is next to a locked door
        if (ag->room==4){//check for correct room
            if (ag->artifactLoc[7]==-1){//check for correct key
                ag->room10Status[0]=1;//changing one of the status to 1 since there are two checks to enter the room
                ag->artifactLoc[7]=-2;//a location of -2 means the items is used
                printf("You unlocked the door to Room 10\n");
                mandatoryProcess(ag);
                return(1);
            }
            else{
                printf("You do not have the Bronze Key, unable to unlock door\n");
                return(1);
            }
        }
        if (ag->room==11){
            if (ag->artifactLoc[6]==-1){
                ag->moveToArray[11][2]=12;//changing the array value so it leads to the correct room
                ag->artifactLoc[6]=-2;
                printf("You unlocked the door to Room 13\n");
                return(1);
            }
            else{
                 printf("You do not have the Copper Key, unable to unlock door\n");
                 return(1);
            }
        }
    }
     else{
        printf("You are not next to a locked door, unable to unlock door\n");
        return(1);
     }
    return(1);
}

int processHeal(adventureGame *ag){
    if (strncmp(ag->command,"eat food\n",10)==0){//check for the correct command
        if (ag->artifactLoc[4]==-1){//check for item in player's inv
            ag->playerHP=ag->playerHP+5;
            if (ag->playerHP>ag->maxHP) {ag->playerHP=ag->maxHP;}//ensuring the health doesnt exceed maximum
            printf("You ate the food and recovered 5hp, you are now at %dhp\n",ag->playerHP);
            ag->artifactLoc[4]=-2;//item is used
        }
        else printf("You do not have food to eat\n");
    }
    if (strncmp(ag->command,"use medpack\n",13)==0){
        if (ag->artifactLoc[5]==-1){
                ag->playerHP=ag->playerHP+10;
            if (ag->playerHP>ag->maxHP) {ag->playerHP=ag->maxHP;}
            printf("You used the medpack and recovered 10hp, you are now at %dhp\n",ag->playerHP);
            ag->artifactLoc[5]=-2;
        }
        else printf("You do not have medpack to use\n");
    }
    if (strncmp(ag->command,"drink elixir\n",14)==0){
         if (ag->artifactLoc[8]==-1){
                ag->playerHP=ag->playerHP+10;
            if (ag->playerHP>ag->maxHP) {ag->playerHP=ag->maxHP;}
            printf("You drank the elixir and recovered 10hp, you are now at %dhp\n",ag->playerHP);
            ag->artifactLoc[8]=-2;
        }
        else printf("You do not have elixir to drink\n");
    }
    return (1);
}

int processHelp(){
    printf("Command List\n======================\n");
    printf("Movement Command: north/ n/ south/ s/ east/ e/ west/ w - move between rooms\n");
    printf("Look Command: look/ l - inspect room situation\n");
    printf("Fight Command: fight/ f/ killmonster/ killMonster/ km - fight the enemy in the room\n");
    printf("Alternate Fight Command: kill zombie/ kill werewolf/ kill dragon - alternate command used to fight the specific enemy ");
    printf("Get Command: get (object) - take the item in the room if there is and player item count is less than 3\n");
    printf("Drop Command: drop (object) - drop the selected object onto the current room\n");
    printf("Inventory Command: inventory/ i - list what the player is carrying\n");
    printf("Healing Command: eat food/ drink elixir/ use medpack - heal the player for an amount\n");
    printf("Unlocking Door: unlock door - unlocks the door if the player has the correct key and is next to the lock\n");
    printf("Exit game: exit/ quit - exit and end the game\n");
    printf("======================\n");
    return (1);
}

void processCalc(adventureGame *ag){//process for calculating and displaying xp at end of playthrough
    for (int i=0;i<=12;i++){//each enemy killed correspond to 2 xp
        if (ag->monsterStatusArray[i]==0){
            ag->XP=ag->XP+2;
        }
    }
    for (int j=0;j<=9;j++){// each item picked up or used correspond to 1 xp
        if (ag->artifactLoc[j]==-1 || ag->artifactLoc[j]==-2){
            ag->XP++;
        }
    }
    if (ag->winFlag==1){ag->XP=ag->XP+5;}// a wi flag that is only able to be changed by mandatoryprocess signifying a win, add 5 to xp
    printf("The XP/score for this run is %d\n",ag->XP);
}

int processCommand(adventureGame *ag) {
    printf("======================\n");
    // copying the last command to the current command if ntg is entered, reducing player load
    if (strncmp(ag->command,"\n",2)!=0) {strcpy(ag->buf,ag->command);}
    if (strncmp(ag->command,"\n",2)==0) {strcpy(ag->command,ag->buf);}
    // Handle the exit command.
    if (strncmp(ag->command,"exit\n",6)==0 || strncmp(ag->command,"quit\n",6)==0) {
        printf("You exit the game.\n");
        processCalc(ag);
        return(0);
    }
    // Process of other relevant commands, function calls in the format of return(function)
    // is due to the chance of the game ending at that command either due to winning or dying
    if (strncmp(ag->command,"look\n",6)==0 || strncmp(ag->command,"l\n",3)==0) {processLook(*ag); return(1);}
    if (strncmp(ag->command,"fight\n",7)==0 || strncmp(ag->command,"f\n",3 )==0 ||
        strncmp(ag->command,"killMonster\n",13)==0 || strncmp(ag->command,"km\n",4)==0 ||
        strncmp(ag->command,"killmonster\n",13)==0) {return (processKillMonster(ag)); return(1);}
    if (strncmp(ag->command,"kill zombie\n",13)==0) {return (processKillZombie(ag)); return(1);}
    if (strncmp(ag->command,"kill werewolf\n",15)==0) {return (processKillWerewolf(ag)); return(1);}
    if (strncmp(ag->command,"kill dragon\n",13)==0) {return (processKillDragon(ag)); return(1);}
    if (strncmp(ag->command,"get ",4)==0) {processGet(&ag->command[4],ag);return(1);}
    if (strncmp(ag->command,"inventory\n",11)==0 || strncmp(ag->command,"i\n",3)==0) {printInventory(*ag);return(1);}
    if (strncmp(ag->command,"drop ",5)==0) {processDrop(&ag->command[5],ag);return(1);}
    if (strncmp(ag->command,"unlock door\n",13)==0) {processUnlock(ag);return(1);}
    if (strncmp(ag->command,"eat food\n",10)==0) {processHeal(ag);return(1);}
    if (strncmp(ag->command,"use medpack\n",13)==0) {processHeal(ag);return(1);}
    if (strncmp(ag->command,"drink elixir\n",14)==0) {processHeal(ag);return(1);}
    if (strncmp(ag->command,"help\n",6)==0) {processHelp();return(1);}
    if (strncmp(ag->command,"north\n",7)==0 || strncmp(ag->command,"n\n",3)==0 || strncmp(ag->command,"south\n",7)==0 ||
        strncmp(ag->command,"s\n",3)==0 ||strncmp(ag->command,"east\n",6)==0 || strncmp(ag->command,"e\n",3)==0 ||
        strncmp(ag->command,"west\n",6)==0 || strncmp(ag->command,"w\n",3)==0) {return(processMovement(ag));return(1);}
    ag->command[strcspn(ag->command,"\n")]=0;
    printf("Unknown command: %s\n",ag->command);
    return(1);
}

void processStart(){//printing process for the start of the game put here to let the main file looks cleaner
    printf("======================\nWelcome to adventure game\n======================\n");
    printf("Your goal is to defeat the dragon in the Dragon's Den and get the golden chalice back to the Dungeon Entrance\n");
    printf("Be careful, there are other enemies, and items are scattered around the Dungeon for you to pick up\n");
    printf("The game ends when you either get the golden chalice back, or get killed\n");
    printf("Type \"help\" to get command list\n");
    printf("Take note that the program is case sensitive for your commands\n");
    printf("Good Luck!\n");
}
