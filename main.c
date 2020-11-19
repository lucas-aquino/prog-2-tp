#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#include "funciones.h"

/** MAIN *************/
int main()
{
    int x, y;
    int frame;
    short key;

    clock_t start;

    //Las constantes SS_COL, SS_ROW estan definidas en "funciones.h"
    char display[SS_COL][SS_ROW];

    for(x = 0; x < SS_COL; x++)
    {
        for(y = 0; y < SS_ROW; y++)
        {
            display[x][y] = CH_BGD;
        }
    }


    frame = 0;

    while(1)
    {
        start = clock();

        if(kbhit())
        {
            key = getch();

            if(key == 0 || key == 224)
                key = getch() + 1000;

            if(key == 27)
                break;
        }


        printf("%3d\r", frame);

        frame++;


        while((clock() - start) <= T_REFRESH);
        system("cls");
    }

    return 0;
}
/*********************/


