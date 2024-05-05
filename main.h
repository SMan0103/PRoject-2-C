//
// Created by steam on 10/04/2024.
//

//#ifndef UNTITLED1_MAIN_H
//#define UNTITLED1_MAIN_H

//#endif //UNTITLED1_MAIN_H

int doesCardExists(char inputFileName[50]);
void GameLoop();
void Display();
void displayAllCards();
struct Node *deck = NULL; // Initialize head to NULL - This was debug from ChatGPT
struct Node *deckInF = NULL;
const char *Filename = "../Cards.txt";
int fileChange = 0;
void PlayLoop();
void setMessage(int value);
int moveCards(char input[]);
void saveDeck(char input[]);