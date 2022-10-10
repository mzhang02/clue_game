#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"

// 0 out the memory for the rmArr, initialize it {0}
struct Room *rmArr[3][3] = {0};

// declare real room and zero out memory region
struct Room realRoom[9] = {0};

void generateRooms()
{
    realRoom[0].name = "Seattle";
    realRoom[1].name = "Amherst";
    realRoom[2].name = "Los-Angeles";
    realRoom[3].name = "Boston";
    realRoom[4].name = "New-York-City";
    realRoom[5].name = "Chicago";
    realRoom[6].name = "Houston";
    realRoom[7].name = "Portland";
    realRoom[8].name = "Miami";

    // allocate and use memory in LL, 6 items
    realRoom[0].itemList = malloc(sizeof(struct Item));
    strcpy(realRoom[0].itemList->name, "Red-Scarf");
    realRoom[0].itemList->next = NULL;
    realRoom[1].itemList = malloc(sizeof(struct Item));
    strcpy(realRoom[1].itemList->name, "Crowbar");
    realRoom[1].itemList->next = NULL;
    realRoom[2].itemList = malloc(sizeof(struct Item));
    strcpy(realRoom[2].itemList->name, "Chess-Board");
    realRoom[2].itemList->next = NULL;
    realRoom[3].itemList = malloc(sizeof(struct Item));
    strcpy(realRoom[3].itemList->name, "Ricin");
    realRoom[3].itemList->next = NULL;
    realRoom[4].itemList = malloc(sizeof(struct Item));
    strcpy(realRoom[4].itemList->name, "Notebook");
    realRoom[4].itemList->next = NULL;
    realRoom[5].itemList = malloc(sizeof(struct Item));
    strcpy(realRoom[5].itemList->name, "Pillow");
    realRoom[5].itemList->next = NULL;

    //5 characters
    realRoom[0].character[0] = "Eren-Jeager";
    realRoom[1].character[0] = "Joker";
    realRoom[2].character[0] = "Meruem";
    realRoom[3].character[0] = "Walter-White";
    realRoom[4].character[0] = "Light";

    // your game must randomly initialize the location of each room in the game board before the game starts
    for (int i = 0; i < 9; i++)
    {
        int randVal = 0;
        do
        {
            randVal = rand() % 9;
        } while (rmArr[randVal / 3][randVal % 3] != NULL);
        {
            rmArr[randVal / 3][randVal % 3] = &(realRoom[i]);
        }
    }

    // creating the 3x3 room
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == 0)
                // rmArr[i][j] is an array element, but the element
                // itself is a point. so rmArr array is a pointer array
                // referring a struct member in via an pointer use "->"
                rmArr[i][j]->North = NULL;
            else
                rmArr[i][j]->North = rmArr[i - 1][j];
            if (i == 2)
                rmArr[i][j]->South = NULL;
            else
                rmArr[i][j]->South = rmArr[i + 1][j];
            if (j == 0)
                rmArr[i][j]->West = NULL;
            else
                rmArr[i][j]->West = rmArr[i][j - 1];
            if (j == 2)
                rmArr[i][j]->East = NULL;
            else
                rmArr[i][j]->East = rmArr[i][j + 1];
        }
    }
}
