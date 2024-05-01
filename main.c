#include <stdio.h>
#include <stdlib.h>

#include "Terminal.c"
#include "Flinkedstacks.h"


const int sz = 3;

typedef struct Node {
    char name[3];
    int visible;
    int value;
    char FName[2];
    struct Node *next;
} Node;


struct Node *columns[7];
struct Node *fcolumns[4];

int ffirstTimeRun = 0;
int ftotalLinkedListArray[4];


void finsertStart(struct Node **fdeck, const char *name, int i) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->visible = 1;
    newNode->value = 0;
    char secCard[3];
    sprintf(secCard, "F%d", i);
    strcpy(newNode->FName, secCard);

    strcpy(newNode->FName, secCard);
    newNode->next = NULL;

    if (*fdeck == NULL)
        *fdeck = newNode;
    else {
        struct Node *lastNode = *fdeck;

        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }

}


struct Node **fInsertSplit() {
    if (ffirstTimeRun == 0) {
        int firstpartListLenth[] = {1, 1, 1, 1};
        for (int i = 0; i < 4; i++) {
            ftotalLinkedListArray[i] = firstpartListLenth[i];
        }
        ffirstTimeRun += 1;
    }

    struct Node *nextCardToF = deckInF;
    struct Node *currentFColumn = NULL;

    for (int i = 0; i < 4; i++) {
        currentFColumn = NULL;
        for (int j = 0; j < ftotalLinkedListArray[i]; j++) {
            if (currentFColumn == NULL) {
                fcolumns[i] = nextCardToF;
                currentFColumn = nextCardToF;
            } else {
                currentFColumn->next = nextCardToF;
                currentFColumn = currentFColumn->next;
            }
            nextCardToF = nextCardToF->next;
        }
        if (currentFColumn != NULL) {
            currentFColumn->next = NULL; // Disconnect the current segment from the rest
        }
    }

    return fcolumns;
}


void insertStart(struct Node **deck, const char *name) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->visible = 1;
    if(name[0] == 'A'){
        newNode->value = 1;
    } else if (name[0] == '2'){
        newNode->value = 2;
    } else if (name[0] == '3'){
        newNode->value = 3;
    } else if (name[0] == '4'){
        newNode->value = 4;
    } else if (name[0] == '5'){
        newNode->value = 5;
    } else if (name[0] == '6'){
        newNode->value = 6;
    } else if (name[0] == '7'){
        newNode->value = 7;
    } else if (name[0] == '8'){
        newNode->value = 8;
    } else if (name[0] == '9'){
        newNode->value = 9;
    } else if (name[0] == 'T'){
        newNode->value = 10;
    } else if (name[0] == 'J'){
        newNode->value = 11;
    } else if (name[0] == 'Q'){
        newNode->value = 12;
    } else if (name[0] == 'K'){
        newNode->value = 13;
    } else {
        newNode->value = 0;
    }
    newNode->next = NULL;

    if (*deck == NULL)
        *deck = newNode;
    else {
        struct Node *lastNode = *deck;

        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}

char Message[7];

void setMessage(int value) {
    char Ok[5] = "OK";
    char fail[5] = "Fail";

    if (value == 0) {
        strcpy(Message, Ok);
    } else {
        strcpy(Message, fail);
    }
}

char *getMessage() {
    return Message;
}

int totalLinkedListArray[7];
int totalLinkedListArrayOfF[4];
int firstTimeRun = 0;
//Some help from chat with debug


struct Node **splitLinkedList() {
    if (firstTimeRun == 0) {
        int firstpartListLenth[] = {1, 6, 7, 8, 9, 10, 11};
        for (int i = 0; i < 7; i++) {
            totalLinkedListArray[i] = firstpartListLenth[i];
        }
        firstTimeRun += 1;
    }

    struct Node *nextCard = deck;
    struct Node *currentColumn = NULL;

    for (int i = 0; i < 7; i++) {
        currentColumn = NULL;
        for (int j = 0; j < totalLinkedListArray[i]; j++) {
            if (currentColumn == NULL) {
                columns[i] = nextCard;
                currentColumn = nextCard;
            } else {
                currentColumn->next = nextCard;
                currentColumn = currentColumn->next;
            }
            nextCard = nextCard->next;
        }
        if (currentColumn != NULL) {
            currentColumn->next = NULL; // Disconnect the current segment from the rest
        }
    }

    return columns;
}

void LoadDisplay(struct Node *node) {
    int count = 0; // Count to keep track of the number of elements printed in a row
    int countFKeys = 0;
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    while (node != NULL) {
        count++;
        printf("\t[]");
        // If 7 elements have been printed, start a new line - This was help from ChatGPT
        if (count % 9 == 0)
            printf("\n");

        node = node->next;

    }

    printf("\n");
}

