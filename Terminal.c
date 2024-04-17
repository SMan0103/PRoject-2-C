#include <stdio.h>
#include <string.h>
#include  "main.h"
#include "Shuffle.h"

//void command1ShowCards();
//void command2Shuffle();
//void command3Split();
int GameCommands(char input[]) {

    //printf("Enter a command (ShowCards, Shuffle, Split: ");
    //stscanf("%s", *input);
    if (strcmp(input, "Sp") == 0) {
        //command1ShowCards();

    } else if (strcmp(input, "Sh") == 0) {
        ShuffleCommand();

    } else if (strcmp(input, "St") == 0) {
        //command3Split();

    } else if (strcmp(input, "LD") == 0) {
        doesCardExists();

    } else if (strcmp(input, "ST") == 0) {
        exit(1);
    } else {
        printf("Invalid command\n");

    }
    setMessage(0);
    GameLoop(input);
    return 0;
}
