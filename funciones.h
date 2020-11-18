#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

/** DEFINE ***********/

/* Caracteres del display */
#define CH_BGD          176 //Caracter del fondo
#define CH_OBJ          178 //Caracter del objeto
#define CH_OBJ_DR       219 //Direccion del objeto

/* Tamanno de la pantalla */
#define SS_COL           60
#define SS_ROW           21

/* teclas de comandos */
#define KB_INCIO       1065 //[F5]  Setear la posicion de inicio
#define KB_ARCH_F      1060 //[F1]  Limpia la lista de procesos y ejecuta el archivo hasta el final
#define KB_ARCHIVO     1062 //[F3]  Selecciona un archiuvo y agrega los comando a lista de procesos
#define KB_DETENER     1061 //[F2]  Detener el proceso

#define KB_ARRIBA      1072 //[ARR] Ejecutar el comando hacia arriba
#define KB_DERECHA     1077 //[DER] Ejecutar el comando hacia la Derecha
#define KB_ABAJO       1080 //[ABJ] Ejecutar el comando hacia abajo
#define KB_IZQUIERDA   1075 //[IZQ] Ejecutar el comando hacia la izquierda

/*********************/

/** ENUMS ************/

typedef enum Comandos {
    INCIO,
    ARRIBA,
    DERECHA,
    ABAJO,
    IZQUIERDA
} _Comandos;

/*********************/


/** ESTRUCTURAS ******/

typedef struct
{
    int x;
    int y;
} _Coordenada;

typedef struct
{
    char nombre[12];
    _Coordenada value;
    char estado;
} _Proceso;

typedef struct
{
   _Coordenada  pos;
   _Coordenada  size;
   _Comandos    dir;
} _Objeto;

/*********************/

/** FUNCIONES ********/

void refreshDisplay();

void displayMenu();

int getFHandler(int *fHandler, char *fPath);

int fHListaComandos(int *fHandler, _Proceso *cmdList);

/*********************/

#endif // FUNCIONES_H_INCLUDED
