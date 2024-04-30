#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Shuffle.h"

typedef struct Cards {
    char *name;
    struct Cards *next;
} Cards;

Cards* createCard(char *name) {
    Cards *newCard = (Cards *)malloc(sizeof(Cards));
    newCard->name = strdup(name);
    newCard->next = NULL;
    return newCard;
}
void shuffleCards(Cards **head){
    int count = 0;
    Cards *current =*head;
    while (current !=NULL){
        count++;
        current = current -> next;
    }
    srand(time(NULL));

    for(int i=0; i < count * 2; i++){
        int index = rand() % count;
        int indey = rand() % count;

        Cards *node = *head;
        Cards *node1 = *head;

        for (int j = 0; j < index; j++)
            node = node -> next;
        for (int j = 0; j < indey; j++)
            node1 = node1 -> next;

        char *temp = node -> name;
        node -> name = node1 -> name;
        node1 -> name = temp;
    }
}

void saveListToFile(struct Cards *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }
    while (head != NULL) {
        fprintf(file, "%s\n", head->name);
        head = head->next;
    }

    fclose(file);
}


int ShuffleCommand() {

    FILE *file = fopen("C:\\Users\\PC\\Desktop\\CLionProjects\\PRoject-2-C\\Cards.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    char cardName[4];
    Cards *head = NULL;
    Cards *current = NULL;
    while (fscanf(file, "%s", cardName) == 1) {
        if (head == NULL) {
            head = createCard(cardName);
            current = head;
        } else {
            current->next = createCard(cardName);
            current = current->next;
        }
    }
    fclose(file);

    // Shuffle the linked list
    shuffleCards(&head);
    //Saving the shuffled cards
    saveListToFile(head, "C:\\Users\\PC\\Desktop\\CLionProjects\\PRoject-2-C\\Cards.txt");
    // Free memory
    //freeList(head);
}
//Memory leak problems

//void freeList(Cards *head) {
//  Cards *temp;
//while (head != NULL) {
//  temp = head;
//head = head->next;
//free(temp->name);
//free(temp);
//}
//}