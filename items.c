#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "items.h"

struct Item *addItem(struct Item **head, char *name)
{
    // create new Item
    struct Item *newItem = malloc(sizeof(struct Item));
    strcpy((char *)(newItem->name), name);
    newItem->next = NULL;

    // check if it is an empty list
    if (*head == NULL)
    {
        *head = newItem;
    }
    // find lastItem and add newItem
    else
    {
        struct Item *lastItem = *head;
        while (lastItem->next != NULL)
        {
            lastItem = lastItem->next;
        }
        lastItem->next = newItem;
    }
    return (*head);
}

// delete
struct Item *deleteItem(struct Item **head, char *name)
{
    struct Item *currItem = *head;
    struct Item *prevItem;
    while (currItem != NULL)
    {
        if (strcmp(currItem->name, name) == 0)
        {
            if (currItem == *head)
            {
                *head = currItem->next;
            }
            else
            {
                prevItem->next = currItem->next;
            }
            free(currItem);
            return (*head);
        }
        prevItem = currItem;
        currItem = currItem->next;
    }
    return (*head);
}

// print
void printItem(struct Item **head)
{
    struct Item *currItem = *head;
    while (currItem != NULL)
    {
        printf("%s\n", currItem->name);
        currItem = currItem->next;
    }
}

// check if item is in inventory/room (use helper function, scan from head to end and return 0 or 1 depending on strcmp())
int isIteminList(struct Item **head, char *name)
{
    struct Item *currItem = *head;
    while (currItem != NULL)
    {
        // found item
        if (strcmp(currItem->name, name) == 0)
            return 1;
        currItem = currItem->next;
    }
    // no item
    return 0;
}
