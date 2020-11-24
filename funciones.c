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
    int y = 0;
    while(y < SS_ROW)
    {
        puts(display[y]);
        y++;
    }
}

void clearDisplay(char display[SS_ROW][SS_COL])
{
    int y = 0;

    while(y < SS_ROW)
    {
        memset(display[y], CH_BGD, SS_COL);
        display[y][SS_COL - 1] = '\0';
        y++;
    }
}

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
        if(errno == ENOENT)
            return 0;
        else
            return -1;

    return 1;
}

int archivoCargarComandos(int *fHandler, _Proceso *cmdList)
{
 return 0;
}

/*********************/

