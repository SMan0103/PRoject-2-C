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
<<<<<<< HEAD
    //stscanf("%s", *input);
    if (strcmp(input, "Sp") == 0) {
        //command1ShowCards();
=======
    //scanf("%s", *input);



    if (strcmp(input, "SW") == 0) {
        Display();
>>>>>>> 8f9a0b510b70d9d666a2c623083eae03c0a98e48

    } else if (strcmp(input, "Sh") == 0) {
        ShuffleCommand();

    } else if (strcmp(input, "St") == 0) {
        //command3Split();

    } else if (strcmp(input, "LD") == 0) {
        if(LDfalse == 0 ){
            LDfalse = 1;
            doesCardExists();
        } else {
            printf("Cammand alrig in place");
        }

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
    }else {
        moveCards(input);

    }
    setMessage(0);
    return 0;
}