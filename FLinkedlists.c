//
// Created by Simon on 22-04-2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

struct F1Node *F1head = NULL;
struct F2Node *F2head = NULL;
struct F3Node *F3head = NULL;
struct F4Node *F4head = NULL;

struct F1Node {
    char F1name[2];
    struct F1NodeStack *next;
};
struct F2Node {
    char F2name[2];
    struct F2NodeStack *next;
};
struct F3Node {
    char F3name[2];
    struct F3NodeStack *next;
};
struct F4Node {
    char F4name[2];
    struct F4NodeStack *next;
};
void insertStartF1(struct F1Node **head, const char *name) {

    struct F1Node *newNode = (struct F1Node *) malloc(sizeof(struct F1Node));

    strcpy(newNode->F1name, name);
    newNode->next = *head;

    //changing the new head to this freshly entered node
    *head = newNode;
}
void insertStartF2(struct F2Node **head, const char *name) {

    struct F1Node *newNode = (struct F2Node *) malloc(sizeof(struct F2Node));

    strcpy(newNode->F1name, name);
    newNode->next = *head;

    //changing the new head to this freshly entered node
    *head = newNode;
}
void insertStartF3(struct F3Node **head, const char *name) {

    struct F1Node *newNode = (struct F3Node *) malloc(sizeof(struct F3Node));

    strcpy(newNode->F1name, name);
    newNode->next = *head;

    //changing the new head to this freshly entered node
    *head = newNode;
}
void insertStartF4(struct F4Node **head, const char *name) {

    struct F1Node *newNode = (struct F4Node *) malloc(sizeof(struct F4Node));

    strcpy(newNode->F1name, name);
    newNode->next = *head;

    //changing the new head to this freshly entered node
    *head = newNode;
}