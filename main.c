#include <stdio.h>
#include <stdlib.h>

#include "Terminal.c"
#include "Flinkedstacks.h"

#define ROWS 7

const int sz = 3;

struct Node {
    int value;
    char name[2];
    int visible;
    struct nodeStack *next;
};

void insertStart(struct Node **head, const char *name) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->visible = 1;
    newNode->next = NULL;

    if(*head == NULL)
        *head = newNode;
    else{
        struct Node* lastNode = *head;

        while(lastNode -> next != NULL){
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}
void hideCard(struct Node* node){
    node->visible = 0;
}
void visibleCard(struct Node* node){
    node->visible = 1;
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

//Some help from chat with debug
struct Node **splitLinkedList(struct Node *head) {
    int totalNodes = 0;
    struct Node **parts = (struct Node **) malloc(7 * sizeof(struct Node *));

    int extraNodes = totalNodes % 7;
    int totalLinkedListArray[] = {1, 6, 7, 8, 9, 10, 11};

    struct Node *current = head;
    for (int i = 0; i < 7; i++) {
        int nodesPerPart = totalLinkedListArray[i];
        parts[i] = current;
        int partSize = nodesPerPart + (extraNodes > 0 ? 1 : 0);
        for (int j = 1; j < partSize; j++) {
            current = current->next;
        }
        if (current != NULL) {
            struct Node *temp = current->next;
            current->next = NULL;
            current = temp;
        }
        extraNodes--;
    }

    return parts;
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
        insertStart(&head, str);
    }
    fclose(outStream);
    LoadDisplay(head);
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
//Some help from ChatGPT with the use of PrintSpaces and Calculate the MaxHeight
//The other section code is selfmade, that was used to promt ChatGPT
void Display() {
    struct Node *node = head;
    struct Node **parts = splitLinkedList(head);
    int countArray[7];

    // Calculate lengths of sublists
    for (int t = 0; t < 7; t++) {
        struct Node *childNode = parts[t];
        countArray[t] = LinkedlistLength(childNode);
    }

    // Find max height for loop
    int maxHeight = 0;
    for (int t = 0; t < 7; t++) {
        if (countArray[t] > maxHeight) {
            maxHeight = countArray[t];
        }
    }

    // Print the cards
    for (int h = 0; h < maxHeight; h++) {
        for (int t = 0; t < 7; t++) {
            struct Node *childNode = parts[t];
            int height = countArray[t];

            // If the current height is less than the number of nodes in the column
            if (h < height) {
                // Move to the card we want to print
                for (int k = 0; k < h; k++) {
                    childNode = childNode->next;
                }
                printf("\t %s", childNode->name);
            } else {
                PrintSpaces(1); // Print empty space
            }
        }
        printf("\n");
    }
}

// TODO If <Cards.txt>  is not provided: A new, shuffled deck is loaded by default, starting with all Clubs from A to K, followed by Diamonds, Hearts, and Spades in that order. In this case, the command simply returns OK.


// TODO Cards
// TODO Shuffle card
// TODO Split
// TODO Did read Command
// TODO Store last command
// TODO Get from linked list

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
    //freeLinkedList(head); // Free memory for the entire linked list

    return 0;
}