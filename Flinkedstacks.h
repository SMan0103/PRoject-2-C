//
// Created by Simon on 22-04-2024.
//
#ifndef Flinkedstacks.H
#define Flinkedstacks.H

struct F1Node {
    char F1name[2];
    struct F1Node *next;
};
struct F2Node {
    char F2name[2];
    struct F2Node *next;
};
struct F3Node {
    char F3name[2];
    struct F3Node *next;
};
struct F4Node {
    char F4name[2];
    struct F4Node *next;
};


void insertStartF1(struct F1Node **head, const char *name);
void insertStartF2(struct F2Node **head, const char *name);
void insertStartF3(struct F3Node **head, const char *name);
void insertStartF4(struct F4Node **head, const char *name);

#endif

