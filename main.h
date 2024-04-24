//
// Created by steam on 10/04/2024.
//

//#ifndef UNTITLED1_MAIN_H
//#define UNTITLED1_MAIN_H

//#endif //UNTITLED1_MAIN_H

int doesCardExists(const char *Filename);
void GameLoop();
const char *Filename = "../Cards.txt";
void setMessage(int value);

SDL_Window* window;
SDL_Renderer* renderer;
