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
void fillDisplay(char display[SS_ROW][SS_COL])
{
    int y = 0;

    while(y < SS_ROW)
    {
        memset(display[y], CH_BGD, SS_COL);
        memset(&display[y][SS_COL - 1], '\n', sizeof(char));
        y++;
    }
    display[SS_ROW - 1][SS_COL - 1]  = '\0';
}






//Comandos

_Proceso *cmdListAgregar(_Proceso *cmdList, _Proceso nuevoCmd, int *cantidadProc, int agregarModo)
{

    if(agregarModo == CMD_APPEND)
    {
        (*cantidadProc)++;
        cmdList = (_Proceso *)realloc(cmdList, sizeof(_Proceso) * (*cantidadProc));
    }else
    {
        *cantidadProc = 1;
        free(cmdList);
        cmdList = (_Proceso *)malloc(sizeof(_Proceso) * (*cantidadProc));
    }

    if(cmdList == NULL)
    {
        printf("No se ha podidio agregar el nuevo comando por falta de memoria");
        exit(1);
    }

    memcpy(&cmdList[(*cantidadProc) - 1], &nuevoCmd, sizeof(_Proceso));

    return cmdList;
}





//Jugador
void ubicarPlayer(_Objeto *player, char display[SS_ROW][SS_COL])
{
    memset(&display[player->pos.y - 1][player->pos.x - 2], CH_OBJ, sizeof(char) * 5);
    memset(&display[player->pos.y][player->pos.x - 2],     CH_OBJ, sizeof(char) * 5);
    memset(&display[player->pos.y + 1][player->pos.x - 2], CH_OBJ, sizeof(char) * 5);

    if(abs(player->dir) > 1)
    {
        memset(&display[player->pos.y - 1][player->pos.x + player->dir], CH_OBJ_DR, sizeof(char));
        memset(&display[player->pos.y][player->pos.x + player->dir],     CH_OBJ_DR, sizeof(char));
        memset(&display[player->pos.y + 1][player->pos.x + player->dir], CH_OBJ_DR, sizeof(char));
    }else
    {
        memset(&display[player->pos.y + player->dir][player->pos.x - 2], CH_OBJ_DR, sizeof(char) * 5);
    }
}



void desplazarPlayer(_Objeto *player, _Proceso *cmdList, int *punteroProceso, int *contadorProceso, int *cantidadProcesos, int isPasos)
{
    if(cmdList[*punteroProceso].estado == HACIENDO)
    {
        if(player->dir != cmdList[*punteroProceso].cmd)
        {
            player->dir = cmdList[*punteroProceso].cmd;
        }else if(cmdList[*punteroProceso].value > 0)
        {
            if(abs(cmdList[*punteroProceso].cmd) > 1)
            {

                if(cmdList[*punteroProceso].cmd == DERECHA && player->pos.x < SS_COL - 4)
                    player->pos.x += 1;
                else if(cmdList[*punteroProceso].cmd == IZQUIERDA && player->pos.x > 2 )
                    player->pos.x -= 1;
                else
                    cmdList[*punteroProceso].estado = ERROR;

            }else
            {

                if(cmdList[*punteroProceso].cmd == ABAJO && player->pos.y < SS_ROW - 2)
                    player->pos.y += 1;
                else if(cmdList[*punteroProceso].cmd == ARRIBA && player->pos.y > 1 )
                    player->pos.y -= 1;
                else
                    cmdList[*punteroProceso].estado = ERROR;

            }
            (*contadorProceso)++;
        }


        if(*contadorProceso >= cmdList[*punteroProceso].value && cmdList[*punteroProceso].estado != ERROR)
        {
            cmdList[*punteroProceso].estado = HECHO;
        }

        if(cmdList[*punteroProceso].estado == HECHO)
        {
            if(*punteroProceso < (*cantidadProcesos) - 1 && !isPasos)
                cmdList[++(*punteroProceso)].estado = HACIENDO;

            *contadorProceso = 0;
        }
    }
}





