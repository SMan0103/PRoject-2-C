#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h> // Include errno for perror


struct nodeStack{
    int value;
    char name[2];
    struct nodeStack *next;
};
// Function to free memory recursively for the linked list - ChatGPT
// TODO Remake this
void freeLinkedList(struct nodeStack *head) {
    if (head == NULL) // Base case: if the list is empty
        return;

    // Recursively free memory for the rest of the list
    freeLinkedList(head->next);

    // Free memory for the current node
    free(head);
}




int doesCardExists(const char *Filename) {
    FILE *outStream = fopen(Filename, "r");

    if (outStream != NULL) {
        // File exists and successfully opened
        printf("OK\n"); // Proper Error Message
        fclose(outStream);
        return 1; // Indicate that the file exists
    } else {
        // File does not exist or cannot be opened
        perror("Error opening file"); // Print system-specific error message
        return 0; // Indicate that the file does not exist
    }
}





// TODO If <Cards.txt>  is not provided: A new, unshuffled deck is loaded by default, starting with all Clubs from A to K, followed by Diamonds, Hearts, and Spades in that order. In this case, the command simply returns OK.


// TODO Cards
// TODO Shuffel card
// TODO Split
// TODO Did read Command
// TODO Store last command
// TODO Get from linked list

int GameLoop(const char *str2[2]) {
    const char *Filename = "C:\\Users\\steam\\CLionProjects\\untitled1\\Cards.txt";
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    printf("Last Command: ", str2);
    printf("\n Message:  \n");
    printf("Input > ");

    scanf("%s", str2);
    //TODO Make a try catch for length of string


    if (strcmp(str2,"LD") == 0){
        doesCardExists(Filename);
    }
    if (strcmp(str2, "STOP") == 0){
        return 0;
    }
    GameLoop(str2);
}




int main() {
    char *str1[2];
    const char *Filename = "C:\\Users\\steam\\CLionProjects\\untitled1\\Cards.txt";
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    printf("Last Command: \n");
    printf("Message: \n");
    printf("\n Input > ");

    scanf("%s", str1);
    //TODO Make a try catch for length of string


    if (strcmp(str1,"LD") == 0){
        doesCardExists(Filename);
    }
    if (strcmp(str1, "STOP") == 0){
        return 0;
    }
    GameLoop(str1);

    struct nodeStack *head = NULL;
    freeLinkedList(head); // Free memory for the entire linked list

    return 0;
}




