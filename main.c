/*
  
  ROTx 1.0

  ROTx is a C program that encrypts text using a customizable rotation-based 
  algorithm, similar to ROT13. Users input text and choose a rotation value ('x'), 
  shifting characters in the alphabet accordingly. This provides a quick and 
  customizable method for text encryption.

  Created 15 Jun 2023
  by Martin McCorkle

*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include </Header_Files/Error.h>
#include </Header_Files/TerminalColors.h>

#define MAX_NUM_OF_ARGS 2
#define MAX_ROTATION 25
#define MIN_ROTATION 1
#define CAP_START 65
#define CAP_STOP 90
#define LOW_START 97
#define LOW_STOP 122
#define MAX_ENCRYPTION_BYTES 1000

char main(__uint8_t argc, char *argv[]) {
    
    if (argc > MAX_NUM_OF_ARGS)
    {
        Return_Error("Too many arguments!", 1);
    }
    else if (argc <= 1)
    {
        Return_Error("Expecting an argument!", 1);
    }

    int x = atoi(argv[1]);

    if (x > MAX_ROTATION || x < MIN_ROTATION)
    {
        Return_Error("Not within bounds or NaN!", 1);
    }

    const char *source = "src.txt"; // Input file for encryption
	
	FILE *f1 = fopen(source, "r"); // Sets permission to read-only

    int c;
    int d[MAX_ENCRYPTION_BYTES] = {};
    int i = 0;

    if (f1 == NULL) // Checks if file exists
    {
		Return_Error("src.txt not found!", 1); 
    }
    else
    { 

        while (1)
        {
            c = 0;
            c = fgetc(f1); // Gets 1 character from 'f1' as an int

            if (c == EOF) 
            {
                    // printf("%sEOF%s\n", Kernel_RED, Kernel_WHITE);
                    break; // Checks for End Of File
            } 
            else if (c >= CAP_START && c <= CAP_STOP) 
            {
                goto shift; // Goto end if upper case
            }
            else if (c >= LOW_START && c <= LOW_STOP) 
            {
                c -= 32; // Makes upper case
            }
            else if (c < CAP_START || (c > CAP_STOP && c < LOW_START) || c > LOW_STOP) 
            {
                goto exclude; // Skips shift if a special character
            }

            shift:

            if (c > (CAP_STOP - x))
            {
                c -= 26; // Adjusts for overlap
            }
            
            c += x; // The final shift

            exclude:

            d[i] = c; // Adds characters to array
            ++i;

            if (i >= MAX_ENCRYPTION_BYTES)
            {
                Return_Error("src.txt contains too many characters (i > 1000)", 1);
            }


        }

    }

    printf("Encrypted Output (X=%d)\n", x);

    printf("%s%s'%ls'%s%s\n", Kernel_BACK_WHITE, Kernel_FORE_BLACK, d, Kernel_BACK_BLACK, Kernel_FORE_WHITE);

    return *d;

}

