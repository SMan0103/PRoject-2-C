//
// Created by steam on 10/04/2024.
//

//#ifndef UNTITLED1_MAIN_H
//#define UNTITLED1_MAIN_H

//#endif //UNTITLED1_MAIN_H

int doesCardExists();
void GameLoop();
void Display();
struct Node *deck = NULL; // Initialize head to NULL - This was debug from ChatGPT
const char *Filename = "../ShuffledCards.txt";
void PlayLoop();
void setMessage(int value);
int moveCards(char input[]);
int SplitShuffle();