#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "items.h"
#include "room.h"

//LL of the avatar's inventory/backpack
struct Item *inventory = NULL;

//strings that hold the answers to the clue game
char targetRoom[32] = "";
char targetItem[32] = "";
char targetCharacter[32] = "";

//current room character is in
struct Room *currRoom = NULL;

// randomly pick room, item, character as the answer
int randomGen(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

//generates random game answer for every game run
void genCurrentRmAndGameAnswer()
{
    currRoom = rmArr[rand() % 3][rand() % 3];

    int targetRoomNum = randomGen(0, 8);
    int targetItemNum = randomGen(0, 5);
    int targetCharacNum = randomGen(0, 4);
    strcpy((char *)&targetRoom, realRoom[targetRoomNum].name);
    strcpy((char *)&targetItem, realRoom[targetItemNum].itemList->name);
    strcpy((char *)&targetCharacter, realRoom[targetCharacNum].character[0]);
}

//main function that processes user input and checks win condition
void processCommand()
{
    //winning status (sets to 1 if all three target match with user's)
    int winningStatus = 0;
    //counts guesses (if >10 user loses)
    int numGuesses = 0;

    while (winningStatus == 0 && numGuesses < 10)
    {
        printf("Type your command: ");
        char currUserInput[256];
        scanf("%s", currUserInput); // when to use &

        // help
        if (strcmp(currUserInput, "help") == 0)
        {
            printf("The commands are as follows:\nhelp: look-up all commands in the table\n");
            printf("list: look-up list of items, rooms and characters\n");
            printf("look: allows your avatar to see what room they are in, the rooms in each direction, the characters in the room, and the items in the room\n");
            printf("go: prompts you to type which direction (north, south, east, west) you would like to go\n");
            printf("take: allows your avatar to pick up an item and place it into the inventory\n");
            printf("drop: prompts you to type an item name and allows your avatar to drop that item\n");
            printf("inventory: allows your avatar to check items in avatar's inventory\n");
            printf("clue: prompts you to make a guess! Type the suspect's name, and if the room and item also match, you win.\n");
        }
        // list
        else if (strcmp(currUserInput, "list") == 0)
        {
            printf("The items, rooms, and characters are listed (all case sensitive):\n");
            printf("The items are: Red-Scarf, Crowbar, Chess-Board, Ricin, and Notebook.\n");
            printf("The rooms are: Seattle, Los-Angeles, Boston, New-York-City, Chicago, Houston, Portlan, and Mianmi. \n");
            printf("The characters are: Eren-Jeager, Joker, Meruem, Walter-White, and Light.\n");
        }
        // look
        else if (strcmp(currUserInput, "look") == 0)
        {
            // room
            printf("The current room you are in is %s.\n", currRoom->name);
            // rooms adjacent
            printf("The adjacent rooms are the following:\n");
            if (currRoom->North != NULL)
            {
                printf("north\n");
            }
            if (currRoom->East != NULL)
            {
                printf("east\n");
            }
            if (currRoom->South != NULL)
            {
                printf("south\n");
            }
            if (currRoom->West != NULL)
            {
                printf("west\n");
            }
            // characters in the room
            printf("The characters in the room are the following:\n");
            for (int i = 0; i < MAX_CHARACTER; i++)
            {
                if (currRoom->character[i] != NULL)
                    printf("%s\n", currRoom->character[i]);
            }
            // items in the room
            printf("The items in the room are the following:\n");
            printItem(&(currRoom->itemList));
        }
        // go
        else if (strcmp(currUserInput, "go") == 0)
        {
            char inputDirection[255];
            printf("Which direction would you like to move? Pick from north, south, east, or west (case-sensitive).\n");
            while (1)
            { // forces player to make a move (pick a direction)
                scanf("%s", inputDirection);
                if (strcmp(inputDirection, "north") == 0 && currRoom->North != NULL)
                {
                    printf("You moved up to the north room.\n");
                    currRoom = currRoom->North;
                    break;
                }
                else if (strcmp(inputDirection, "south") == 0 && currRoom->South != NULL)
                {
                    printf("You moved down to the south room.\n");
                    currRoom = currRoom->South;
                    break;
                }
                else if (strcmp(inputDirection, "east") == 0 && currRoom->East != NULL)
                {
                    printf("You moved right to the east room.\n");
                    currRoom = currRoom->East;
                    break;
                }
                else if (strcmp(inputDirection, "west") == 0 && currRoom->West != NULL)
                {
                    printf("You moved left to the west room.\n");
                    currRoom = currRoom->West;
                    break;
                }
                else
                { // non-existing room OR invalid input
                    printf("Non-existing room or invalid input. ");
                    printf("Try again. Which direction would you like to move? Pick from north, south, east, or west (case-sensitive).\n");
                }
            }
        }
        // take
        else if (strcmp(currUserInput, "take") == 0)
        {
            if (currRoom->itemList == NULL)
            {
                printf("No item exists in the room, cannot use \"take\" command.\n");
                continue;
            }
            char item[255];
            printf("Type the item you want to take (case-sensitive).\n");
            scanf("%s", item);
            while (isIteminList(&(currRoom->itemList), item) == 0)
            {
                printf("No item named %s in the room.\n", item);
                printf("Please try taking item again. The following items exist in the room: ");
                // use & when referencing pointer of the pointer (itemList is a pointer value)
                printItem(&(currRoom->itemList));
                scanf("%s", item);
            }
            addItem(&inventory, item);
            deleteItem(&(currRoom->itemList), item);
            printf("Successfully taken item.\n");
        }
        // drop
        else if (strcmp(currUserInput, "drop") == 0)
        {
            if (inventory == NULL)
            {
                printf("Your inventory does not have that item, cannot use \"drop\" command.\n");
                continue;
            }
            char item[255];
            printf("Type the item you want to drop (case-sensitive).\n");
            scanf("%s", item);
            while (isIteminList(&(inventory), item) == 0)
            {
                printf("No item named %s exists in your inventory.\n", item);
                printf("Please try dropping item again. The following items exist in your backpack: ");
                printItem(&(inventory));
                scanf("%s", item);
            }
            deleteItem(&inventory, item);
            addItem(&(currRoom->itemList), item);
            printf("Successfully dropped item.\n");
        }
        // inventory
        else if (strcmp(currUserInput, "inventory") == 0)
        {
            printf("Here is the list of items:\n");
            printItem(&inventory);
        }
        // clue
        else if (strcmp(currUserInput, "clue") == 0)
        {
            char inputName[256];
            int roomMatch = 0;
            int characterMatch = 0;
            int itemMatch = 0;
            
            //checks if character name is valid, if not, reprompt user for valid suspect name
            const char *characterList[5];
            characterList[0] = "Eren-Jeager";
            characterList[1] = "Joker";
            characterList[2] = "Meruem";
            characterList[3] = "Walter-White";
            characterList[4] = "Light";
            int flag = 0;
            while(1)
            {
                printf("Please type suspect character's name (case sensitive):\n");
                scanf("%s", inputName);
               for (int k = 0; k < 5; k++)
               {
                   if (strcmp(inputName, characterList[k]) != 0)
                   {
                       continue;
                   }
                   else
                   {
                       flag = 1;
                       break;
                   }
               }
               if (flag == 0)
               {
                   printf("Invalid character input. Please re-input valid character name.\n");
               }
               else
               { //flag == 1
                   break;
               }
            }

            // find which room the accused is in
            int i;
            // initialize currCharacter to 0 to avoid invalid memory access
            int currCharacter = 0;
            int found = 0;
            for (int i = 0; i < 9 && found == 0; i++)
            {
                currCharacter = 0;
                while ((realRoom[i].character[currCharacter] != NULL) && (found == 0) && (currCharacter < MAX_CHARACTER))
                {
                    if (strcmp(inputName, realRoom[i].character[currCharacter]) != 0)
                    {
                        currCharacter++;
                    }
                    else
                    {
                        // add character to currRoom
                        for (int j = 0; j < MAX_CHARACTER && found == 0; j++)
                        {
                            // empty spot in character array found, add to currRoom
                            if (currRoom->character[j] == NULL)
                            {
                                currRoom->character[j] = realRoom[i].character[currCharacter];
                                realRoom[i].character[currCharacter] = NULL;
                                found = 1;
                            }
                        }
                    }
                }
            }
            // check if inputName is equal to targetCharacter
            for (int i = 0; i < MAX_CHARACTER; i++)
            {
                if ((currRoom->character[i] != NULL) && (strcmp(currRoom->character[i], targetCharacter) == 0))
                {
                    printf("Character Match.\n");
                    characterMatch = 1;
                }
            }
            if (characterMatch == 0)
            {
                printf("Character doesn't match.\n");
            }

            // check roomMatch
            if (strcmp(currRoom->name, targetRoom) == 0)
            {
                printf("Room Match.\n");
                roomMatch = 1;
            }
            else
            {
                printf("Room doesn't match.\n");
            }

            // check itemMatch
            if (isIteminList(&(currRoom->itemList), targetItem) || isIteminList(&(inventory), targetItem))
            {
                printf("Item Match.\n");
                itemMatch = 1;
            }
            else
            {
                printf("There are no items in the room or in the inventory that match.\n");
            }

            if (itemMatch == 1 && characterMatch == 1 && roomMatch == 1)
            {
                winningStatus = 1;
                numGuesses++;
                break;
            }
            numGuesses++;
            printf("You now have %d total guesses.\n", numGuesses);
        }
        // invalid command
        else
        {
            printf("Invalid command, try again. Type "
                   "help"
                   " for all valid commands.\n");
        }
    }

    // win condition
    if (numGuesses == 10 && winningStatus == 0)
    {
        printf("Sorry, all ten "
               "clue"
               " guesses have been used. You lose!\n");
    }
    // win condition not met
    else
    {
        printf("Congrats, you found the suspect, room, and item used! You win!\n");
        printf("It took you only %d guesses to find the suspect %s, using item %s, and in room %s!\n", numGuesses, targetCharacter, targetItem, targetRoom);
    }
}

//main function constructs rooms, processes user input
int main(void)
{
    srand(time(0));
    generateRooms();
    genCurrentRmAndGameAnswer();
    processCommand();
}
