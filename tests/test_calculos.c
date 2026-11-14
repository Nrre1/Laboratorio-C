#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "artemis.h"

static void comprobar_cerca(double actual, double esperado, double tolerancia)
{
    assert(fabs(actual - esperado) < tolerancia);
}

int main(void)
{
    NaveOrion nave = {0};

    nave.masa = 33000.0;
    nave.radio_orbital = RT + 192000.0;

    CalcVelocidad(&nave);

    comprobar_cerca(nave.velocidad_orbital, 7792.95, 0.01);
    comprobar_cerca(nave.fuerza_gravitatoria, 305362.10, 1.0);
    comprobar_cerca(nave.fuerza_gravitatoria, nave.fuerza_centripeta, 0.01);

    CalcPeriodo(&nave);
    comprobar_cerca(nave.periodo_segundos, 5291.52, 0.01);

    CalcAceleracion(&nave);
    comprobar_cerca(nave.aceleracion_centripeta, 9.2534, 0.001);

    Elementos orbita;
    CalcElementos(nave.radio_orbital, 0.0, nave.velocidad_orbital, &orbita);

    comprobar_cerca(orbita.excentricidad, 0.0, 1e-10);
    comprobar_cerca(orbita.perigeo_km, 192.0, 0.01);
    comprobar_cerca(orbita.apogeo_km, 192.0, 0.01);

    CalcElementos(nave.radio_orbital, 10.0, nave.velocidad_orbital, &orbita);
    assert(orbita.excentricidad > 0.0);
    assert(orbita.perigeo_km < orbita.apogeo_km);

    puts("Pruebas de calculo: OK");
    return 0;
}