//Menu
void displayMenu()
{
    puts(
  "\n   PROGRAMACION II : TP Final - Lucas Aquino  2020\n\n"
    "          [F1]  Seleccione un archivo.\n"
    "          [F2]  Detener el jugador.\n"
    "          [F3]  Ejecutar un archivo paso por paso\n"
    "          [F4]  Iniciar o Pausar.\n"
    "          [F5]  Definir la posicion de inicio.\n\n"
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




_Proceso *cargarComandosArchivo(int *fHandler, _Proceso *cmdList, int *cantidadProcesos, int listMode)
{
    char cmd[16];
    int fSize;
    int l, i;
    _Proceso cmdAux;
    cmdAux.estado = PORHACER;
    char args[16];

    fSize = lseek(*fHandler, 0, SEEK_END);
    lseek(*fHandler, 0,SEEK_SET);

    while(1)
    {
        l = 0;
        for(i = 0; i < 16; i++)
        {
            if(read(*fHandler, &cmd[l], 1))
            {
                if(cmd[l] == '(')
                {
                    cmd[l] = '\0';
                    break;
                }else
                {
                    if(isalpha(cmd[l]))
                        l++;
                }

            }else
                break;
        }
        i = 0;
        while(cmd[i])
        {
            cmd[i] = toupper(cmd[i]);
            i++;
        }

        strcpy(cmdAux.nombre, cmd);

        if(strcmp(cmd, "INICIO") == 0)
        {
            cmdAux.cmd = INICIO;
            cmdAux.value = 0;

            l = 0;
            for(i = 0; i < 16; i++)
            {
                if(read(*fHandler, &args[l], 1))
                {
                    if(args[l] == ',')
                    {
                        args[l] = '\0';
                        break;
                    }else
                    {
                        if(isdigit(args[l]))
                            l++;
                    }
                }else
                    return 0;
            }

            if(atoi(args) > SS_MAX_X)
                cmdAux.pos.x = SS_MAX_X;
            else if(atoi(args) <= 0)
                cmdAux.pos.x = 2;
            else
                cmdAux.pos.x = atoi(args) + 2;

            l = 0;
            for(i = 0; i < 16; i++)
            {
                if(read(*fHandler, &args[l], 1))
                {
                    if(args[l] == ')')
                    {
                        args[l] = '\0';
                        break;
                    }else
                    {
                        if(isdigit(args[l]))
                            l++;
                    }
                }else
                    return 0;
            }

            if(atoi(args) > SS_MAX_Y)
                cmdAux.pos.y = SS_MAX_Y;
            else if(atoi(args) <= 0)
                cmdAux.pos.y = 1;
            else
                cmdAux.pos.y = atoi(args) + 1;


        }else
        {
            cmdAux.pos.x = 0;
            cmdAux.pos.y = 0;

            l = 0;
            for(i = 0; i < 16; i++)
            {
                if(read(*fHandler, &args[l], 1))
                {
                    if(args[l] == ')')
                    {
                        args[l] == '\0';
                        break;
                    }else
                    {
                        if(isdigit(args[i]))
                            l++;
                    }
                }else
                    return 0;
            }

            if(strcmp(cmd, "ARRIBA") == 0)
                cmdAux.cmd = ARRIBA;
            else if(strcmp(cmd, "IZQUIERDA") == 0)
                cmdAux.cmd = IZQUIERDA;
            else if(strcmp(cmd, "ABAJO") == 0)
                cmdAux.cmd = ABAJO;
            else if(strcmp(cmd, "DERECHA") == 0)
                cmdAux.cmd = DERECHA;
            else
                return 0;

            cmdAux.value = atoi(args);
        }

        //printf("\n%10s : { val : %2d, posX : %2d, posY : %2d }", cmdAux.nombre, cmdAux.value, cmdAux.pos.x, cmdAux.pos.y);

        cmdList = cmdListAgregar(cmdList, cmdAux, cantidadProcesos, CMD_APPEND);

        if(lseek(*fHandler, 0, SEEK_CUR) >= fSize - 5)
            break;
    }

    close(*fHandler);
    return cmdList;
}

/*********************/

