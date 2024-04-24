#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "Terminal.c"


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
    const char *Filename = "Cards.txt";
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




int main(int argc, char* argv[]) {

    SDL_Window* window;
    SDL_Renderer* renderer;
    int quit = 0;
    SDL_Event event;

    int result = SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Test_1",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800, 600,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) goto CLEANUP_AND_QUIT;



    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if ( renderer == NULL) goto CLEANUP_AND_QUIT;
    while(!quit) {
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
    GameCommands( str1);

    GameLoop( str1);

    struct nodeStack *head = NULL;
    free(str1);
    freeLinkedList(head); // Free memory for the entire linked list

    return 0;
}




