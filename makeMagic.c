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

// Structure that represents a magic square
typedef struct
{
    int size;      // dimension of the square
    int **msquare; // pointer to heap allocated magic square
} MSquare;

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
    }
    MSquare Square = {n, square};
    MSquare *squarePtr = &Square;

    return squarePtr;
}
void fill(int **board)
{ //start with 1
    int n = 1;
    //start with the first row
    int i = 0;
    //get the middle of the board
    int j = sizeof(board) / 2;
    printf("%d:%d:%d", j, i, n);
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
