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
    char fPath[80];
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
                strcpy(nuevoProc.nombre, "INICIO");
                nuevoProc.cmd = INICIO;
                nuevoProc.estado = PORHACER;

                printf("\nINICIO POSICION X: ");
                scanf("%d", &varUsuario);

                varUsuario += 2;

                if(varUsuario > SS_MAX_X)
                    varUsuario = SS_MAX_X;
                else if(varUsuario < 0)
                    varUsuario = 2;

                nuevoProc.pos.x = varUsuario;

                printf("INICIO POSICION Y: ");
                scanf("%d", &varUsuario);
                fflush(stdin);

                varUsuario++;

                if(varUsuario > SS_MAX_Y)
                    varUsuario = SS_MAX_Y;
                else if(varUsuario < 0)
                    varUsuario = 1;

                nuevoProc.pos.y = varUsuario;

                cmdList = cmdListAgregar(cmdList, nuevoProc, &cantidadProc, CMD_APPEND);

                nuevoProc.pos.x = -1;
                nuevoProc.pos.y = -1;

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

                strcpy(nuevoProc.nombre ,"ARRIBA");
                nuevoProc.estado = PORHACER;
                nuevoProc.cmd = ARRIBA;

                printf("\nDESPLAZAR HACIA ARRIBA: ");

                scanf("%d", &varUsuario);
                fflush(stdin);

                nuevoProc.value = varUsuario;

                cmdList = cmdListAgregar(cmdList, nuevoProc, &cantidadProc, CMD_APPEND);

            }

            if(key == KB_DERECHA)
            {

                strcpy(nuevoProc.nombre ,"DERECHA");
                nuevoProc.estado = PORHACER;
                nuevoProc.cmd = DERECHA;

                printf("\nDESPLAZAR HACIA LA DERECHA: ");

                scanf("%d", &varUsuario);
                fflush(stdin);

                nuevoProc.value = varUsuario;

                cmdList = cmdListAgregar(cmdList, nuevoProc, &cantidadProc, CMD_APPEND);
            }



            if(key == KB_ABAJO)
            {

                strcpy(nuevoProc.nombre ,"ABAJO");
                nuevoProc.estado = PORHACER;
                nuevoProc.cmd = ABAJO;

                printf("\nDESPLAZAR HACIA ABAJO: ");

                scanf("%d", &varUsuario);
                fflush(stdin);

                nuevoProc.value = varUsuario;

                cmdList = cmdListAgregar(cmdList, nuevoProc, &cantidadProc, CMD_APPEND);

            }

            if(key == KB_IZQUIERDA)
            {

                strcpy(nuevoProc.nombre ,"IZQUIERDA");
                nuevoProc.estado = PORHACER;
                nuevoProc.cmd = IZQUIERDA;

                printf("\nDESPLAZAR HACIA LA IZQUIERDA: ");

                scanf("%d", &varUsuario);
                fflush(stdin);

                nuevoProc.value = varUsuario;

                cmdList = cmdListAgregar(cmdList, nuevoProc, &cantidadProc, CMD_APPEND);

            }

            if(key == KB_ARCHIVO)
            {
                printf("INGRESE EL NOMBRE DEL ARCHIVO: ");

                scanf("%s", fPath);

                if(getFHandler(&fHandler, fPath))
                {
                    cmdList = cargarComandosArchivo(&fHandler, cmdList, &cantidadProc, CMD_OVERRIDE);
                }else
                    printf("Archivo No Encontrado!!");
            }

        }
        system("cls");

        fillDisplay(display);

        if(cmdList[punteroProc].cmd == INICIO && cmdList[punteroProc].estado == HACIENDO)
        {
            player.dir = ARRIBA;

            player.pos.x = cmdList[punteroProc].pos.x;
            player.pos.y = cmdList[punteroProc].pos.y;

            cmdList[punteroProc].estado = HECHO;
            if(punteroProc < cantidadProc - 1)
            {
                punteroProc++;
                cmdList[punteroProc].estado = HACIENDO;
            }
        }

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

        puts("\nLISTA DE COMANDOS POR HACER:");

        puts("\tCMD\t\tESTADO\t\tVALUE");

        for(int i = 0; i < cantidadProc; i++)
        {
            if(/*cmdList[i].estado == PORHACER ||*/ cmdList[i].estado == HACIENDO)
            {
                if(cmdList[i].cmd == INICIO)
                    printf("\t%-10s\t%-7d\t\t(%2d,%2d)\n", cmdList[i].nombre, cmdList[i].estado, cmdList[i].pos.x - 2, cmdList[i].pos.y - 1);
                else
                    printf("\t%-10s\t%-7d\t\t%-5d\n", cmdList[i].nombre, cmdList[i].estado, cmdList[i].value);
            }
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

    system("cls");
    printf("\n\n\tEL PROGRAMA SE CERRARA ENSEGIDA :(\n\n");
    while((clock() - start) <= 5000);

    free(cmdList);
    close(fHandler);
    return 0;
}
/*********************/


