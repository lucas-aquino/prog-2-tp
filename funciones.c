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




//DISPLAY
void refreshDisplay(char display[SS_ROW][SS_COL])
{
    int y = 0;/*
    while(y < SS_ROW)
    {
        puts(display[y]);
        y++;
    }*/

    puts(display);
}

void clearDisplay(char display[SS_ROW][SS_COL])
{
    int y = 0;

    while(y < SS_ROW)
    {
        memset(display[y], CH_BGD, SS_COL);
        display[y][SS_COL - 1] = '\n';
        y++;
    }
}

//Jugador
void ubicarPlayer(_Objeto *player, char display[SS_ROW][SS_COL])
{
    char i;
    i = -2;

    memset(&display[player->pos.y - 1][player->pos.x + i], CH_OBJ, sizeof(char) * 5);
    memset(&display[player->pos.y][player->pos.x + i],     CH_OBJ, sizeof(char) * 5);
    memset(&display[player->pos.y + 1][player->pos.x + i], CH_OBJ, sizeof(char) * 5);

    if(abs(player->dir) > 1)
    {
        memset(&display[player->pos.y - 1][player->pos.x + player->dir], CH_OBJ_DR, sizeof(char));
        memset(&display[player->pos.y][player->pos.x + player->dir],     CH_OBJ_DR, sizeof(char));
        memset(&display[player->pos.y + 1][player->pos.x + player->dir], CH_OBJ_DR, sizeof(char));
    }else
    {
        memset(&display[player->pos.y + player->dir][player->pos.x + i], CH_OBJ_DR, sizeof(char) * 5);
    }
}

void desplazarPlayer(_Objeto *player, _Proceso *cmdList, int *punteroProceso, int *contadorProceso, int *cantidadProcesos)
{
    if(*cantidadProcesos > 0 && cmdList[*punteroProceso].estado == HACIENDO)
    {
        player->dir = cmdList[*punteroProceso].cmd;
        if(cmdList[*punteroProceso].value > 0)
        {
            if(abs(cmdList[*punteroProceso].cmd) > 1)
            {

                if(cmdList[*punteroProceso].cmd == DERECHA && player->pos.x < SS_COL - 2)
                    player->pos.x += 1;
                else if(cmdList[*punteroProceso].cmd == IZQUIERDA && player->pos.x > 2 )
                    player->pos.x -= 1;
                else
                    cmdList[*punteroProceso].estado = ERROR;
            }else
            {
                if(player->pos.y >= 2 && player->pos.x <= SS_ROW - 2)
                {
                    player->pos.y += cmdList[*punteroProceso].cmd;
                }else
                    cmdList[*punteroProceso].estado = ERROR;
            }
        }

        (*contadorProceso)++;

        if(*contadorProceso >= cmdList[*punteroProceso].value && cmdList[*punteroProceso].estado != ERROR)
        {
            cmdList[*punteroProceso].estado = HECHO;
            (*punteroProceso)++;
            cmdList[*punteroProceso].estado = HACIENDO;
            *contadorProceso = 0;
            (*cantidadProcesos)--;
        }

        if(cmdList[*punteroProceso].estado == ERROR)
        {
            (*punteroProceso)++;
            cmdList[*punteroProceso].estado = HACIENDO;
            *contadorProceso = 0;
            (*cantidadProcesos)--;
        }
    }
}



//Menu
void displayMenu()
{
    puts(
  "\n   PROGRAMACION II : TP Final - Lucas Aquino  2020\n\n"
    "   Controles:\n\n"
    "          [F1]  Seleccione un archivo.\n"
    "          [F2]  Detener el jugador.\n"
    "          [F3]  Reemplazar comandos por un archivo.\n"
    "          [F4]  Pausar o Reanudar.\n"
    "          [F5]  Definir la posicion de inicio.\n\n"
    "   Agregar directamente comandos a la lista de comandos:\n\n"
    "      [ARRIBA]  Indicar los pasos hacia ARRIBA.\n"
    "     [DERECHA]  Indicar los pasos hacia la DERECHA.\n"
    "       [ABAJO]  Indicar los pasos hacia ABAJO.\n"
    "   [IZQUIERDA]  Indicar los pasos hacia la IZQUIERDA.\n\n"
    );
}



//Manejo de Archivos
int getFHandler(int *fHandler, char *fPath)
{
    *fHandler = open(fPath, O_RDONLY | O_BINARY);

    if(*fHandler == -1)
    {
        if(errno == ENOENT)
            return 0;

        return -1;
    }

    return 1;
}

int agregarComandoLista(_Proceso *cmdList, _Proceso *cmdAgregar, int *cantidadProcesos, int modeList)
{
    if(modeList == CMD_OVERRIDE)
    {
        free(cmdList);
        *cantidadProcesos = 1;
        cmdList = (_Proceso *)malloc(sizeof(_Proceso) * (*cantidadProcesos));
    }

    if(modeList == CMD_APPEND)
    {
        (*cantidadProcesos)++;
        cmdList = (_Proceso *)realloc(cmdList, sizeof(_Proceso) * (*cantidadProcesos));
    }


    cmdAgregar->estado = PORHACER;

    memcpy(&cmdList[(*cantidadProcesos) - 1], cmdAgregar, sizeof(_Proceso));

    return -1;
}

int cargarComandosArchivo(int *fHandler, _Proceso *cmdList)
{
    return 0;
}

/*********************/

