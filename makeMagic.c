///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        (name of file with main function)
// This File:        (name of this file)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           (your name)
// Email:            (your wisc email address)
// CS Login:         (your CS login name)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure that represents a magic square
typedef struct
{
    int size;      // dimension of the square
    int **msquare; // pointer to heap allocated magic square
} MSquare;

void fillRecur(int **board, int size, int n, int i, int j)
{
    n++;
    if (n > size * size)
    {
        printf("done\n");
        exit(1);
    }
    printf("found empty spot, filling now\n");
    *(*(board + i) + j) = n;
    int iNE = j;
    int jNE = i;
    int iB = i;

    //set y coordinate
    if (i == 0)
    {
        printf("wrapping around\n");
        iNE = size - 1;
    }
    else
    {
        iNE = i - 1;
    }
    //set x coordinate
    if (j == size - 1)
    {
        printf("wrapping around\n");
        jNE = 0;
    }
    else
    {
        jNE = j + 1;
    }
    //see if the NE is clear
    if (*(*(board + iNE) + jNE) == 0)
    {
        //recursively fill in the NE
        fillRecur(board, size, n, iNE, jNE);
    }
    //if the NE isnt clear
    else
    {
        //see if i needs to wrap
        if (i == size - 1)
        {
            printf("wrapping around");
            iB = 0;
        }
        else
        {
            iB = i + 1;
        }

        fillRecur(board, size, n, iB, j);
    }
}
void fill(int **board, int size)
{ //start with 1
    int n = 1;
    //start with the first row
    int i = 0;
    //get the middle of the board
    int j = size / 2;

    //set top middle to one
    *(*(board + i) + j) = n;
    //fill the next cell in the board
    fillRecur(board, size, n, i, j);
}

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize()
{
    printf("Enter magic square's size (odd integer >=3)\n");
    //create array to hold input
    char buffer[6];
    //get user input
    fgets(buffer, 6, stdin);
    //parse the integer from the buffer
    int number = atoi(buffer);
    //make sure size is greater than 3
    if (number < 3)
    {
        printf("Size must be >= 3.\n");
        exit(1);
    }
    //make sure size is even
    if (number % 2 != 1)
    {
        printf("Size must be odd.\n");
        exit(1);
    }
    return number;
}

/* TODO:
 * Makes a magic square of size n using the Siamese algorithm
 * and returns a pointer to the completed MSquare struct.
 *
 * n the number of rosw and columns
 */
MSquare *generateMSquare(int n)
{
    //TODO: Dynamically allocate a 2D array of dimensions retrieved above.
    int **square;
    square = malloc(n * sizeof(int *));
    if (square == NULL)
    {
        printf("Memory not allocated.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        *(square + i) = malloc(n * sizeof(int));
        if (*(square + i) == NULL)
        {
            printf("Memory not allocated.\n");
            exit(1);
        }
        else
        {
            printf("square: %d\n ", *(*(square + i)));
        }
    }

    //create the square struct
    MSquare Square = {n, square};
    //get a pointer to the square struct
    MSquare *squarePtr = &Square;
    //fill the board with numbers
    fill(squarePtr->msquare, squarePtr->size);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", *(*(square + i) + j));
        } /* code */
    }

    return squarePtr;
}

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * msquare the magic square to output
 * filename the name of the output file
 */
void outputMSquare(MSquare *msquare, char *filename)
{
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[])
{
    // TODO: Check input arguments to get output filename
    //make sure the correct number of arguments are entered
    if (argc != 2)
    {
        printf("Usage: ./makeMagic <output_filename>\n");
        exit(1);
    }
    // TODO: Get magin square's size from user
    int size = getSize();
    // TODO: Generate the magic square
    generateMSquare(size);
    // TODO: Output the magic square
    return 0;
}
