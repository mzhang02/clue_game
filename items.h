#ifndef ITEMS_H
#define ITEMS_H
struct Item
{
      char name[255];
      struct Item *next;
};

//prints Item names starting from **head of LL to the end
//head is the head of the LL
void printItem(struct Item **head);

//deletes Item with specific passed in name
//returns head of LL
//head is the head of the LL
//name is the name of the Item to be deleted
struct Item *deleteItem(struct Item **head, char *name);

//adds Item with specific passed in name to the end of the LL
//returns head of LL
//head is the head of the LL
//name is the name of the Item to be added
struct Item *addItem(struct Item **head, char *name);

//looks for Item specific passed in name
//returns 1 if found, 0 otherwise
//head is the head of the LL
//name is the name of the Item that is being searched for
int isIteminList(struct Item **head, char *name);
#endif // ITEMS_H
