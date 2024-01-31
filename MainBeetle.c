#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define boardSize 8

int board[boardSize][boardSize] = {0};

void input(short*, short*);     //Input validation
int  checksquares(void);        //Checks squares if beetle visited or not
void printBoard(void);          //Prints board to console
void printResult(int, int, int, int, int, int); //Prints the possibilities of moving directions.
void clearBoard(void);          //Cleans the console

int main(void)
{
    short i = 0, j = 0;
    int left = 0, right = 0, up = 0, down = 0, border = 0, allMoves = 0;
    clearBoard();

    // Ask user for initial positioning
    input(&i, &j); 
    srand(time(NULL));

    while (checksquares())
    {
        board[i][j]++;

        int moves = (rand() % 8) + 1;
        
        // This is to go up only
        if (moves == 1 && i > 0)
        {   
            i -= 1;
            up++;
        }
        // This is for up-right
        else if (moves == 2 && i > 0 && j < boardSize-1)
        {
            i -= 1, j += 1;
            right++;
            up++;
        }
        //This is for right
        else if (moves == 3 && j < boardSize-1)
        {
            j += 1;
            right++;
        }
        else if (moves == 4 && i < boardSize-1 && j < boardSize-1)
        {
            i += 1, j += 1;
            down++;
            right++;
        }
        else if (moves == 5 && i < boardSize-1)
        {
            i += 1;
            down++;
        }
        else if (moves == 6 && i < boardSize-1 && j > 0)
        {
            i += 1, j -= 1;
            down++;
            left++;
        }
        else if (moves == 7 && j > 0)
        {
            j -= 1;
            left++;
        }
        else if (moves == 8 && i > 0 && j > 0)
        {
            i -= 1, j -= 1;
            up++;
            left++;
        }
        else
        {
            border++;
        }
    }

    allMoves = left + right + up + down + border; 

    clearBoard();
    printBoard();
    printResult(left, right, up, down, border, allMoves);

    return 0;
}

void input(short *i, short *j)
{
    char c;
    printf("Enter i and j (i j): ");

    while (!(scanf("%hd %hd", i, j) == 2 && *i >= 0 && boardSize > *i && *j >= 0 && boardSize > *j))
    {
        printf("Invalid input.\nEnter i and j (i j): ");
        while ((c = getchar()) != '\n' && c != EOF); //It clears the console inputs.
    }
}

int checksquares(void)
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

void printBoard(void)
{
    printf("\n\t\t      ---- Beetle ----\n\n ");  

    for (int i = 0; i < boardSize; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (j==0)
                {
                    printf("   ______");
                }
                else
                {
                    printf(" ______");
                }
            }
            printf("\n");
        }

        for (int j = 0; j < boardSize; j++)
        {
            if (j == 0){printf("   |      |");}
            else 
            {
                printf("      |");
            }
        }
        printf("\n");

        // Now insert the statistics here / number of visits
        for (int j = 0; j < boardSize; j++)
        {
                if (j == 0)
                {
                    printf("%2d |  %2d  |",i , board[i][j]);
                }
                else
                {
                    printf("  %2d  |", board[i][j]);
                }
        }
        printf("\n");

        for (int j = 0; j < boardSize; j++)
        {
            if (j == 0)
            {
                printf("   |______|");
            }
            else
            {
                printf("______|");
            }
        }
        printf("\n");
    }
}

void printResult(int left, int right, int up, int down, int border, int allMoves)
{
    printf("\nNumber of all moves = %d\n\n", allMoves);

    printf("Probability of moving Right       : %d %%\n", 100 * right / allMoves);
    printf("Probability of moving Left        : %d %%\n", 100 * left / allMoves);
    printf("Probability of moving Up          : %d %%\n", 100 * up / allMoves);
    printf("Probability of moving Down        : %d %%\n", 100 * down / allMoves);
    printf("Probability of reaching the Border: %d %%\n", 100 * border / allMoves);
}

// Clear the screen before plotting the board
void clearBoard(void)
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}