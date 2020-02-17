///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:       n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           Robinson Cook
// Email:            rcook5@wisc.edu
// CS Login:         robinson
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
/**
 * print to the file
 * @param square the square being printed to
 * @param size the size of the square
 * @param squareFile the file being written to
*/
void printSquare(int **square, int size, FILE *squareFile)
{
    //print the size to the file
    fprintf(squareFile, "%d\n", size);

    //iterate through rows
    for (int i = 0; i < size; i++)
    {
        //iterate through row indices
        for (int j = 0; j < size; j++)
        {
            //see if not end of row
            if (j != size - 1)
            {
                //print with a comma
                fprintf(squareFile, "%d,", *(*(square + i) + j));
            }
            //if end of row
            else
            {
                //print without a comma
                fprintf(squareFile, "%d", *(*(square + i) + j));
            }
        }
        //print a new line
        fprintf(squareFile, "\n");
    }
}
/**
 * recursively fill the square
 * @param square the square you are filling
 * @param size the size of the square
 * @param n the number that was filled last
 * @param i the row being filled
 * @param j the column being filled
 * 
*/
void fillRecur(int **square, int size, int n, int i, int j)
{
    //incriment the number that is going to fill in
    n++;
    //see if the program has filled in all squares
    if (n > size * size)
    {
        //stop filling
        return;
    }
    //fill in the square
    *(*(square + i) + j) = n;
    //set the NE and below to the current indices
    int iNE = j;
    int jNE = i;
    int iB = i;

    //set y coordinate
    //see if on the top row
    if (i == 0)
    {
        //wrap around to the bottom row
        iNE = size - 1;
    }
    //if not on the top row
    else
    {
        //set next i to be up one row
        iNE = i - 1;
    }
    //set x coordinate
    //see if on the rightmost side
    if (j == size - 1)
    {
        //wrap around to the left side
        jNE = 0;
    }
    //if not on the rightmost side
    else
    {
        //set next j to be one to the right
        jNE = j + 1;
    }
    //see if the NE is clear
    if (*(*(square + iNE) + jNE) == 0)
    {
        //recursively fill in the NE
        fillRecur(square, size, n, iNE, jNE);
    }
    //if the NE isnt clear
    else
    { //handle below coordinate
        //see if i is the bottom row
        if (i == size - 1)
        {
            //wrap around to the top row
            iB = 0;
        }
        //if i isn't at the bottom row
        else
        {
            //the next i will be one below the current i
            iB = i + 1;
        }
        //recursively fill in the square below
        fillRecur(square, size, n, iB, j);
    }
}
/**
 * start filling the square
 * @param square the square you are filling
 * @param size the size of the square
*/
void fill(int **square, int size)
{ //start with 1
    int n = 0;
    //start with the first row
    int i = 0;
    //get the middle of the square
    int j = size / 2;
    //fill the next cell in the square
    fillRecur(square, size, n, i, j);
}

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize()
{
    printf("Enter magic square's size (odd integer >=3)\n");
    //array to hold input
    char *buffer = malloc(6 * sizeof(char));
    if (buffer == NULL)
    {
        printf("Memory not allocated.\n");
        exit(1);
    }
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
    //the magic square being filled in
    int **square;
    //allocate memory to hold rows
    square = malloc(n * sizeof(int *));
    if (square == NULL)
    {
        printf("Memory not allocated.\n");
        exit(1);
    }
    //allocate memory for each row
    for (int i = 0; i < n; i++)
    {
        *(square + i) = malloc(n * sizeof(int));
        if (*(square + i) == NULL)
        {
            printf("Memory not allocated.\n");
            exit(1);
        }
    }

    //create the square struct
    MSquare Square = {n, square};
    //get a pointer to the square struct
    MSquare *squarePtr = &Square;
    //fill the square with numbers
    fill(squarePtr->msquare, squarePtr->size);

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
    //open the file
    FILE *squareFile = fopen(filename, "w");
    if (squareFile == NULL)
    {
        printf("file not opened\b");
        exit(1);
    }
    //write square to the file
    printSquare(msquare->msquare, msquare->size, squareFile);
    //close the file
    if (fclose(squareFile) != 0)
    {
        printf("Error while closing the file.\n");
        exit(1);
    }
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
    MSquare *msquare = generateMSquare(size);
    // TODO: Output the magic square
    outputMSquare(msquare, *(argv + 1));
    //free memory

    int **square = msquare->msquare;
    for (int i = 0; i < size; i++)
    {
        free(*(square + i));
    }
    free(square);

    return 0;
}
