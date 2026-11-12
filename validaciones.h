#ifndef VALIDACIONES_H   
#define VALIDACIONES_H

#include <stdbool.h>     
/*devuelve un numero valido entre minimo y maximo (entero si soloEntero es true). */
double lee_nro(const char *mensaje, double minimo, double maximo, bool soloEntero);

#endif
