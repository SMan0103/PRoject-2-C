#include <stdio.h>
#include <stdlib.h>

#include "Terminal.c"
#include "Flinkedstacks.h"



const int sz = 3;

typedef struct Node {
    int value;
    char name[2];
    int visible;
    struct Node* next;
} Node;


struct Node* columns[7];

void insertStart(struct Node **deck, const char *name) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->visible = 1;
    newNode->next = NULL;

    if(*deck == NULL)
        *deck = newNode;
    else{
        struct Node* lastNode = *deck;

        while(lastNode -> next != NULL){
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
        *Message = *fail;
    } else {
        *Message = *Ok;
    }
}

char *getMessage() {
    return Message;
}
int totalLinkedListArray[7];
int firstTimeRun = 0;
//Some help from chat with debug
struct Node **splitLinkedList() {
    int totalNodes = 0;

    if (firstTimeRun == 0){
        int firstpartListLenth[] = {1, 6, 7, 8, 9, 10, 11};
        for(int i = 0; i < 7; i++){
            totalLinkedListArray[i] = firstpartListLenth[i];
        }
        firstTimeRun += 1;
    }
    // Help from Lucas
    struct Node* nextCard = deck;
    struct Node* currentColumn = NULL;
    while (nextCard != NULL) {
        for (int i = 0; i < sizeof(totalLinkedListArray); i++) {
            currentColumn = columns[i];
            for (int j = 0; j < totalLinkedListArray[i]; j++) {
                if (currentColumn == NULL){
                    currentColumn = nextCard;
                } else {
                    currentColumn -> next = nextCard;
                    currentColumn = currentColumn->next;
                }
                nextCard = nextCard -> next;
            }
        }
    }
}

void LoadDisplay(struct Node *node) {
    int count = 0; // Count to keep track of the number of elements printed in a row
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    while (node != NULL) {
        count++;
        printf("\t[]");
        // If 7 elements have been printed, start a new line - This was help from ChatGPT
        if (count % 7 == 0)
            printf("\n");

        node = node->next;
    }
    printf("\n");
}

int doesCardExists() {
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
    LoadDisplay(deck);
    return 0; // Return success
}

// This function take a linked list a return its length.
int LinkedlistLength(struct Node *node) {
    int count;
    int tempCount = 0;
    while (node != NULL){
        tempCount += 1;
        node = node->next;
    }
    return tempCount;
}

// Assuming the Node structure and other necessary structures and functions are defined elsewhere - ChatGPT

void PrintSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf("\t");
    }
}

void setVisibility(){
    struct Node* nextCard = deck;
    for(int i = 0; i < 7; i++){
        int count = LinkedlistLength(columns[i]);
        for(int j = 1; j <= count - 5; j++) {
            if (nextCard != NULL) {
                nextCard->visible = 0;
                nextCard = nextCard->next;
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

        setVisibility();
        FirstLoadFalse = 1;
    }


    // Calculate lengths of sublists
    for (int t = 0; t < 7; t++) {
        totalLinkedListArray[t] = LinkedlistLength(columns);
    }

    // Find max height for loop

    for (int t = 0; t < 7; t++) {
        if (totalLinkedListArray[t] > maxHeight) {
            maxHeight = totalLinkedListArray[t];
        }
    }
    struct Node* nextCard = deck;
    // Print the cards
    for (int h = 0; h < maxHeight; h++) {
        for (int t = 0; t < 7; t++) {
            columns[t];
            int height = totalLinkedListArray[t];
            // If the current height is less than the number of nodes in the column
            if (h < height) {
                // Move to the card we want to print

                for (int k = 0; k < h; k++) {
                    nextCard = nextCard->next;
                }
                if (nextCard -> visible == 1){
                    printf("\t %s", nextCard->name);
                } else{
                    printf("\t []");
                }
            } else {
                PrintSpaces(1); // Print empty space
            }
        }
        printf("\n");
    }
}





void FindAndReplace(char inputOne[5]){
    struct Node **parts = splitLinkedList(deck);

    for (int j = 0; j < 7; j++) {
        struct Node *childNode = parts[j];
        while (childNode != NULL) {
            if (strcmp(childNode->name, inputOne) == 0) {
                strcpy(childNode->name, "DM");
            }
            childNode = childNode->next;
        }
        //totalLinkedListArray[i] = LinkedlistLength(childNode); // update with the new length
    }
}

int moveCards(char input[]){
    // Ensure the input is at least 6 characters long
    if (input[2] != '-' && input[2] != '>'){
        return 0;
    }


    if (strlen(input) < 6) {
        printf("Invalid input format.\n");
        return 0;
    }

    // Extract the first and second cards from the input string
    char firstCard[3] = {input[0], input[1], '\0'};
    char secCard[3] = {input[3], input[4], '\0'};

    // Call FindAndReplace with the first card
    FindAndReplace(firstCard);

    // Optionally, you can call FindAndReplace with the second card as well
    // FindAndReplace(secCard);

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