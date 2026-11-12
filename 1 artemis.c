#include <stdio.h>         
#include <stdlib.h>        
#include <stdbool.h>       
#include <math.h>          
#include "artemis.h"       
#include "validaciones.h"  


/* Item a) la gravedad actua como fuerza centripeta.*/
void CalcVelocidad(NaveOrion *nave)
{
    const double mu = G * Mt;                  
    const double r  = nave->radio_orbital;     

    nave->fuerza_gravitatoria = mu * nave->masa / (r * r);   
    nave->velocidad_orbital   = sqrt(mu / r);                
    nave->fuerza_centripeta   = nave->masa * nave->velocidad_orbital * nave->velocidad_orbital / r; 
}

/* Item b) periodo del movimiento circular uniforme*/
void CalcPeriodo(NaveOrion *nave)
{
    nave->periodo_segundos = 2.0 * Pi * nave->radio_orbital / nave->velocidad_orbital;
}

/* Item c): aceleracion centripeta*/
void CalcAceleracion(NaveOrion *nave)
{
    nave->aceleracion_centripeta = nave->velocidad_orbital * nave->velocidad_orbital / nave->radio_orbital; 
}

/* Solicita masa y altitud al usuario y calcula la orbita. */
void InicializarNave(NaveOrion *nave)
{
    nave->altitud = lee_nro("Altitud orbital h [km]: ", 180, 2000, false);    
    nave->masa    = lee_nro("Masa de la nave m [kg]: ", 1000, 100000, false);  
    nave->radio_orbital = Rt + nave->altitud * 1000.0;  
    CalcVelocidad(nave);      
    CalcPeriodo(nave);        
    CalcAceleracion(nave);    
}

/* Muestra los items a), b) y c). */
void MostrarOrb(const NaveOrion *nave)
{
    printf("\na) Fg = G*Mt*m/r^2 = %.6e N\n", nave->fuerza_gravitatoria);   /* fuerza gravitatoria */
    printf("   Fc = m*v^2/r    = %.6e N\n", nave->fuerza_centripeta);       /* fuerza centripeta */
    printf("   Diferencia relativa = %.2e\n",                               /* prueba numerica de que Fg = Fc */
           fabs(nave->fuerza_gravitatoria - nave->fuerza_centripeta) / nave->fuerza_gravitatoria);
    printf("   Si Fg actua como Fc: G*MT*m/r^2 = m*v^2/r -> v^2 = G*Mt/r (la masa se cancela)\n"); /* demostracion analitica */
    printf("   Velocidad orbital v = %.3f m/s\n", nave->velocidad_orbital); /* resultado de a) */
    printf("b) Periodo T = %.2f s = %.2f min\n",                            /* resultado de b) en s y min */
           nave->periodo_segundos, nave->periodo_segundos / 60.0);
    printf("c) Aceleracion centripeta = %.4f m/s2\n", nave->aceleracion_centripeta); /* resultado de c) */
}

/* item d y juego */

void CalcElementos(double r, double vr, double vt, Elementos *e)
{
    const double mu = G * Mt;                                  
    const double energia = (vr * vr + vt * vt) / 2.0 - mu / r; 
    const double fx = r * vt * vt / mu - 1.0;         
    const double fy = r * vr * vt / mu;             
    const double semieje = -mu / (2.0 * energia);          

    e->excentricidad = sqrt(fx * fx + fy * fy);                      
    e->perigeo_km = (semieje * (1.0 - e->excentricidad) - Rt) / 1000.0;  
    e->apogeo_km  = (semieje * (1.0 + e->excentricidad) - Rt) / 1000.0;  
}

/* imprime la forma de una orbita */
void MostrarElem(Elementos e)
{
    printf("   e = %.6f | perigeo = %.2f km | apogeo = %.2f km\n",
           e.excentricidad, e.perigeo_km, e.apogeo_km);
}

/*  item d) pulso lateral*/

/* Aceleracion a perpendicular a la velocidad durante t.*/
void PulsoLateral(const NaveOrion *nave)
{
    double a, t, dv;       /* aceleracion, duracion y cambio de velocidad */
    Elementos e;           /* forma de la orbita despues del pulso */

    a = lee_nro("Aceleracion lateral a [m/s2]: ", 0.01, 5, false);  
    t = lee_nro("Duracion del pulso t [s]: ", 0.1, 60, false);     
    dv = a * t;                                                    
    CalcElementos(nave->radio_orbital, dv, nave->velocidad_orbital, &e);

    printf("\nCambio de velocidad lateral dv = a*t = %.3f m/s\n", dv);       
    printf("Desviacion lateral instantanea 1/2*a*t^2 = %.3f m\n", 0.5 * a * t * t); 
    printf("Trayectoria: la orbita circular pasa a ser eliptica (e = dv/v)\n");     
    MostrarElem(e);                                                           
}

/*SIMULACION POR TURNOS */
/*Reporte final: recorre el arreglo de turnos y muestra el resultado.*/

static void ReporteFinal(const Turno tab[], bool exito)
{
    int i;    /* indice del arreglo (en C empieza en 0) */

    printf("\nREPORTE FINAL DE DESEMPENO\n");
    for (i = 0; i < MaxTurnos; i++) {                                  
        printf("Turno %d: perturbacion = %+.2f m/s | dv aplicado = %+.2f m/s\n",
               i + 1, tab[i].perturbacion, tab[i].delta_v);           
        MostrarElem(tab[i].orbita);                               
    }
    if (exito)                                                         
        printf("MISION EXITOSA: orbita estabilizada.\n");
    else
        printf("MISION INCOMPLETA: la orbita sigue demasiado excentrica.\n");
}

/* Juego: en cada turno un evento aleatorio desvia la nave y el jugador corrige con un pulso lateral.*/
/* Gana si despues de MaxTurnos turnos la orbita es casi circular (e <= Excen).*/
 
void Turnos(const NaveOrion *nave)
{
    Turno tab[MaxTurnos];                    /* arreglo de structs: un registro por turno */
    double vr = 0.0;                         
    const double vt = nave->velocidad_orbital; 
    double a, t, dv;                         
    int turno;                                

    printf("\nSIMULACION POR TURNOS: deje la orbita casi circular (e <= %g)\n", Excen);
    for (turno = 0; turno < MaxTurnos; turno++) {                      
        tab[turno].perturbacion = (rand() % 1001) / 100.0 - 5.0;        
        vr += tab[turno].perturbacion;                                 
        printf("\n--- TURNO %d de %d ---\n", turno + 1, MaxTurnos);
        printf("Evento: dv radial = %+.2f m/s | velocidad radial actual = %+.2f m/s\n",
               tab[turno].perturbacion, vr);                           

        a = lee_nro("Aceleracion [m/s2] (+ afuera, - adentro, 0 = no actuar): ", -2, 2, false);
        t = lee_nro("Duracion del pulso [s]: ", 0, 30, false);         
        dv = a * t;                                                  
        vr += dv;                                                      

        tab[turno].delta_v = dv;                                        
        CalcElementos(nave->radio_orbital, vr, vt, &tab[turno].orbita);
        printf("Resultado del turno:\n");
        MostrarElem(tab[turno].orbita);
    }
    ReporteFinal(tab, tab[MaxTurnos - 1].orbita.excentricidad <= Excen); /* gana si el ultimo turno quedo casi circular */
}

