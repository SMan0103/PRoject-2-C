#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>


SDL_Event event;

struct cardPropety{
    int x, y;
    int w, h;
};

struct cardColorFuckDig{

};
struct card{
    int value;
    SDL_Rect cardPropety;
    //SDL_Texture cardColorFuckDig;

};
void drawCard(SDL_Renderer* renderer, const SDL_Rect* cardPropety) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, cardPropety);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, cardPropety);
}
void AddCardsToGUI(){

    int startY = 150;
    int startX = 150;
    int cardW = 50;
    int cardH = 70;

    for (int j = 0; j < 4;  j++){
        for(int i = 0; i < 13; i++){
            // Her skal der laves så der kan komme et nyt card ud.
                struct card cards;

                cards.cardPropety.x = startX + i * (cardW + 5);
                cards.cardPropety.y = startY + j * (cardH + 5);
                cards.cardPropety.w = cardW;
                cards.cardPropety.h = cardH;
            drawCard(renderer,&cards.cardPropety);


        }
    }

}







