#include <stdio.h>
#include <string.h>

void command1ShowCards();
void command2Shuffle();
void command3Split();

int main(){
    char input[50];

    printf("Enter a command (ShowCards, Shuffle, Split: ");
    scanf("%s", input);
    if (strcmp(input, "ShowCards") == 0) {
        command1ShowCards();
    } else if (strcmp(input, "Shuffle") == 0) {
        command2Shuffle();
    } else if (strcmp(input, "Split") == 0) {
        command3Split();
    } else {
        printf("Invalid command\n");
    }

    return 0;
}
