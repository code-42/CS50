/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

void findLegitMoves(void);
// int legitMoves[d];

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                // Next line gets written to log.txt
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("\nTile to move: ");
        int tile = get_int();

        // Much like you automated input into find,
        // you can automate execution of this game.
        // In fact, in ~cs50/pset3 are 3x3.txt and 4x4.txt,
        // winning sequences of moves for a 3 × 3 board and
        // a 4 × 4 board, respectively. To test your program execute
        // ./fifteen 3 < ~cs50/pset3/3x3.txt
        // ./fifteen 4 < ~cs50/pset3/4x4.txt
        // printf("%d\n", tile);

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "tile %i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO the GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO
    // Calculate total number of tiles
    int nTiles = d * d;

    // Add tiles to board
    for (int r = 0; r < d; r++)
    {
        // printf("%dx%d board ", d, d);
        for (int c = 0; c < d; c++)
        {
            // Decrement value by one and assign to array
            board[r][c] = --nTiles;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO

    // Draw the board
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if(board[r][c] < 1)
            {
                printf("  ");
            }
            // Right-align numbers if < 10
            else if(board[r][c] < 10)
            {
                printf(" %i", board[r][c]);
            }
            else
            {
                printf("%i", board[r][c]);
            }
            if (c < d - 1)
            {
                printf("|");
            }
        }
        printf("\n");
    }

    // The positions of tiles numbered 1 and 2 should start off swapped
    // if the board has an odd number of tiles (ex. 4x4 board)
    // in other words, if d is even, for example: if(d % 2 == 0)
    // IMPORTANT: add this code snippet to init() also
    // if(d % 2 == 0)
    // {
    //     // Swap elements
    //     int temp = board[j];
    //     board[j] = board[j + 1];
    //     board[j + 1] = temp;
    // }

    // Draw the matrix for dev
    printf("\n");
    for (int r = 0; r < d; r++)
    {
        printf("%dx%d board ", d, d);
        for (int c = 0; c < d; c++)
        {
            printf("[%d,%d]", r, c);
        }
        printf("\n");
    }

    // Make modulo table
    printf("\n");
    for (int r = 0; r < d; r++)
    {
        printf("[%d mod %d] = %i\n",r, d, r%d);
        for (int c = 0; c < d; c++)
        {
            // printf("[%d mod %d] = %i\n",r, d, r%d);
        }
        // printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // TODO
    // Find tile row & col
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (board[r][c] == tile)
            {
                printf("Found tile %d @ element [%d,%d]",tile, r, c);
                // get_int();
                return true;
            }
        }
    }

    // Find the empty square
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (board[r][c] == 0)
            {
                printf("Found empty square [%d,%d]", r, c);
                // get_int();
                return true;
            }
        }
    }


    // Check 4 ways around blank to see what tiles can move
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            // Find edges of board
            if (r % d > 0)
            {
                printf("\nTop edge of board");
                // Row must be r or r+1
                printf("\nLegit move is row %d or %d", r, r + 1);
            }

            if ((r + 1) % d == 0)
            {
                printf("\nBottom edge of board");
                // Row must be r or r-1
                printf("\nLegit move is row %d or %d", r, r - 1);
            }

            if (c % d == 0)
            {
                printf("\nLeft edge of board");
                // Col must be c or c+1
                printf("\nLegit move is col %d or %d", c, c + 1);
            }

            if ((c + 1) % d == 0)
            {
                printf("\nRight edge of board");
                // Col must be c or c-1
                printf("\nLegit move is col %d or %d", c, c - 1);
            }
        }
    }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // TODO
    return false;
}
