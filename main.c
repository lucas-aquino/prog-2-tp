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
    clock_t start;
    clock_t end;

    short key;
    int frame = 0;

    float sumaPromRender = 0;
    float promedioRender = 0;

    int cantidadProc = 5;
    int punteroProc  = 0;
    int contadorProc = 0;
    /*
    int fHandler;
    int fSize;
    char *fPath = "algo.txt";
    char *buffer;

    char *token;*/

    _Objeto player;

    _Proceso *cmdList;

    cmdList = (_Proceso *)malloc(sizeof(_Proceso) * cantidadProc);

    strcpy(cmdList[0].nombre, "ABA");
    cmdList[0].estado = PORHACER;
    cmdList[0].value  = 0;
    cmdList[0].cmd    = ABAJO;

    strcpy(cmdList[1].nombre, "IZQ");
    cmdList[1].estado = PORHACER;
    cmdList[1].value  = 0;
    cmdList[1].cmd    = IZQUIERDA;

    strcpy(cmdList[2].nombre, "ARR");
    cmdList[2].estado = PORHACER;
    cmdList[2].value  = 0;
    cmdList[2].cmd    = ARRIBA;

    strcpy(cmdList[3].nombre, "DER");
    cmdList[3].estado = PORHACER;
    cmdList[3].value  = 0;
    cmdList[3].cmd    = DERECHA;

    strcpy(cmdList[4].nombre, "ABA");
    cmdList[4].estado = PORHACER;
    cmdList[4].value  = 0;
    cmdList[4].cmd    = ABAJO;

    _Proceso nuevoProceso;

    strcpy(nuevoProceso.nombre, "ARR");
    nuevoProceso.value = 5;
    nuevoProceso.cmd = ARRIBA;

    agregarComandoLista(cmdList, &nuevoProceso, &cantidadProc, CMD_APPEND);

    player.pos.x = 11;
    player.pos.y = 5;

    player.dir = ARRIBA;

    char display[SS_ROW][SS_COL];

    clearDisplay(display);

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

            switch(key)
            {
            case KB_INCIO:
                /*gets(cmd);

                player.dir = ARRIBA;

                player.pos.y = y;
                player.pos.x = x;*/
                cmdList[punteroProc].estado = HACIENDO;
                break;
            case KB_PAUSA:
                if(cmdList[punteroProc].estado == HACIENDO)
                {
                    cmdList[punteroProc].estado = PAUSADO;
                    break;
                }
                cmdList[punteroProc].estado = HACIENDO;
                break;
            }
        }
        system("cls");


        desplazarPlayer(&player, cmdList, &punteroProc, &contadorProc, &cantidadProc);
        ubicarPlayer(&player, display);

        displayMenu();
        refreshDisplay(display);

        /*
        getFHandler(&fHandler, fPath);

        fSize = lseek(fHandler, 0, SEEK_END);

        buffer = (char *)malloc(fSize);

        lseek(fHandler, 0, SEEK_SET);

        read(fHandler, buffer, sizeof(char) * fSize);

        printf("%d", fSize);

        token = strtok(buffer, "%[^\n]");


        while( token != NULL ) {
            printf( " %s\n", token );

            token = strtok(NULL, "%[^\n]");
        }*/

        printf("PLAYER POS: x%2d y%2d DIR:%2d\n", player.pos.x, player.pos.y, player.dir);
        puts("CMD\tESTADO\tVALUE");

        for(int i = 0; i < 6; i++)
        {
            printf("%-3s\t%-6d\t%-5d\n", cmdList[i].nombre, cmdList[i].estado, cmdList[i].value);
        }

        printf("\nFrame: %3d\n", frame);

        frame++;

        end = clock() - end;
        printf("Render: %3d ms\n", end);

        sumaPromRender += end;
        promedioRender = sumaPromRender / (float) frame;
        printf("Promedio: %3.1f ms\n", promedioRender);

        while((clock() - start) <= T_REFRESH);
    }

    free(cmdList);
    //close(fHandler);
    return 0;
}
/*********************/


