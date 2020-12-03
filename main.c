#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

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

    int cantidadProc = 0;
    int punteroProc  = 0;
    int contadorProc = 0;

    int isPasos = 0;

    int fHandler;
    char fPath[80];

    _Objeto player;

    _Proceso *cmdList;

    cmdList = (_Proceso *)malloc(sizeof(_Proceso) * cantidadProc);

    _Proceso nuevoProc;
    int varUsuario;

    player.pos.x = 2;
    player.pos.y = SS_MAX_Y;

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
                else if(varUsuario <= 0)
                    varUsuario = 1;

                nuevoProc.pos.y = varUsuario;

                cmdList = cmdListAgregar(cmdList, nuevoProc, &cantidadProc, CMD_APPEND);

                nuevoProc.pos.x = 0;
                nuevoProc.pos.y = 0;

            }

            if(key == KB_DETENER)
            {

                cantidadProc = 0;
                punteroProc  = 0;
                contadorProc = 0;

                free(cmdList);

                cmdList = (_Proceso *)malloc(sizeof(_Proceso) * cantidadProc);
            }


            if(key == KB_PAUSA)
            {
                if(cmdList[punteroProc].estado == HACIENDO)
                    cmdList[punteroProc].estado = PAUSADO;
                else if(cmdList[punteroProc].estado != ERROR && cmdList[punteroProc].estado != HECHO)
                    cmdList[punteroProc].estado = HACIENDO;
                else if(punteroProc < cantidadProc - 1)
                    cmdList[++punteroProc].estado = HACIENDO;
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
                {
                    printf("Archivo No Encontrado!!");
                    while((clock() - start) <= 5000);
                }
            }

            if(key == KB_ARCH_PXP)
            {
                if(!isPasos)
                {
                    printf("INGRESE EL NOMBRE DEL ARCHIVO: ");

                    scanf("%s", fPath);

                    if(getFHandler(&fHandler, fPath))
                    {
                        cmdList = cargarComandosArchivo(&fHandler, cmdList, &cantidadProc, CMD_OVERRIDE);
                        isPasos = 1;
                    }else
                    {
                        printf("Archivo No Encontrado!!");
                        while((clock() - start) <= 5000);
                    }
                }else if(cmdList[punteroProc].estado == HECHO)
                {
                    cmdList[++punteroProc].estado = HACIENDO;
                }else
                    cmdList[punteroProc].estado = HACIENDO;

            }

        }
        system("cls");

        fillDisplay(display);

        //Define el proceso que indica el inicio del player
        if(cmdList[punteroProc].cmd == INICIO && cmdList[punteroProc].estado == HACIENDO)
        {
            player.dir = ARRIBA;

            player.pos.x = cmdList[punteroProc].pos.x;
            player.pos.y = cmdList[punteroProc].pos.y;

            cmdList[punteroProc].estado = HECHO;
            if(punteroProc < cantidadProc - 1 && !isPasos)
                cmdList[++punteroProc].estado = HACIENDO;
        }


        //Movimiento del Jugador
        if(cantidadProc != 0)
            desplazarPlayer(&player, cmdList, &punteroProc, &contadorProc, &cantidadProc, isPasos);


        if(punteroProc >= cantidadProc - 1 && isPasos)
            isPasos = 0;

        //CLI
        displayMenu();



        //Ubica el jugador en el display
        ubicarPlayer(&player, display);



        //Muestra el display
        puts((char *)display);





        //Muestra la posicion del jugador
        //printf("\nPLAYER POS: x%2d y%2d DIR:%2d\n", player.pos.x - 2, player.pos.y - 1, player.dir);


        //Muestra el tamanno en bytes del comando
        //printf("\nCMD SIZE: %d", sizeof(_Proceso));

        //Muestra el tamanno en byte de la lista de comandos
        //printf("\nCMDLIST SIZE: %d", sizeof(_Proceso) * cantidadProc);

        //Muestra la posicion en memoria de la lista de comandos
        //printf("\nMEM-POS CMDLIST: %p", cmdList);

        //Muestra a que posicion de la lista de comandos esta apuntando
        //printf("\nPTR A CMD: %d", punteroProc);

        //Muestra la cantidad de comandos de la lista
        //printf("\nCANTIDAD DE CMD: %d", cantidadProc);

        //Muestra la cantidad de comandos que quedan por ejecutar
        //printf("\nCMD QUE FALTAN: %d", cantidadProc - punteroProc - 1);

        if(cmdList[punteroProc].estado == PAUSADO && round((float)(frame % 10) / 10))
            puts("\n\t\t\tPAUSA!!");
        else
            puts("\n");

        //Modulo de frame (para hacer titilar el cartel de pausa)
        //printf("\nMODULO DE FRAME: %.2f", round((float)(frame % 10) / 10));

        //Muestra la lista de comandos

        puts("\n---------------------------------------");
        puts("    COMANDO  |  VALOR");
        puts("---------------------------------------");

        for(int i = 0; i < cantidadProc; i++)
        {
            if(cmdList[i].estado == PORHACER || cmdList[i].estado == HACIENDO)
            {
                if(cmdList[i].cmd == INICIO)
                    printf(" %10s  |  (%2d,%2d)\n", cmdList[i].nombre, cmdList[i].pos.x - 2, cmdList[i].pos.y - 1);
                else
                    printf(" %10s  |  %-5d\n", cmdList[i].nombre, cmdList[i].value);
            }
        }
        puts("\n");



        //Esto es para ver el tamanno del display
        //printf("\nPANTALLA: %d", sizeof(display));

        //Esto es para ver el numero del frame actual
        //printf("\nFRAME: %3d\n", frame);


        //Lleva la cuanta de los frames del programa

        frame++;



        //Aca se calcula el tiempo que se tardo en mostrar el frame
        end = clock() - end;

        sumaPromRender += end;
        promedioRender = sumaPromRender / (float)frame;



        //Aca se muestra el tiempo en que se tardo en mostrar el frame
        //printf("RENDER: %3d ms\n", end);
        //printf("PROMEDIO: %3.1f ms\n", promedioRender);



        //Tiempo de espera para el proximo frame
        while((clock() - start) <= T_REFRESH);

    }

    system("cls");

    free(cmdList);
    close(fHandler);
    return 0;
}
/*********************/


