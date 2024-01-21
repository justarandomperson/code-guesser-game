#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

enum difficulties {Easy = 1, Moderate, Hard, Crazy};
enum difficultyRounds {EasyRounds = 20, ModerateRounds = 15, HardRounds = 10, CrazyMinRounds = 5, CrazyMaxRounds = 25};

void welcomeRules();
void gameOverScreen();
void winScreen(int guesses);
int isInNumber(int number, int digit);
int checkPrintAccuracy(int guess);
int generateRandomNumber(int min, int max);
int generateRandomCode();
int getValidDifficulty();
int getValidGuess(int guesses);
int isValidGuess(int guess);
int calcGuesses(int difficulty);
bool askPlayAgain();

int code = 0;

int main()
{
    int guesses = 0,difficultyGuesses = 0, guess = 0, difficulty = 0, number = 0, guessesUsed = 0;
    bool won = false, playing = true;

    code = 0;
    srand(time(NULL));

    while (playing)
    {
        generateRandomCode();
        welcomeRules();

        difficulty = getValidDifficulty();
        difficultyGuesses = calcGuesses(difficulty);
        guesses = difficultyGuesses;

        while (guesses > 0 && !won)
        {   
            guess = getValidGuess(guesses);
            won = checkPrintAccuracy(guess);
            guesses--;
        }

        if (!won)
        {
            gameOverScreen();
        }
        else 
        {
            guessesUsed = difficultyGuesses - guesses;
            winScreen(guessesUsed);
        }

        playing = askPlayAgain();
    }
    return 0;
}

/*
function that gets a number and a digit. it iterates over the number and checks each digit 
if it's equal to the given digit
input: the number to search through, the digit to try to find
output: the spot index for the digit if it's found, else false.
*/
int isInNumber(int number, int digit)
{
    int spotIndex = 0;
    while(number!=0)
    {
        int ones = number%10;
        number/=10;
        spotIndex++; 

        if (ones == digit)
        {
            return spotIndex;
        }
    }

    return false;
}

/*
function that generates a random number between the provided range
input: minimum and maximum possible number to be generated
output: the randomly generated number
*/
int generateRandomNumber(int min, int max)
{
    int randNum = 0;
    randNum = rand() % (max - min + 1) + min;

    return randNum;
}

/*
function that generates a random number that has 4 digits, each one is a different number.
input: none
output: the randomly generated number
*/
int generateRandomCode()
{
    int digit = 0, length = 0;

    while (length<4)
    {
        digit = generateRandomNumber(1,6);
        if (!isInNumber(code, digit))
        {
            code+=digit;
            code*=10;
            length++;
        }
    }

    code/=10;

    return code;
}  

/*
function that prints a welcome message and the rules.
input: none
output: none
*/
void welcomeRules()
{
    printf("WELCOME TO \"CODE BREAKER\"!!!\n\n");
    printf("A secret password was chosen,\n");
    printf("Your mission is find out the secret password.\n\n");
    printf("The rules are as follows:\n");
    printf("1. In each round you try to guess the secret code (4 distinct digits)\n");
    printf("2. After every guess you'll receive two hints about the code\n");
    printf("   HITS:   The number of digits in your guess which were exactly right.\n");
    printf("   MISSES: The number of digits in your guess which belongs to\n");
    printf(" the password but were miss-placed.\n");
    printf("3. You'll lose if you fail to guess the password after a certain number of rounds\n");
}

/*
function that prints a game over screen.
input: none
output: none
*/
void gameOverScreen()
{
    printf("\n\n_______________________________________________________________________\n\n");
    printf(" _______  _______  __   __  _______    _______  __   __  _______  ______ \n");
    printf("|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  \n");
    printf("|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  \n");
    printf("|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ \n");
    printf("|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |\n");
    printf("|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |\n");
    printf("|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|\n");
    printf("\n\n_______________________________________________________________________\n\n");

    printf("You lost!\n");
    printf("The secret code was %d\n", code);
}

