#ifndef ARTEMIS_H
#define ARTEMIS_H

/* Constantes  */
#define G   6.674e-11   
#define Mt  5.972e24           
#define Rt  6371000.0           
#define Pi  3.141592653589793  
#define Excen      0.0001      
#define MaxTurnos 5            

/*  Tipos de datos */

typedef struct {
    double masa;                   /* m [kg] */
    double altitud;                /* h [km] */
    double radio_orbital;          /* r = RT + h [m] */
    double fuerza_gravitatoria;    /* Fg [N] */
    double fuerza_centripeta;      /* Fc [N] */
    double velocidad_orbital;      /* v [m/s] */
    double periodo_segundos;       /* T [s] */
    double aceleracion_centripeta; /* ac [m/s2] */
} NaveOrion;

/* Forma de una orbita  */
typedef struct {
    double excentricidad;         
    double perigeo_km;           
    double apogeo_km;           
} Elementos;

/* Un turno del juego */
typedef struct {
    double perturbacion;        
    double delta_v;                
    Elementos orbita;              
} Turno;

/* Funciones de artemis.c  */
void InicializarNave(NaveOrion *nave);
void CalcVelocidad(NaveOrion *nave);
void CalcPeriodo(NaveOrion *nave);
void CalcAceleracion(NaveOrion *nave);
void MostrarOrb(const NaveOrion *nave);
void CalcElementos(double r, double vr, double vt, Elementos *e);
void MostrarElem(Elementos e);
void PulsoLateral(const NaveOrion *nave);
void Turnos(const NaveOrion *nave);

#endif
