# clue_game

To compile the code, type the following into the terminal where the source code is located:
gcc -g adventure.c room.c items.c -o adventure
The output binary name is "adventure".

The structure of the room is defined as the following:
struct Room *rmArr[3][3] = {0};
In room.c, from lines 60-85, the 9 rooms are connected via pointers to the adjacent rooms. 
I also factor in the rooms on the edge, and set the null pointer accordingly.
"->" is used to connect the specific room in the 3x3 2D array to its neighboring rooms with the pre-defined struct North, South, East, West.
In other words, rmArr[i][j] is an array element, but the element itself is a pointer.
The rmArr array is a pointer array referring a struct member in via an pointer use "->".

In processCommand(), I use the C function scanf() to get the user's input. 
Then in the processCommand() function, I use a while loop to get additional information associated with this command.
Error tracking is also considered for invalid input.


