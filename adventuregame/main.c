#include "lab2.h"

//this is a program that runs an adventure game
//please read the report before trying out the game as there are some changes made to the base of the game that is discussed in the report

int main()
{
    adventureGame ag={
        //global variables that are to used by the program
        .room=0,
        .lookArray={
                    "You are in the Dungeon Entrance,\nYou can go south to the Hidden Room,\nor go east to a Empty Hallway.",
                    "You are in a Empty Hallway,\nYou can go east to the Prisoners's Cells,\nor go west to the Dungeon Entrance.",
                    "You are in the Prisoners's Cells,\nYou can go south to the Central Hall,\nor go east to the Lookout Tower,\nor go west to a Empty Hallway.",
                    "You are in the Lookout Tower,\nYou can go south to the Potions' Storage,\nor go east to the Warden's Office,\nor go west to the Prisoners's Cells.",
                    "You are in the Warden's Office,\nYou can go south to the Courtyard if you have a Bronze Key and kill the Werewolf,\nor go west to the Lookout Tower.",
                    "You are in the Hidden Room,\nYou can go north to the Dungeon Entrance.",
                    "You are in the Dracula's Bedroom,\nYou can go south to the Bride's Bedroom,\nor go east to the Central Hall.",
                    "you are in the Central Hall,\nYou can go north to the Prisoners's Cells,\nor go south to the Den's Entrance,\nor go east to the Potions' Storage,\nor go west to the Dracula's Bedroom.",
                    "you are in the Potions' Storage,\nYou can go north to the Lookout Tower,\nor go west to the Central Hall.",
                    "You are in the Courtyard,\nYou can go north to the Warden's Office.",
                    "You are in the Bride's Bedroom,\nYou can go north to the Dracula's Bedroom,\nor go east to the Den's Entrance.",
                    "You are in the Den's Entrance,\nYou can go north to the Central Hall,\nor go east to the Dragon's Den if you have a Copper Key,\nor go west to the Bride's Bedroom.",
                    "You are in the Dragon's Den,\nYou can go west to the Den's Entrance."
                    },
        .moveArray={// direction that is a wall has no text since the program will never need those text
                    {"","You go south to the Hidden Room","You go east to a Empty Hallway",""},
                    {"","","You go east to the Prisoners's Cells","You go west to the Dungeon Entrance."},
                    {"","You go south to the Central Hall.","You go east to the Lookout Tower.","You go west to a Empty Hallway."},
                    {"","You go south to the Potions' Storage.","You go east to the Warden's Office.","You go west to the Prisoners's Cells."},
                    {"","You go south to the Courtyard.","",""},
                    {"You go north to the Dungeon Entrance.","","",""},
                    {"","You go south to the Bride's Bedroom.","You go east to the Central Hall.",""},
                    {"You go north to the Prisoners's Cells.","You go south to the Den's Entrance.","You go east to the Potions' Storage.","You go west to the Dracula's Bedroom."},
                    {"You go north to the Lookout Tower.","","","You go west to the Central Hall."},
                    {"You go north to the Warden's Office.","","",""},
                    {"You go north to the Dracula's Bedroom.","","You go east to the Den's Entrance.",""},
                    {"You go north to the Central Hall.","","You go east to the Dragon's Den.","You go west to the Bride's Bedroom."},
                    {"","","","You go east to the Den's Entrance."},
                    },
        .moveToArray={
                    {-1,5,1,-1},
                    {-1,-1,2,0},
                    {-1,7,3,1},
                    {-1,8,4,2},
                    {-1,-1,-1,3},
                    {0,-1,-1,-1},
                    {-1,10,7,-1},
                    {2,11,8,6},
                    {3,-1,-1,7},
                    {4,-1,-1,-1},
                    {6,-1,11,-1},
                    {7,-1,-1,10},
                    {-1,-1,-1,11}
                    },
        .monsterArray={"","","Zombie","","Werewolf","Monster","Dracula","","","Lizard-man","Bride of Dracula","","Dragon"},
        .monsterStatusArray={-1,-1,5,-1,12,4,12,-1,-1,5,7,-1,12},
        .monsterFlag={0,0,0,0,0,0,0,0,0,0,0,0,0},
        .damageBase=2,
        .damageVampire=2,
        .damageWerewolf=2,
        .N_artifact=9,
        .artifact={"Sword","Golden chalice","Diamond Cross","Silver Spear","Food","Medpack","Copper Key","Bronze Key","Elixir"},
        .artifactLoc={5,12,9,11,1,3,6,7,8},
        .artifactStatus={1,0,0,1,1,1,0,1,1},
        .room10Status={0,0},
        .playerHP=12,
        .maxHP=20,
        .XP=0,
        .winFlag=0,
    };
    //a function that prints the start of the game
    processStart();
    while (fgets(ag.command,1000,stdin)) {//Read a command-line from the user
        if (processCommand(&ag)==0) break;
    }


    return 0;
}
