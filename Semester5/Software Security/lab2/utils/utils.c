#include "utils.h"
#include <stdio.h>

#define CHARS_PER_LINE  16

void
PrintBuffer(
            char *Buffer,
            int Length
            )
{
    int i;
    char a[CHARS_PER_LINE+1];

    //
    a[CHARS_PER_LINE] = 0;

    for (i = 0; i < Length; i++)
    {
        char x = Buffer[i];

        if ((x >= 'a') && (x <= 'z') ||
            (x >= 'A') && (x <= 'Z') ||
            (x >= '0') && (x <= '9') )
        {
            a[i % CHARS_PER_LINE] = x;
        }
        else
        {
            a[i % CHARS_PER_LINE] = '.';    // Replace with '.' if non alpha characters might appear in buffer
        }

        printf("%0.2x ", (unsigned char)Buffer[i]);

        if (i % CHARS_PER_LINE == (CHARS_PER_LINE-1))
        {
            printf("| %s\n", a);
        }
        else 
        if (i == Length-1)
        {
            int j;
            for (j = (i+1) % CHARS_PER_LINE; j < CHARS_PER_LINE; j++)
            {
                printf("   ");
            }

            if ((i+1) % CHARS_PER_LINE != 0)
            {
                a[(i+1)%CHARS_PER_LINE] = 0;
                printf("| %s\n", a);
            }
        }

    }

    //printf("\n");
}
