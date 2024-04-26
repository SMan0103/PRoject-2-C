#include <stdio.h>
#include <stdlib.h>

#include "Terminal.c"
#include "Flinkedstacks.h"

const int sz = 3;

struct Node {
    int value;
    char name[2];
    struct nodeStack *next;
};

void insertStart(struct Node **head, const char *name) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
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
    // Read from file until EOF is reached
    while (fscanf(outStream, "%s", str) == 1) {
        insertStart(&head, str);
    }
    fclose(outStream);
    LoadDisplay(head);
    return 0; // Return success
}

void Display(struct Node *node) {
    while (node != NULL) {
        printf("\t%s", node->name);
        node = node->next;
    }
    printf("\n");
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
    struct Node **parts = splitLinkedList(head);
    for (int i = 0; i < 7; i++) {
        Display(parts[i]);
    }

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