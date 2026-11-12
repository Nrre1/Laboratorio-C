# 🚀 Simulador Artemis
![Lenguaje](https://img.shields.io/badge/Lenguaje-C11-blue?logo=c&logoColor=white)

Universidad Tecnológica Nacional – Facultad Regional Resistencia Cátedra: Algoritmos y Estructuras de Datos · Ingeniería en Sistemas de Información Trabajo Práctico Integrador Final · Lenguaje C


Integrantes:
-
⭐ Arriazu, Nerea Micaela

⭐ Franco, Gastón Agustín

⭐ Lazarte, Valentino Mariano

⭐ Valussi Melendes, Fabrizio Francisco


Comisión: K1.3

Año: 2026 

Video de presentación del trabajo:

---

## Escenario asignado

> **Situación-Problema 2: Inserción y Estabilidad en Órbita Terrestre Baja — LEO (MCU y Gravitación)**

Tras apagar los motores de ascenso, la nave Orion queda en una órbita terrestre baja (LEO) de estacionamiento, donde describe un Movimiento Circular Uniforme (MCU) a altitud constante. Datos otorgados por el enunciado:

| Dato | Símbolo | Valor |
|------|:-------:|------:|
| Masa de la Tierra | MT | 5,972 × 10²⁴ kg |
| Radio medio de la Tierra | RT | 6.371.000 m |
| Constante de gravitación | G | 6,674 × 10⁻¹¹ N·m²/kg² |
| Altitud de la órbita | h | 192.000 m |
| Radio orbital (RT + h) | r | 6.563.000 m |
| Masa de Orion | m | 33.000 kg |
| Pulso lateral | a, Δt | 0,50 m/s² durante 10 s |
    
---

Fundamento Físico:
-
1) Ecuaciones Utilizadas:

| Magnitud | Ecuación |
|----------|----------|
| Radio orbital | $r = R_T + h$ |
| Fuerza gravitatoria | $F_g = \dfrac{G \, M_T \, m}{r^2}$ |
| Fuerza centrípeta | $F_c = \dfrac{m \, v^2}{r}$ |
| Velocidad orbital (de $F_g = F_c$, la masa se cancela) | $v = \sqrt{\dfrac{G \, M_T}{r}}$ |
| Período (MCU) | $T = \dfrac{2\pi r}{v}$ |
| Aceleración centrípeta | $a_c = \dfrac{v^2}{r}$ |
| Cambio de velocidad del pulso | $\Delta v = a \cdot t$ |
| Desviación lateral instantánea | $d = \tfrac{1}{2} \, a \, t^2$ |
| Energía específica (con $\mu = G M_T$) | $E = \dfrac{v_r^2 + v_t^2}{2} - \dfrac{\mu}{r}$ |
| Excentricidad | $e^2 = \left(\dfrac{r v_t^2}{\mu} - 1\right)^2 + \left(\dfrac{r v_r v_t}{\mu}\right)^2$ |
| Semieje mayor | $a = -\dfrac{\mu}{2E}$ |
| Perigeo / Apogeo | $a(1 - e)$ / $a(1 + e)$ |

3) ¿Qué hace el programa?

           - Calcula Fg y Fc por separado, muestra su diferencia relativa (≈ 10⁻¹⁶) y la deducción de v
           - Calcula y muestra T en s y en min.
           - Calcula y muestra ac
           - Calcula Δv, la desviación, y describe la nueva órbita (elíptica, con excentricidad, perigeo y apogeo)
---
   
## Funcionamiento del programa

### Reglas del Juego

1)	La partida tiene **5 turnos**
2)	En cada turno ocurre un **evento aleatorio** que desvía la nave con una velocidad radial entre −5,00 y +5,00 m/s. El programa muestra la velocidad radial acumulada
3)	El jugador corrige con un pulso lateral: aceleración a entre −2 y +2 m/s² (el signo indica el sentido: + hacia afuera, − hacia adentro, 0 = no actuar) y una duración t entre 0 y 30 s.
4)	Al terminar cada turno se muestra la órbita resultante (excentricidad, perigeo y apogeo)
5)	Se gana si después del 5.º turno la excentricidad es e ≤ 0,0001 (órbita casi circular, equivale a una velocidad radial residual de menos de ≈ 0,78 m/s). Si no, la misión queda incompleta
6)	Para estabilizar, el jugador debe elegir a · t ≈ − (velocidad radial actual)
7)	Al finalizar se genera automáticamente el **reporte final** de desempeño con todos los turnos

entrada de datos:

| Dato | Rango válido |
|------|:------------:|
| Altitud (h) | 180 a 2000 km |
| Masa (m) | 1000 a 100000 kg |
| Aceleración del pulso | 0,01 a 5 m/s² |
| Duración del pulso | 0,1 a 60 s |
| Aceleración en el juego | −2 a 2 m/s² |
| Duración en el juego | 0 a 30 s |
| Opción del menú | 0 a 4 |

Se acepta **coma o punto** como separador decimal

---

Menú Principal:
-
```text
      SIMULADOR ARTEMIS - ESCENARIO 2 LEO
      1. Cambiar altitud y masa
      2. Mostrar orbita LEO 
      3. Pulso lateral 
      4. Simulacion por turnos
      0. Salir
```

## Estructura del proyecto

```text
Laboratorio-C/
├── main.c            # main() y menú principal
├── artemis.h         # constantes, structs y prototipos
├── artemis.c         # lógica y cálculos físicos
├── validaciones.h    # prototipos de ingreso seguro
├── validaciones.c    # lectura validada de enteros, decimales y caracteres
├── Makefile          # compilación
└── README.md
```

| Módulo | Responsabilidad |
|--------|-----------------|
| `main.c` | Menú principal y flujo general |
| `artemis.h` / `artemis.c` | Tipos de datos, cálculos físicos, simulación por turnos y reporte final |
| `validaciones.h` / `validaciones.c` | Ingreso seguro de datos y mensajes de error |

--- 
Al iniciar, el programa pide altitud y masa (sin esos datos no existe la órbita). Luego repite el menú hasta que se elige 0

Estructuras de datos utilizadas:

Instrucciones de compilación y ejecución:

Ejemplo de ejecución:

---

Registro del uso de Inteligencia Artificial:


   



