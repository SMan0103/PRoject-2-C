//
// Created by Simon on 22-04-2024.
//
#include "Flinkedstacks.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include  "main.h"


void insertStartF1(struct F1Node **F1head, const char *name) {

    struct F1Node *newNode = malloc(sizeof(struct F1Node));

    strcpy(newNode->F1name, name);
    newNode->next = *F1head;

    //changing the new head to this freshly entered node
    *F1head = newNode;
}
void insertStartF2(struct F2Node **F2head, const char *name) {

    struct F2Node *newNode = malloc(sizeof(struct F2Node));

    strcpy(newNode->F2name, name);
    newNode->next = *F2head;

    //changing the new head to this freshly entered node
    *F2head = newNode;
}
void insertStartF3(struct F3Node **F3head, const char *name) {

    struct F3Node *newNode = malloc(sizeof(struct F3Node));


    strcpy(newNode->F3name, name);
    newNode->next = *F3head;

    //changing the new head to this freshly entered node
    *F3head = newNode;
}
void insertStartF4(struct F4Node **F4head, const char *name) {

    struct F4Node *newNode = malloc(sizeof(struct F4Node));


    strcpy(newNode->F4name, name);
    newNode->next = *F4head;

    //changing the new head to this freshly entered node
    *F4head = newNode;
}