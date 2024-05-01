#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <dirent.h>
#include <SDL_image.h>
#include "Terminal.c"
//#include "Cards.c"

struct nodeStack{
    int value;
    char name[2];
    struct nodeStack *next;
};

char Message[7];
void setMessage(int value) {
    char Ok[5] = "OK";
    char fail[5] = "Fail";

    if (value == 0) {
        //Message = "Fail";
    } else {
        *Message = *Ok;
    }
}

char *getMessage(){
    return  Message;
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
        // TODO make a new deck that is sorted
        // TODO If <Cards.txt>  is not provided: A new, shuffled deck is loaded by default, starting with all Clubs from A to K, followed by Diamonds, Hearts, and Spades in that order. In this case, the command simply returns OK.
        setMessage(0);
        perror("Error opening file"); // Print system-specific error message
        return 0; // Indicate that the file does not exist
    }
}









// TODO Cards
// TODO Shuffle card
// TODO Split
// TODO Did read Command
// TODO Store last command
// TODO Get from linked list

void GameLoop(char str2[4]) {
    const char *Filename = "../Cards.txt";
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    for(int i = 0; i < 8; i++){
        printf("\t[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
    }


    printf("Last Command: %s",str2);
    printf("\n Message:  %s\n", getMessage());
    printf("Input > ");

    scanf("%s", str2);
    //TODO Make a try catch for length of string

    GameCommands(str2);
    GameLoop(str2);

}


// all gui propety of the cards
struct cardPropety{
    int x, y;
    int w, h;
};


struct card{
    int value;
    SDL_Rect cardPropety;

};


void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rect) {
    SDL_RenderCopy(renderer, texture, NULL, rect);
}
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename) {
    SDL_Surface* surface = SDL_LoadBMP(filename);
    if (!surface) {
        printf("Failed to load image %s: %s\n", filename, SDL_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Free the surface as it's no longer needed
    if (!texture) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}
void drawCard(SDL_Renderer* renderer, const SDL_Rect* cardPropety, SDL_Texture* cardTexture, int isFaceDown) {
    if (isFaceDown) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color for facedown cards
        SDL_RenderFillRect(renderer, cardPropety); // Draw a rectangle to represent facedown card
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, cardPropety); // Draw border for facedown card
    } else {
        if (cardTexture) { // Render the card texture if available
            SDL_RenderCopy(renderer, cardTexture, NULL, cardPropety);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Red color for other fields
            SDL_RenderFillRect(renderer, cardPropety);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, cardPropety);
        }
    }
}
// SUp for the cards
    void AddCardsToGUI(SDL_Renderer *renderer) {
    char filename[] = "C:\\Users\\Chris\\Desktop\\CLionProjects\\PRoject-2-C\\PlayingCards\\c01.bmp";


    SDL_Texture* cardTexture = loadTexture(renderer, filename);
        int startY = 25;
        int startX = 25;
        int cardW = 50;
        int cardH = 70;

        int stopFor = 0;

        int StartUpPhaseForCardPlacement[] = {1, 6, 7, 8, 9, 10, 11};

        SDL_Color redColor = {255, 0, 0, 255};
        SDL_Color blueColor = {0, 0, 255, 255};

        for (int j = 0; j < 7; j++) {
            int xOffSet = cardW + 10;
            for (int i = 0; i < StartUpPhaseForCardPlacement[j]; i++) {
                if (stopFor == 52) {
                    continue;
                }

                // Her skal der laves så der kan komme et nyt card ud.

                struct card cards;

                cards.cardPropety.x = startX + j * xOffSet;
                cards.cardPropety.y = startY + i * (cardH - 35);
                cards.cardPropety.w = cardW;
                cards.cardPropety.h = cardH;

                int Blue = (i >= StartUpPhaseForCardPlacement[j] - 5) ? 1 : 0;

                drawCard(renderer, &cards.cardPropety, (Blue ? cardTexture : NULL), 0);
                stopFor += 1;

            }

            xOffSet += 10;
        }

        for (int i = 0; i < 4; i++) {
            struct card cards;

            cards.cardPropety.x = startX + (cardW + 20) * 7;
            cards.cardPropety.y = startY + i * (cardH + 15);
            cards.cardPropety.w = cardW;
            cards.cardPropety.h = cardH;
            drawCard(renderer, &cards.cardPropety, cardTexture, 1);        }


    }


    int main(int argc, char *argv[]) {

        SDL_Window *window;
        SDL_Renderer *renderer;
        int quit = 0;
        SDL_Event event;

        int result = SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Test_1",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  800, 800,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL) goto CLEANUP_AND_QUIT;


        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) goto CLEANUP_AND_QUIT;
        while (!quit) {
            while (SDL_PollEvent(&event) != 0) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = 1;

                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 40, 0, 0);
            SDL_RenderClear(renderer);

            AddCardsToGUI(renderer);

            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        CLEANUP_AND_QUIT:
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();


        //const char *Filename = "C:\\Users\\steam\\CLionProjects\\untitled1\\Cards.txt";
        printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

        printf("Last Command: \n");
        printf("\n Message:  %s\n", getMessage());
        printf("\n Input > ");

        char str1[4];

        scanf("%s", str1);
        //TODO Make a try catch for length of string
        GameCommands(str1);

        GameLoop(str1);

        struct nodeStack *head = NULL;
        free(str1);
        freeLinkedList(head); // Free memory for the entire linked list

        return 0;
    }




