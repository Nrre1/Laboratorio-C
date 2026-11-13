#include <stdio.h>        
#include <stdlib.h>      
#include <string.h>      
#include <math.h>     
#include "validaciones.h" 

#define TAM_LINEA 128 /* maximo de caracteres que se leen de una vez */

/* Pide un dato y solo lo acepta si es un NUMERO dentro del rango.
 * Con cualquier otra cosa (letras, simbolos, vacio, etc) muestra el error y vuelve a pedir. */
double lee_nro(const char *mensaje, double minimo, double maximo, bool soloEntero)
{
    char linea[TAM_LINEA];  
    char *fin;              
    char *coma;            
    double valor = 0.0;     
    bool valido;           
    int c;             

    do {                                                    /* repite hasta tener un dato valido (pide al menos una vez) */            
        valido = false;                                     
        printf("%s", mensaje);                              
        if (fgets(linea, sizeof linea, stdin) == NULL) {    
            printf("\nFin de la entrada. Se cierra el programa.\n");  /* avisa el motivo */
            exit(EXIT_FAILURE);                            
        }
        fin = strchr(linea, '\n');                          
        if (fin != NULL) {                                 
            *fin = '\0';                                    
            while ((coma = strchr(linea, ',')) != NULL)     
                *coma = '.';                                
            valor = strtod(linea, &fin);                  /* convierte a numero; "fin" queda donde se detuvo */
            valido = strspn(linea, "0123456789+-.") == strlen(linea) 
                     && fin != linea && *fin == '\0'        
                     && valor >= minimo && valor <= maximo  /* asegura que el num esta dentro del rango pedido */
                     && (!soloEntero || valor == floor(valor)); 
        } else {                                           
            while ((c = getchar()) != '\n' && c != EOF)     
                ;
        }
        if (!valido)                                     
            printf("  Error, ingrese un numero de %g a %g\n", minimo, maximo); /* mensaje de falla */
    } while (!valido);                                

    return valor;                                         /* devuelve el numero ya comprobado */
}