int doesCardExists(char inputFileName[50]) {

    //strcmp(*Filename, inputFileName)

    char str[sz];
    FILE *outStream = fopen(Filename, "r");

    if (outStream == NULL) {
        perror("Error opening file");
        return -1; // Return an error code
    }
    printf("OK\n");
    while (fscanf(outStream, "%s", str) == 1) {
        insertStart(&deck, str);
    }
    fclose(outStream);
    for (int i = 0; i < 4; i++) {
        finsertStart(&deckInF, "[]", i + 1);
    }
    LoadDisplay(deck);
    return 0; // Return success
}


// This function take a linked list a return its length.
int LinkedListLength(struct Node *head) {
    int count = 0;
    struct Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int LinkedListLengthOfF(struct Node *fcolumns) {
    int count = 0;
    struct Node *current = fcolumns;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


// Assuming the Node structure and other necessary structures and functions are defined elsewhere - ChatGPT

void PrintSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf("\t");
    }
}

void setVisibility() {
    for (int i = 0; i < 7; i++) {
        struct Node *current = columns[i];
        int count = LinkedListLength(columns[i]);
        for (int j = 1; j <= count - 5; j++) {
            if (current != NULL) {
                current->visible = 0;
                current = current->next;
            }
        }

    }
}


int FirstLoadFalse = 0;
int maxHeight = 0;

//Some help from ChatGPT with the use of PrintSpaces and Recalculated the MaxHeight
//The other section code is selfmade, that was used to promt ChatGPT
void Display() {

    if (FirstLoadFalse == 0) {
        splitLinkedList();
        fInsertSplit();
        setVisibility();
        FirstLoadFalse = 1;
    }
    // Calculate lengths of sublists
    for (int t = 0; t < 7; t++) {
        totalLinkedListArray[t] = LinkedListLength(columns[t]);
        if (t < 4) {
            totalLinkedListArrayOfF[t] = LinkedListLengthOfF(fcolumns[t]);
        }
    }

    // Find max height for loop
    for (int t = 0; t < 7; t++) {
        if (totalLinkedListArray[t] > maxHeight) {
            maxHeight = totalLinkedListArray[t];
        }
    }
    int countFKeys = 0;
    // Print the cards
    for (int h = 0; h < maxHeight || h < 7; h++) {
        for (int t = 0; t < 7; t++) {
            int height = totalLinkedListArray[t];
            // If the current height is less than the number of nodes in the column
            if (h < height) {
                // Move to the card we want to print
                struct Node *current = columns[t];
                for (int k = 0; k < h; k++) {
                    current = current->next;
                }
                if (current->visible == 1) {
                    printf("\t %s", current->name);
                } else {
                    printf("\t []");
                }
            } else {
                PrintSpaces(1); // Print empty space
            }
        }

        if (h % 2 == 0 && countFKeys < 4) {
            struct Node *fcurrent = fcolumns[countFKeys];
            while (fcurrent->next != NULL) {
                fcurrent = fcurrent->next;
            }
            printf("\t%s", fcurrent->name);
            printf("\t F%d", countFKeys + 1);
            countFKeys += 1;
        }
        printf("\n");
    }
}

