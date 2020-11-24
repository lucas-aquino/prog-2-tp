#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

/** DEFINE ***********/

/* Caracteres del display */
#define CH_BGD          176 //Caracter del fondo
#define CH_OBJ          177 //Caracter del objeto
#define CH_OBJ_DR       219 //Direccion del objeto

/* Pantalla */
#define SS_COL           61
#define SS_ROW           21

#define T_REFRESH       100 // Tiempo de espera para el programa

/* teclas de comandos */
#define KB_ARCH_F      1059 //[F1]  Limpia la lista de procesos y ejecuta el archivo hasta el final
#define KB_DETENER     1060 //[F2]  Detener el proceso
#define KB_ARCHIVO     1061 //[F3]  Selecciona un archivo y agrega los comando a lista de procesos
#define KB_PAUSA       1062 //[F4]  Pausar y reanudar proceso
#define KB_INCIO       1063 //[F5]  Setear la posicion de inicio

#define KB_ARRIBA      1072 //[ARR] Ejecutar el comando hacia arriba
#define KB_DERECHA     1077 //[DER] Ejecutar el comando hacia la Derecha
#define KB_ABAJO       1080 //[ABJ] Ejecutar el comando hacia abajo
#define KB_IZQUIERDA   1075 //[IZQ] Ejecutar el comando hacia la izquierda


/*********************/

/** ENUMS ************/

typedef enum Comandos {
    ARRIBA    = -1,
    DERECHA   =  2,
    ABAJO     =  1,
    IZQUIERDA = -2
} _Comando;

typedef enum Estado{
    ERROR = -1,
    PORHACER,
    HACIENDO,
    HECHO,
    PAUSADO
} _Estado;

/*********************/


/** ESTRUCTURAS ******/

typedef struct
{
    int x;
    int y;
} _Coordenada;

typedef struct
{
    char nombre[4];
    _Comando cmd;
    short value;
    _Estado estado;
} _Proceso;

typedef struct
{
   _Coordenada  pos;
   _Coordenada  size;
   _Comando     dir;
} _Objeto;

/*********************/

/** FUNCIONES ********/

//Display
void clearDisplay(char display[SS_ROW][SS_COL]);
void refreshDisplay(char display[SS_ROW][SS_COL]);
void displayMenu();
void ubicarPlayer(_Objeto *player, char display[SS_ROW][SS_COL]);
void desplazarPlayer(_Objeto *player, _Proceso *cdmList, int *punteroProceso, int *contadorProceso, int *cantidadProcesos);

//Manejo de Archivos
int getFHandler(int *fHandler, char *fPath);

//Comandos
int archivoCargarComandos(int *fHandler, _Proceso *cmdList);

/*********************/

#endif // FUNCIONES_H_INCLUDED
