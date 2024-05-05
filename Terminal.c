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
        displayAllCards();




    } else if (strcmp(input, "Sh") == 0) {
            ShuffleCommand();
            fileChange = 1;

    } else if (strcmp(input, "St") == 0) {
        //command3Split();

    } else if (strcmp(input, "LD") == 0) {
        if(LDfalse == 0 ){
            LDfalse = 1;
            char inputFileName[50] = "../Cards.txt";

            doesCardExists(inputFileName);
        } else {
            printf("Command alrig in place");
        }

    } else if (strcmp(input, "QQ") == 0) {
        exit(1);
    } else if (strcmp(input, "P") == 0) {
        PlayLoop(input);
    } else if (input[0] == 'S' && input[1] == 'D') {
        saveDeck(input);

    } else {
        printf("Invalid Command");
        setMessage(0);
    }
    GameLoop(input);
    return 0;
}
int PlayCommands(char input[]){

    if (strcmp(input, "Q") == 0) {
        setMessage(1);
        GameLoop(input);
    } else {
        moveCards(input);
    }
    return 0;
}