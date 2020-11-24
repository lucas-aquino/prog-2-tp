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
    int frame;
    short key;

    float sumaPromRender = 0;
    float promedioRender = 0;

    int cantidadProc = 5;
    int punteroProc  = 0;
    int contadorProc = 0;

    clock_t start;
    clock_t end;

    _Objeto player;

    _Proceso *cmdList;

    cmdList = (_Proceso *)malloc(sizeof(_Proceso) * cantidadProc);

    strcpy(cmdList[0].nombre, "ABA");
    cmdList[0].estado = PORHACER;
    cmdList[0].value  = 7;
    cmdList[0].cmd    = ABAJO;

    strcpy(cmdList[1].nombre, "IZQ");
    cmdList[1].estado = PORHACER;
    cmdList[1].value  = 7;
    cmdList[1].cmd    = IZQUIERDA;

    strcpy(cmdList[2].nombre, "ARR");
    cmdList[2].estado = PORHACER;
    cmdList[2].value  = 7;
    cmdList[2].cmd    = ARRIBA;

    strcpy(cmdList[3].nombre, "DER");
    cmdList[3].estado = PORHACER;
    cmdList[3].value  = 7;
    cmdList[3].cmd    = DERECHA;

    strcpy(cmdList[4].nombre, "ABA");
    cmdList[4].estado = PORHACER;
    cmdList[4].value  = 7;
    cmdList[4].cmd    = ABAJO;



    player.pos.x = 11;
    player.pos.y = 5;

    player.dir = ARRIBA;

    char display[SS_ROW][SS_COL];

    clearDisplay(display);

    frame = 0;

    while(1)
    {
        start = clock();
        end = clock();
        clearDisplay(display);

        if(kbhit())
        {
            key = getch();

            if(key == 0 || key == 224)
                key = getch() + 1000;

            if(key == 27)
                break;


            char cmd[16];
            int x,y;

            switch(key)
            {
            case KB_INCIO:
                gets(cmd);

                player.dir = ARRIBA;

                player.pos.y = y;
                player.pos.x = x;

                break;
            }
        }

        system("cls");


        if(cantidadProc > 0 && cmdList[punteroProc].estado == HACIENDO)
        {

            if(abs(cmdList[punteroProc].cmd) > 1)
            {
                player.dir = cmdList[punteroProc].cmd;
                player.pos.x += cmdList[punteroProc].cmd;
            }else
            {
                player.dir = cmdList[punteroProc].cmd;
                player.pos.y += cmdList[punteroProc].cmd;
            }
            contadorProc++;

            if(contadorProc >= cmdList[punteroProc].value )
            {
                cmdList[punteroProc].estado = HECHO;
                punteroProc++;
                cmdList[punteroProc].estado = HACIENDO;
                contadorProc = 0;
                cantidadProc--;
            }
        }


        ubicarPlayer(&player, display);

        displayMenu();
        refreshDisplay(display);

        printf("PLAYER POS: x%2d y%2d DIR:%2d\n", player.pos.x, player.pos.y, player.dir);
        puts("CMD\tESTADO\tVALUE");

        for(int i = 0; i < 5; i++)
        {
            printf("%-3s\t%-6d\t%-5d\n", cmdList[i].nombre, cmdList[i].estado, cmdList[i].value);
        }

        printf("\nFrame: %3d\n", frame);

        frame++;

        end = clock() - end;
        sumaPromRender += end;
        promedioRender = sumaPromRender / (float) frame;
        printf("Render: %3d ms\n", end);
        printf("Promedio: %3.1f ms\n", promedioRender);

        while((clock() - start) <= T_REFRESH);


    }

    return 0;
}
/*********************/