/*
function that prints a game win screen.
input: how many guesses the user used
output: none
*/
void winScreen(int guesses)
{
    printf("\n\n_______________________________________________________________________\n\n");
    printf(" __   __  _______  __   __    _     _  _______  __    _  __ \n");
    printf("|  | |  ||       ||  | |  |  | | _ | ||       ||  |  | ||  |\n");
    printf("|  |_|  ||   _   ||  | |  |  | || || ||   _   ||   |_| ||  |\n");
    printf("|       ||  | |  ||  |_|  |  |       ||  | |  ||       ||  |\n");
    printf("|_     _||  |_|  ||       |  |       ||  |_|  ||  _    ||__|\n");
    printf("  |   |  |       ||       |  |   _   ||       || | |   | __ \n");
    printf("  |___|  |_______||_______|  |__| |__||_______||_|  |__||__| \n");
    printf("\n\n_______________________________________________________________________\n\n");

    printf("It took you only %d guesses, you are a professional code breaker!\n", guesses);
}

/*
function that prints the game level options, and gets a valid choice from the user
input: none
output: the user's choice
*/
int getValidDifficulty()
{
    int choice = 0;
    printf("Please choose the game level:\n");
    printf("%d - Easy (%d rounds)\n", Easy, EasyRounds);
    printf("%d - Moderate (%d rounds)\n", Moderate, ModerateRounds);
    printf("%d - Hard (%d rounds)\n", Hard, HardRounds);
    printf("%d - Crazy (%d-%d rounds)\n", Crazy, CrazyMinRounds, CrazyMaxRounds);
    
    while (!(choice >= Easy && choice<= Crazy))
    {
        printf("Make a choice: ");
        scanf("%d", &choice);

    }

    return choice;
}

/*
function that prints the guess options and guesses left, and gets a valid guess from the user
input: none
output: the user's guess
*/
int getValidGuess(int guesses)
{
    int guess = 0, digit = 0;
    bool validGuess = false;
    while (!validGuess)
    {
        printf("Write your guess (Only 1-6, 4 distinct digits, no ENTER is needed)\n");
        printf("%d guesses left\n", guesses);

        guess = 0;
        for (int i =1; i<=4; i++)
        {
            digit = getch();
            guess+=digit-'0'; //converts ascii code of number to the actual number
            guess*=10;
            printf("%c", digit);
        }
        printf("\n");
        guess/=10;
        
        validGuess = isValidGuess(guess);

        if (!validGuess)
        {
            printf("Only 1-6 and no double numbers are allowed, try again!\n");
        }
    }

    return guess;
}

/*
function that calculates how many rounds the users get for the difficulty chosen
input: none
output: the amount of guesses
*/
int calcGuesses(int difficulty) 
{
    int guesses = 0;

    switch (difficulty)
    {
        case Easy:
            guesses = EasyRounds;
            break;
        case Moderate:
            guesses = ModerateRounds;
            break;
        case Hard:
            guesses = HardRounds;
            break;
        case Crazy:
            guesses = generateRandomNumber(CrazyMinRounds, CrazyMaxRounds);
            break;        
    }

    return guesses;
}

/*
function that checks if the guess is valid (each digit is from 1 to 6, no same digit twice)
input: none
output: true if the guess is valid, false if not
*/
int isValidGuess(int guess)
{
    int digits = 0, digit = 0;

    while (guess!=0)
    {
        
        digit = guess%10;
        guess/=10;

        if (isInNumber(digits, digit) || digit < 1 || digit > 6) 
        {
            return false;
        }

        digits+=digit;
        digits*=10;
    }
    return true;
}

/*
function that checks and prints how many numbers were right and how many numbers belong to the password, 
but in the wrong place
input: the user's guess
output: true if the hits is 4, false if it isn't
*/
int checkPrintAccuracy(int guess)
{
    int spot_index = 0, digit = 0, hits = 0, misses = 0, inNumber = 0;

    while (guess!=0)
    {
        digit = guess%10;
        guess/=10;
        spot_index++;

        inNumber = isInNumber(code, digit);

        if (inNumber) 
        {
            if (inNumber == spot_index) 
            {
                hits++;
            }
            else
            {
                misses++;
            }
        }
    }

    if (hits == 4)
    {
        printf("You got      %d HITS       YOU WON!!!\n\n",hits,misses);
    }
    else 
    {
        printf("You got      %d HITS       %d MISSES.\n",hits,misses);
    }

    

    return hits==4;
}

/*
function that asks the user if they want to play again as long as the answer is not valid.
input: none
output: true if the answer is 'y', false if 'n'.
*/
bool askPlayAgain()
{
    char ans = ' ';
    bool valid = false;

    while (!valid)
    {
        printf("Would you like to play again? (y/n): ");
        ans = getch();
        printf("%c\n", ans);

        valid = ans == 'y' || ans == 'n';
    }

    return ans == 'y';
}