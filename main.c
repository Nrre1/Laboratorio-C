#include <stdio.h>       
#include <stdlib.h>       
#include <time.h>          
#include "artemis.h"       
#include "validaciones.h"  

/* Muestra las opciones del menu */

static void Menu(void)
{
    printf("\nSIMULADOR MISION ARTEMIS\n");
    printf("\nBienvenido tripulante, seleccione alguna de las opciones porfavor:\n");
    printf("1. Cambiar altitud y masa\n");
    printf("2. Mostrar orbita LEO\n");
    printf("3. Pulso lateral\n");
    printf("4. Simulacion por turnos\n");
    printf("0. Salir\n");
}

int main(void)
{
    NaveOrion miNave;    /* la nave: se pasa por puntero a cada procedimiento */
    int opcion;          

    srand((unsigned)time(NULL));  

    printf("Ingrese los datos de la mision:\n");
    InicializarNave(&miNave);      /*  se piden al inicio los datos */

    do {                                                      /* se muestra el menui */
        Menu();
        opcion = (int)lee_nro("Seleccione una opcion: ", 0, 4, true); /* enteros de 0 a 4 */
        switch (opcion) {                                     /* ejecuta la eleccion */
            case 1: InicializarNave(&miNave);  break;         /* cambiaar datos / nuevos datos */
            case 2: MostrarOrb(&miNave);    break;         /* items a, b, c */
            case 3: PulsoLateral(&miNave);     break;         /* item d */
            case 4: Turnos(&miNave);    break;         /* juego por turnos */
            case 0: printf("Mision finalizada. Buen trabajo tripulante!.\n"); break;    /* salir */
        }
    } while (opcion != 0);                                    /* repite hasta elegir 0 */

    return 0;                                                 /* fin */
}
