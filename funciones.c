#include "funciones.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

/** FUNCIONES ********/

void refreshDisplay(char display[SS_COL][SS_ROW])
{
    int x, y;

    for(y = 0; y < SS_ROW; y++)
    {
        for(x = 0; x < SS_COL; x++)
        {
            printf("%c", display[x][y]);
        }
        printf("\n");
    }
}

void displayMenu()
{
    puts("Hola");
}

int getFHandler(int *fHandler, char *fPath)
{
    *fHandler = open(fPath, O_RDONLY | O_BINARY);

    if(*fHandler == -1)
        if(errno == ENOENT)
            return 0;


    return 1;
}

/*********************/

