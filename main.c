#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define LOWER 1
#define UPPER 100
#define MAX_CHANCE 10

// Function declarations
void game_intro();
bool choice();
void game_over(short int, short int);
void bye();

int main(void)
{
    short int chance, number, guess;
    do
    {
        game_intro();
        printf("\n\nAre you ready? [Y/N]: ");
        if (!choice()) // Enter choice
        {
            bye();
            return 0;
        }
        printf("\nOK, let's begin!");
        chance = MAX_CHANCE;
        srand(time(0));                                // Use current time as seed for the random generator
        number = rand() % (UPPER - LOWER + 1) + LOWER; // Generate random number
        while (chance)
        {
            do
            {
                printf("\n\nWhat is your guess?\n");
                scanf("%hd", &guess);
                if (guess < LOWER || guess > UPPER)
                    printf("\nHey, I didn't get that! Please enter a number within 1 and 100.");
            } while (guess < LOWER || guess > UPPER); // Check for invalid input
            /* Guessing game logic */
            if (guess != number)
            {
                printf("\n\nWhoops! Your guess is wrong.");
                if (guess < number)
                    printf("\nThe mystery number is greater than %hd. ", guess);
                else
                    printf("\nThe mystery number is lesser than %hd. ", guess);
                if (chance - 1 > 0)
                    printf("Try again!");
                printf("\nChances left: %hd", --chance);
            }
            else
            {
                game_over(chance, number);
                break;
            }
        }
        if (!chance)
            game_over(chance, number);
        printf("\n\nDo you want to play again? [Y/N]: ");
        fflush(stdin); // Flush the input stream buffer
    } while (choice()); // Enter choice and loop through
    bye();
    return 0;
}
void game_intro()
{
    printf("\n*******************************************************");
    printf("\n*                  GUESS THE NUMBER                   *");
    printf("\n*      The mystery number lies within 1 and 100       *");
    printf("\n*             You have to find the number             *");
    printf("\n*                  You got 10 chances                 *");
    printf("\n*******************************************************");
}
void game_over(short int chance, short int number)
{
    if (chance >= 7)
    {
        printf("\n\nHOORAY! YOU WERE EXCEPTIONAL!");
        printf("\nYou guessed the number correctly and took minimum chances.");
    }
    else if (chance >= 4)
    {
        printf("\n\nYOU DID IT! GOOD JOB!");
        printf("\nYou guessed the number correctly.");
    }
    else if (chance >= 1)
    {
        printf("\n\nYOU TOOK SOME TIME, BUT GOT IT RIGHT!");
        printf("\nYou need more practice.");
    }
    else
    {
        printf("\n\nGAME OVER!");
        printf("\nYou lost.");
        printf("\nThe number was %hd.", number);
    }
    printf("\n\nFinal score: %d", chance * 10);
}
bool choice()
{
    char ch;
    do
    {
        scanf("%c", &ch);
        ch = (char)toupper(ch);
        if (ch != 'Y' && ch != 'N')
            printf("\nPlease say Y (yes) or N (no): ");
        fflush(stdin);
    } while (ch != 'Y' && ch != 'N');
    if (ch == 'Y')
        return true;
    else
        return false;
}
void bye()
{
    printf("\nGoodbye!");
    printf("\n\n***** PRESS ANY KEY TO EXIT *****\n");
    getchar();
}