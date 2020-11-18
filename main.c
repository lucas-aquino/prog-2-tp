#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#include "funciones.h"

/** MAIN *************/
int main()
{
    int x, y;

    //Las constantes SS_COL, SS_ROW estan definidas en "funciones.h"
    char display[SS_COL][SS_ROW];

    for(x = 0; x < SS_COL; x++)
    {
        for(y = 0; y < SS_ROW; y++)
        {
            display[x][y] = CH_BGD;
        }
    }

    //refreshDisplay(display);

    int fHandler;
    int fSize;
    char *buffer;
    int firstParentesis;

    getFHandler(&fHandler, "algo.txt");

    fSize = lseek(fHandler, 0, SEEK_END);

    buffer = (char *)malloc(fSize);

    lseek(fHandler, 0, SEEK_SET);

    read(fHandler, buffer, fSize);

    buffer[fSize] = '\0';

    char *token;

    token = strtok(buffer, "()");

    while(token != NULL)
    {
        printf("%s  \n", token);

        token = strtok(NULL, "()");
    }

    close(fHandler);

    //short key;

    return 0;
}
/*********************/


