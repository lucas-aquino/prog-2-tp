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

    char userNumbers[2];

    float sumaPromRender = 0;
    float promedioRender = 0;

    int cantidadProc = 0;
    int punteroProc  = 0;
    int contadorProc = 0;

    int fHandler;
    int fSize;
    char *fPath = "algo.txt";
    char *buffer;

    char *token;

    _Objeto player;

    _Proceso *cmdList;

    cmdList = (_Proceso *)malloc(sizeof(_Proceso) * cantidadProc);

    _Proceso nuevoProc;
    int varUsuario;

    player.pos.x = 20;
    player.pos.y = 10;

    player.dir = ARRIBA;

    char display[SS_ROW][SS_COL];

    fillDisplay(display);


    while(1)
    {
        start = clock();
        end = clock();

        if(kbhit())
        {
            key = getch();

            if(key == 0 || key == 224)
                key = getch() + 1000;

            if(key == 27)
            {
                free(cmdList);
                break;
            }

            if(key == KB_INCIO)
            {
                printf("\nINICIO POSICION X: ");
                scanf("%d", &varUsuario);

                varUsuario += 2;

                if(varUsuario > SS_MAX_X)
                    varUsuario = SS_MAX_X;
                else if(varUsuario < 0)
                    varUsuario = 2;

                player.pos.x = varUsuario;

                printf("INICIO POSICION Y: ");
                scanf("%d", &varUsuario);
                fflush(stdin);

                varUsuario++;

                if(varUsuario > SS_MAX_Y)
                    varUsuario = SS_MAX_Y;
                else if(varUsuario < 0)
                    varUsuario = 1;

                player.pos.y = varUsuario;

            }

            if(key == KB_PAUSA)
            {
                if(cmdList[punteroProc].estado == HACIENDO)
                    cmdList[punteroProc].estado = PAUSADO;
                else if(cmdList[punteroProc].estado != ERROR && cmdList[punteroProc].estado != HECHO)
                    cmdList[punteroProc].estado = HACIENDO;
                else if(punteroProc < cantidadProc - 1)
                {
                    punteroProc++;
                    cmdList[punteroProc].estado = HACIENDO;
                }
            }

            if(key == KB_ARRIBA)
            {

                strcpy(nuevoProc.nombre ,"ARR");
                nuevoProc.estado = PORHACER;
                nuevoProc.cmd = ARRIBA;

                printf("\nDESPLAZAR HACIA ARRIBA: ");

                scanf("%d", &varUsuario);
                fflush(stdin);

                nuevoProc.value = varUsuario;

                cantidadProc++;
                cmdList = (_Proceso *)realloc(cmdList, sizeof(_Proceso) * cantidadProc);

                if(cmdList == NULL)
                {
                    printf("No se ha podidio agregar el nuevo comando por falta de memoria");
                    exit(1);
                }

                memcpy(&cmdList[cantidadProc - 1], &nuevoProc, sizeof(_Proceso));

            }

            if(key == KB_DERECHA)
            {

                strcpy(nuevoProc.nombre ,"DER");
                nuevoProc.estado = PORHACER;
                nuevoProc.cmd = DERECHA;

                printf("\nDESPLAZAR HACIA LA DERECHA: ");

                scanf("%d", &varUsuario);
                fflush(stdin);

                nuevoProc.value = varUsuario;

                cantidadProc++;
                cmdList = (_Proceso *)realloc(cmdList, sizeof(_Proceso) * cantidadProc);

                if(cmdList == NULL)
                {
                    printf("No se ha podidio agregar el nuevo comando por falta de memoria");
                    exit(1);
                }

                memcpy(&cmdList[cantidadProc - 1], &nuevoProc, sizeof(_Proceso));
            }



            if(key == KB_ABAJO)
            {

                strcpy(nuevoProc.nombre ,"ABA");
                nuevoProc.estado = PORHACER;
                nuevoProc.cmd = ABAJO;

                printf("\nDESPLAZAR HACIA ABAJO: ");

                scanf("%d", &varUsuario);
                fflush(stdin);

                nuevoProc.value = varUsuario;

                cantidadProc++;
                cmdList = (_Proceso *)realloc(cmdList, sizeof(_Proceso) * cantidadProc);

                if(cmdList == NULL)
                {
                    printf("No se ha podidio agregar el nuevo comando por falta de memoria");
                    exit(1);
                }

                memcpy(&cmdList[cantidadProc - 1], &nuevoProc, sizeof(_Proceso));

            }

            if(key == KB_IZQUIERDA)
            {

                strcpy(nuevoProc.nombre ,"IZQ");
                nuevoProc.estado = PORHACER;
                nuevoProc.cmd = IZQUIERDA;

                printf("\nDESPLAZAR HACIA LA IZQUIERDA: ");

                scanf("%d", &varUsuario);
                fflush(stdin);

                nuevoProc.value = varUsuario;

                cantidadProc++;
                cmdList = (_Proceso *)realloc(cmdList, sizeof(_Proceso) * cantidadProc);

                if(cmdList == NULL)
                {
                    printf("No se ha podidio agregar el nuevo comando por falta de memoria");
                    exit(1);
                }

                memcpy(&cmdList[cantidadProc - 1], &nuevoProc, sizeof(_Proceso));

            }

        }
        system("cls");



        /*
        getFHandler(&fHandler, fPath);

        fSize = lseek(fHandler, 0, SEEK_END);

        buffer = (char *)malloc(fSize);

        lseek(fHandler, 0, SEEK_SET);

        read(fHandler, buffer, sizeof(char) * fSize);

        //printf("%d", fSize);

        token = strtok(buffer, "%[^\n]");*/


        fillDisplay(display);

        //Movimiento del Jugador
        if(cantidadProc != 0)
            desplazarPlayer(&player, cmdList, &punteroProc, &contadorProc, &cantidadProc);


        //CLI
        displayMenu();
        ubicarPlayer(&player, display);
        puts((char *)display);


        printf("\nPLAYER POS: x%2d y%2d DIR:%2d\n", player.pos.x - 2, player.pos.y - 1, player.dir);

        printf("\nCMD SIZE: %d", sizeof(_Proceso));

        printf("\nCMDLIST SIZE: %d", sizeof(_Proceso) * cantidadProc);

        printf("\nMEMPOS CMDLIST: %p", cmdList);

        printf("\nPTR CMD: %d\n", punteroProc);

        printf("\nCANTIDAD COMANDO: %d", cantidadProc);

        puts("\nLISTA DE COMANDOS:");

        puts("\tCMD\tESTADO\tVALUE");

        for(int i = 0; i < cantidadProc; i++)
        {
            if(cmdList[i].estado != HECHO)
                printf("\t%-3s\t%-6d\t%-5d\n", cmdList[i].nombre, cmdList[i].estado, cmdList[i].value);
        }

        printf("\nPANTALLA: %d", sizeof(display));
        printf("\nFRAME: %3d\n", frame);

        frame++;

        end = clock() - end;
        printf("RENDER: %3d ms\n", end);

        sumaPromRender += end;
        promedioRender = sumaPromRender / (float)frame;
        printf("PROMEDIO: %3.1f ms\n", promedioRender);

        while((clock() - start) <= T_REFRESH);
    }

    free(cmdList);
    //close(fHandler);
    return 0;
}
/*********************/