//Debug help from ChatGPT
void FindCardAndMove(char inputOne[2], char inputSec[2]) {
    struct Node *destination;
    struct Node *fDestination;
    if (inputOne[1] == inputSec[1]){
        setMessage(0);
        return;
    }

    if (inputOne[0] == 'F') {
        for (int i = 0; i < 7; i++) {
            struct Node *Fcurrent = columns[i];
            struct Node *previous = NULL;

            while (Fcurrent != NULL) {
                if (strcmp(Fcurrent->FName, inputSec) == 0) {
                    // Card to move is found in current column
                    if (Fcurrent->visible == 0) {
                        setMessage(0);
                        return;
                    } else if (Fcurrent->next != NULL) {
                        setMessage(0);
                        return;
                    }
                    fDestination = Fcurrent;
                }
                Fcurrent = Fcurrent->next;
            }
        }
        for (int i = 0; i < 4; i++) {
            struct Node *current = fcolumns[i];
            struct Node *previous = NULL;

            while (current != NULL) {
                if (strcmp(current->name, inputOne) == 0) {
                    // Card to move is found in current column
                    struct Node *cardToMove = current;
                    if (current->visible == 0) {
                        return;
                    }
                    // Remove cardToMove from its current position
                    if (previous == NULL) {
                        columns[i] = current->next;
                    } else if (previous->visible == 0) {
                        previous->visible = 1;
                        previous->next = NULL;
                    } else {
                        previous->next = NULL;
                    }
                    if(destination->value-1 == cardToMove->value){
                        destination->next = cardToMove;
                    }
                    // Add cardToMove to the destination linked list
                    return;
                }
                previous = current;
                current = current->next;
            }

        }
        setMessage(0);
    } else if (inputSec[0] == 'F') {
        for (int i = 0; i < 4; i++) {
            struct Node *Fcurrent = fcolumns[i];
            struct Node *previous = NULL;

            while (Fcurrent != NULL) {
                if (strcmp(Fcurrent->FName, inputSec) == 0) {
                    // Card to move is found in current column
                    if (Fcurrent->visible == 0) {
                        return;
                    } else if (Fcurrent->next != NULL) {
                        return;
                    }
                    fDestination = Fcurrent;
                }
                Fcurrent = Fcurrent->next;
            }
        }
        for (int i = 0; i < 7; i++) {
            struct Node *current = columns[i];
            struct Node *previous = NULL;

            while (current != NULL) {
                if (strcmp(current->name, inputOne) == 0) {
                    // Card to move is found in current column
                    struct Node *cardToMove = current;
                    if (current->visible == 0) {
                        return;
                    }
                    // Remove cardToMove from its current position
                    if (previous == NULL) {
                        columns[i] = current->next;
                    } else if (previous->visible == 0) {
                        previous->visible = 1;
                        previous->next = NULL;
                    } else {
                        previous->next = NULL;
                    }

                    if(fDestination->value+1 == cardToMove->value){
                        fDestination->next = cardToMove;
                    }
                    return;
                }
                previous = current;
                current = current->next;
            }

        }

    } else {
        for (int i = 0;i < 7; i++) {
            struct Node *current = columns[i];
            struct Node *previous = NULL;

            while (current != NULL) {
                if (strcmp(current->name, inputSec) == 0) {
                    // Card to move is found in current column
                    if (current->visible == 0) {
                        return;
                    } else if (current->next != NULL) {
                        return;
                    }
                    destination = current;
                }
                current = current->next;
            }
        }
        for (int i = 0;i < 7; i++) {
            struct Node *current = columns[i];
            struct Node *previous = NULL;

            while (current != NULL) {
                if (strcmp(current->name, inputOne) == 0) {
                    // Card to move is found in current column
                    struct Node *cardToMove = current;
                    if (current->visible == 0) {
                        return;
                    }
                    if(destination->value-1 != cardToMove->value){
                        return;
                    }
                    // Remove cardToMove from its current position
                    if (previous == NULL) {
                        columns[i] = current->next;
                    } else if (previous->visible == 0) {
                        previous->visible = 1;
                        previous->next = NULL;
                    } else {
                        previous->next = NULL;
                    }

                    destination->next = cardToMove;

                    return;
                }
                previous = current;
                current = current->next;
            }
        }
    }
    printf("Card not found.\n");
}

int moveCards(char input[]) {
    // Ensure the input is at least 6 characters long
    int whereIsWaldow = 0;
    int countChar = 0;
    for (int i = 0; input[i] != 0; i++) {

        if (input[i] == '-') {
            whereIsWaldow = i;
        }
        countChar = i + 1;
    }
    if (whereIsWaldow == 0) {
        return 0;
    }
    if (input[whereIsWaldow] != '-' && input[whereIsWaldow + 1] != '>') {
        setMessage(0);
        return 0;
    }
    if (strlen(input) < 6) {
        printf("Invalid input format.\n");
        setMessage(0);
        return 0;
    }

    if (whereIsWaldow == 2 && countChar == 6) {
        char firstCard[3] = {input[0], input[1]};
        char secCard[3] = {input[4], input[5]};
        FindCardAndMove(firstCard, secCard);
    } else {
        return 0;
    }

    setMessage(1);
    return 0;
}







// TODO Split




void GameLoop(char str2[4]) {
    printf("Last Command: %s", str2);
    printf("\n Message:  %s\n", getMessage());
    printf("Input > ");


    scanf("%s", str2);
    //TODO Make a try catch for length of string

    GameCommands(str2);
    GameLoop(str2);

}


void PlayLoop(char str2[4]) {

    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    Display();


    printf("Last Command: %s", str2);
    printf("\n Message:  %s\n",

           getMessage()

    );
    printf("Input > ");


    scanf("%s", str2);
//TODO Make a try catch for length of string

    PlayCommands(str2);
    PlayLoop(str2);

}


int main() {
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    printf("Last Command: \n");
    printf("\n Message:  %s\n", getMessage());
    printf("\n Input > ");

    char str1[4];
    scanf("%s", str1);

    //TODO Make a try catch for length of string
    GameCommands(str1);

    GameLoop(str1);

    free(str1);
    //freeLinkedList(deck); // Free memory for the entire linked list

    return 0;
}