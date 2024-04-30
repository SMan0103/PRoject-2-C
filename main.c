#include <stdio.h>
#include <stdlib.h>

#include "Terminal.c"
#include "Flinkedstacks.h"



const int sz = 3;

typedef struct Node {
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


struct Node** splitLinkedList() {
    if (firstTimeRun == 0){
        int firstpartListLenth[] = {1, 6, 7, 8, 9, 10, 11};
        for(int i = 0; i < 7; i++){
            totalLinkedListArray[i] = firstpartListLenth[i];
        }
        firstTimeRun += 1;
    }

    struct Node* nextCard = deck;
    struct Node* currentColumn = NULL;

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
int LinkedListLength(struct Node* head) {
    int count = 0;
    struct Node* current = head;
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

void setVisibility(){
    for(int i = 0; i < 7; i++){
        struct Node* current = columns[i];
        int count = LinkedListLength(columns[i]);
        for(int j = 1; j <= count - 5; j++) {
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
        setVisibility();
        FirstLoadFalse = 1;
    }
    // Calculate lengths of sublists
    for (int t = 0; t < 7; t++) {
        totalLinkedListArray[t] = LinkedListLength(columns[t]);
    }

    // Find max height for loop
    for (int t = 0; t < 7; t++) {
        if (totalLinkedListArray[t] > maxHeight) {
            maxHeight = totalLinkedListArray[t];
        }
    }

    // Print the cards
    for (int h = 0; h < maxHeight; h++) {
        for (int t = 0; t < 7; t++) {
            int height = totalLinkedListArray[t];
            // If the current height is less than the number of nodes in the column
            if (h < height) {
                // Move to the card we want to print
                struct Node* current = columns[t];
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
        printf("\n");
    }
}
void DeleteCard(int position){
    Node* temp;
    Node* prev;
    temp = deck;
    prev = deck;
    for (int i = 0; i < position; i++) {
        if (i == 0 && position == 1) {
            *deck = (*deck)->next;
            free(temp);
        }
        else {
            if (i == position - 1 && temp) {
                prev->next = temp->next;
                free(temp);
            }
            else {
                prev = temp;

                // Position was greater than
                // number of nodes in the list
                if (prev == NULL)
                    break;
                temp = temp->next;
            }
        }
    }

}
void FindAndReplace(char inputOne[5], char inputSec[5]){
    for(int i = 0; i < 7; i++){
        struct Node* current = columns[i];
        int count = LinkedListLength(columns[i]);
        for(int j = 0; j < count; j++) {
            if (current != NULL) {
                if (strcmp(current->name, inputSec) == 0) {
                    int hej = 0;
                    while (hej == 0){
                        for(int g = 0; g < 7; g++){
                            struct Node* current2 = columns[g];
                            int count = LinkedListLength(columns[g]);
                            for(int Banna= 0; Banna < count; Banna++) {
                                if (current2 != NULL) {
                                    if (strcmp(current2->name, inputOne) == 0) {
                                        DeleteCard(i,j,g,Banna);
                                        return;

                                        hej = 1;
                                    } else{
                                        current2 = current2->next;
                                    }

                                }
                            }
                        }
                    }
                } else{
                    current = current->next;
                }
            }
        }
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
    char secCard[3] = {input[4], input[5], '\0'};

    // Call FindAndReplace with the first card
    FindAndReplace(firstCard, secCard);

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