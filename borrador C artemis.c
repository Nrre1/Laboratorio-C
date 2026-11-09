void calcula_Or(DatosOrbita *datos)        //La gravedad actua como fuerza centripeta: 
                                            // G*MT*m/r^2 = m*v^2/r   ->   v = sqrt(G*MT/r)   (la masa se cancela) 
                                            // Devuelve varios valores: por eso recibe un puntero al struct
{
    const double mu = G * MT;
    const double r  = RT + datos->altitudKm * 1000.0;
    const double v  = sqrt(mu / r);

    datos->radioOrbital          = r;
    datos->velocidadOrbital      = v;                         
    datos->fuerzaGravitatoria    = mu * datos->masa / (r * r);
    datos->fuerzaCentripeta      = datos->masa * v * v / r;   
    datos->periodoSegundos       = 2.0 * PI * r / v;         
    datos->aceleracionCentripeta = v * v / r;                
}

void muestra_result(const DatosOrbita *datos)
{
    printf("\na) Fg = G*MT*m/r^2 = %.6e N\n", datos->fuerzaGravitatoria);
    printf("   Fc = m*v^2/r    = %.6e N\n", datos->fuerzaCentripeta);
    printf("   Diferencia relativa = %.2e\n",
           fabs(datos->fuerzaGravitatoria - datos->fuerzaCentripeta) / datos->fuerzaGravitatoria);
    printf("   Si Fg actua como Fc: G*MT*m/r^2 = m*v^2/r -> v^2 = G*MT/r (la masa se cancela)\n");
    printf("   Velocidad orbital v = %.3f m/s\n", datos->velocidadOrbital);
    printf("b) Periodo T = %.2f s = %.2f min\n", datos->periodoSegundos, datos->periodoSegundos / 60.0);
    printf("c) Aceleracion centripeta = %.4f m/s2\n", datos->aceleracionCentripeta);
}

//  energia:        E = (vr^2 + vt^2)/2 - mu/r
//   excentricidad:  e^2 = (r*vt^2/mu - 1)^2 + (r*vr*vt/mu)^2
//   semieje mayor:  a = -mu / (2*E)
 //   perigeo = a*(1 - e)    apogeo = a*(1 + e)   (se guardan como altitud)

void eltos(double r, double vr, double vt, Elementos *elem)
{
    const double mu = G * MT;
    const double energia = (vr * vr + vt * vt) / 2.0 - mu / r;
    const double fx = r * vt * vt / mu - 1.0;
    const double fy = r * vr * vt / mu;
    const double semieje = -mu / (2.0 * energia);   // energia < 0 en todo el rango validado

    elem->excentricidad = sqrt(fx * fx + fy * fy);
    elem->perigeoKm = (semieje * (1.0 - elem->excentricidad) - RT) / 1000.0;
    elem->apogeoKm  = (semieje * (1.0 + elem->excentricidad) - RT) / 1000.0;
}

void mostrar_eltos(Elementos elem)
{
    printf("   e = %.6f | perigeo = %.2f km | apogeo = %.2f km\n",
           elem.excentricidad, elem.perigeoKm, elem.apogeoKm);
}

static void reporte_final(const Turno tab[], bool exito)
{
    int i;

    printf("\nREPORTE FINAL DE DESEMPENO\n");
    for (i = 0; i < 5; i++) {
        printf("Turno %d: perturbacion = %+.2f m/s | dv aplicado = %+.2f m/s\n",
               i + 1, tab[i].perturbacion, tab[i].deltaV);
        mostrar_eltos(tab[i].orbita);
    }
    if (exito)
        printf("MISION EXITOSA: orbita estabilizada.\n");
    else
        printf("MISION INCOMPLETA: la orbita sigue demasiado excentrica.\n");
}

