#include <stdio.h>
#include <stdlib.h>

#include "Terminal.c"


struct nodeStack{
    int value;
    char name[2];
    struct nodeStack *next;
};


void setMessage(int value) {
    if (value == 0){
        Message[] = "Fail";
    } else {
        Message[] =  "OK";
    }
}

char getMessage(){
    return Message[6];
}


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
        setMessage(1); // Proper Message
        fclose(outStream);
        return 1; // Indicate that the file exists
    } else {
        // File does not exist or cannot be opened
        perror("Error opening file"); // Print system-specific error message
        return 0; // Indicate that the file does not exist
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
    const char *Filename = "C:\\Users\\steam\\CLionProjects\\untitled1\\Cards.txt";
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    for(int i = 0; i < 8; i++){
        printf("\t[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
    }


    printf("Last Command: %s",str2);
    printf("\n Message:  %c %s", getMessage(), "\n");
    printf("Input > ");

    scanf("%s", str2);
    //TODO Make a try catch for length of string

    GameCommands(str2);
    GameLoop(str2);

}




int main() {
    const char *Filename = "C:\\Users\\steam\\CLionProjects\\untitled1\\Cards.txt";
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    printf("Last Command: \n");
    printf("\n Message:  %c %s", getMessage(), "\n");
    printf("\n Input > ");

    char str1[4];

    scanf("%s", str1);
    //TODO Make a try catch for length of string
    GameCommands( str1);

    GameLoop( str1);

    struct nodeStack *head = NULL;
    free(str1);
    freeLinkedList(head); // Free memory for the entire linked list

    return 0;
}




