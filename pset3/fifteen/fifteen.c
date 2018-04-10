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
./
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
        printf("Board must be between %i x %i and %i x %i, inclusive.\n", DIM_MIN, DIM_MIN, DIM_MAX,
               DIM_MAX);  // style50 insisted on making spaces to line up DIM_MAX with "Board instead of tab
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
            printf("\nftw!\n");
            break;
            // return 0;
        }

        // prompt for move
        printf("\nTile to move: ");
        int tile = get_int();
        printf("%d", tile);

        usleep(500);

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
            printf("Illegal move.\n");
            usleep(1000000);
        }

        // sleep thread for animation's sake
        usleep(1000);
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
    usleep(200000);
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

    // If the board has an odd number of tiles (ex. 4x4 board)
    // the positions of tiles numbered 1 and 2 should start off swapped.
    // In other words, if d is even, for example: if(d % 2 == 0)
    if (d % 2 == 0)
    {
        // Loop through board to find tiles 1 and 2
        for (int r = 0; r < d; r++)
        {
            // printf("%dx%d board ", d, d);
            for (int c = 0; c < d; c++)
            {
                // Swap tiles
                if (r == d - 1 && board[r][c] == 2)
                {
                    board[r][c] = 1;
                    board[r][c + 1] = 2;
                    break;
                }
            }
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
    printf("\n");

    // Loop through board to find 0 tile
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            // Found 0 tile and make it blank
            if (board[r][c] < 1)
            {
                printf("  ");
            }
            // Right-align numbers if < 10
            else if (board[r][c] < 10)
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
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // TODO

    // Find row & col of blank
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            // Found blank tile
            if (board[r][c] == 0)
            {
                // Find element with tile number in it
                if (board[r + 1][c] == tile || board[r - 1][c] == tile || board[r][c + 1] == tile
                    || board[r][c - 1] == tile)
                {
                    // Find row & col of tile
                    for (int row = 0; row < d; row++)
                    {
                        for (int col = 0; col < d; col++)
                        {
                            if (board[row][col] == tile)
                            {
                                // Move tile out of its spot and set element equal 0
                                board[row][col] = 0;
                            }
                        }
                    }

                    // Now move the tile into the blank space
                    board[r][c] = tile;
                    usleep(500000);
                    return true;
                }
                return false;
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

    // Initialize counter
    int counter = 1;

    // Loop through the board
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            // The blank has to be last element on the board
            // So if a blank shows up while looping through the board
            // Don't even look any further
            if (board[row][col] != 0)
            {
                // If the element on the board is not greater than previous element
                // Then the elements are not in order
                // Thank you Zamalya for pointing that out to me
                // But I found a counter works better
                // Because Zamaylas way can stop early
                if (board[row][col] != counter)
                {
                    return false;
                }
            }
            // Increment counter for next loop
            counter++;
        }
    }
    // Looped all the way through and so you won!
    return true;
}
