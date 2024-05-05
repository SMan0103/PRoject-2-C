#include <stdio.h>
#include <string.h>
#include  "main.h"
#include "Shuffle.h"

//void command1ShowCards();
//void command2Shuffle();
//void command3Split();
int LDfalse = 0;
int GameCommands(char input[]) {
    //printf("Enter a command (ShowCards, Shuffle, Split: ");
    //scanf("%s", *input);



    if (strcmp(input, "SW") == 0) {
        Display();

    } else if (strcmp(input, "SR") == 0) {
        ShuffleCommand();

    } else if (strcmp(input, "Sl") == 0) {
        splitDeck();
    } else if (strcmp(input, "LD") == 0) {

            doesCardExists();


    } else if (strcmp(input, "ST") == 0) {
        exit(1);
    } else if (strcmp(input, "P") == 0) {
        PlayLoop(input);
    } else {
        printf("Invalid Command");
    }

    setMessage(0);
    GameLoop(input);
    return 0;
}
int PlayCommands(char input[]){

    if (strcmp(input, "Q") == 0) {
        GameLoop();
    } else if (strcmp(input, "St") == 0) {
        splitDeck();

    } else {
        moveCards(input);

    }
    setMessage(0);
    return 0;
}