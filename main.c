#include <stdio.h>
#include <stdlib.h>

#include "Terminal.c"
#include "Flinkedstacks.c"

const int sz = 3;
const char *Filename = "C:\\Users\\Simon\\CLionProjects\\PRoject-2-C\\Cards.txt";
struct Node *head = NULL; // Initialize head to NULL - This was a debug from ChatGPT
struct F1Node *F1head = NULL;
struct F2Node *F2head = NULL;
struct F3Node *F3head = NULL;
struct F4Node *F4head = NULL;


struct Node {
    int value;
    char name[2];
    struct nodeStack *next;
};


void insertStart(struct Node **head, const char *name) {

    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));

    strcpy(newNode->name, name);
    newNode->next = *head;

    //changing the new head to this freshly entered node
    *head = newNode;
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

// Function to free memory recursively for the linked list - ChatGPT
// TODO Remake this
/*void freeLinkedList(struct nodeStack *head) {
    if (head == NULL) // Base case: if the list is empty
        return;

    // Recursively free memory for the rest of the list
    freeLinkedList(head->next);

    // Free memory for the current node
    free(head);
}*/

void LoadDisplay(struct Node *node) {
    int count = 0; // Count to keep track of the number of elements printed in a row
    int Fcount = 1; // Counter for F1, F2, F3, F4
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    while (node != NULL) {
        count++;
        printf("\t[]");

        if (count % 7 == 0) {
            printf("\t[] F%d\n", Fcount);
            Fcount++;
        }

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


void display() {
    struct Node *node = head;
    int count = 0; // Count to keep track of the number of elements printed in a row
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    while (node != NULL) {
        printf("\t%s", node->name);
        count++;

        // If 7 elements have been printed, start a new line - This was help from ChatGPT
        if (count % 7 == 0)
            printf("\n");

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
    struct Node *node = head;
    int rows = 8;
    int cols = 8;
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    // Loop for rows
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < i; j++) {
            printf("\t  ");
        }
        // Loop for columns
        for (int h = 0; h < cols - i; h++) {
            printf("\t%s", node->name);
            node = node->next;
        }
        printf("\n");

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
    insertStartF1(&F1head, "F1");
    insertStartF2(&F2head, "F2");
    insertStartF3(&F3head, "F3");
    insertStartF4(&F4head, "F4");

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