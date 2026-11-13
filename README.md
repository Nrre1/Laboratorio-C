# 🚀 Simulador Artemis                                                                                                                                                                              
![Lenguaje](https://img.shields.io/badge/Lenguaje-C11-blue?logo=c&logoColor=white)

Universidad Tecnológica Nacional – Facultad Regional Resistencia, Cátedra: Algoritmos y Estructuras de Datos · Ingeniería en Sistemas de Información, Trabajo Práctico Integrador Final · Lenguaje C


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

2) ¿Qué hace el programa?

           - Calcula Fg y Fc por separado, muestra su diferencia relativa (≈ 10⁻¹⁶) y la deducción de v
           - Calcula y muestra T en s y en min.
           - Calcula y muestra ac
           - Calcula Δv, la desviación, y describe la nueva órbita (elíptica, con excentricidad, perigeo y apogeo)
---
   
## Funcionamiento del programa

### Reglas del Juego

1)	La partida tiene **5 turnos**.
2)	En cada turno ocurre un **evento aleatorio** que desvía la nave con una velocidad radial entre −5,00 y +5,00 m/s. El programa muestra la velocidad radial acumulada.
3)	El jugador corrige con un pulso lateral: aceleración a entre −2 y +2 m/s² (el signo indica el sentido: + hacia afuera, − hacia adentro, 0 = no actuar) y una duración t entre 0 y 30 s.
4)	Al terminar cada turno se muestra la órbita resultante (excentricidad, perigeo y apogeo).
5)	Se gana si después del 5.º turno la excentricidad es e ≤ 0,0001 (órbita casi circular, equivale a una velocidad radial residual de menos de ≈ 0,78 m/s). Si no, la misión queda incompleta.
6)	Para estabilizar, el jugador debe elegir a · t ≈ − (velocidad radial actual).
7)	Al finalizar se genera automáticamente el **reporte final** de desempeño con todos los turnos.

Tabla de datos esperados:
En esta tabla el usuario debe ingresar valores dentro del rango permitido respectivamente para cada dato. Si ingresa un dato erróneo se le informara y le pedirá nuevamente que ingrese un dato valido.

| Dato | Rango válido |
|------|:------------:|
| Altitud (h) | 180 a 2000 km |
| Masa (m) | 1000 a 100000 kg |
| Aceleración del pulso | 0,01 a 5 m/s² |
| Duración del pulso | 0,1 a 60 s |
| Aceleración en el juego | −2 a 2 m/s² |
| Duración en el juego | 0 a 30 s |
| Opción del menú | 0 a 4 |

Se acepta **coma o punto** como separador decimal.

### Estructura del proyecto

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
 
### Estructuras de datos utilizadas (ejemplos):

1. Estructuras de datos (`struct`).

   ```text
    typedef struct {
        double masa;                  
        double altitud;               
        double radio_orbital;          
        double fuerza_gravitatoria;   
        double fuerza_centripeta;      
        double velocidad_orbital;     
        double periodo_segundos;       
        double aceleracion_centripeta; 
    } NaveOrion;
   ```
   - Agrupa en una sola variable los datos físicos de la misión, guarda los datos de entrada (masa y altitud) y los resultados calculados (fuerzas, aceleración, velocidad, etc.). En vez de pasar variables sueltas a cada función, se pasa un solo puntero.

2. Punteros 

    ```text
     NaveOrion *nave (InicializarNave, CalcVelocidad, Calcperiodo, Calcaceleracion)
     ```
    - La función puede escribir resultados dentro de la nave original.

3. Arrelos (`array`)
   
   ```text
     char linea[TAM_LINEA]
     ```
   - Guarda lo que ingresa el usuario.

4. Constantes (`#define`)
   
   ```text
   #define EXCEN     0.0001      
   #define MAXTURNOS 5         
    ```
   - Ayudan establecer valores fijos.

5. Funciones y Procedimientos
   
      ```text
      Menu()
      InicializarNave(NaveOrion *nave)     
    ```
   - Menú Imprime las opciones.
   - Inicializar Nave Pide masa y altitud y calcula los valores iniciales.

6. Estructuras de control

   ```text
      if (fin != NULL) {                                  
            *fin = '\0';                                     
            while ((coma = strchr(linea, ',')) != NULL)      
                *coma = '.';                                 
            valor = strtod(linea, &fin);                   
            valido = strspn(linea, "0123456789+-.") == strlen(linea)  
                     && fin != linea && *fin == '\0'         
                     && valor >= minimo && valor <= maximo   
                     && (!soloEntero || valor == floor(valor));  
        } else {                                            
            while ((c = getchar()) != '\n' && c != EOF)      
                ; 
        }
    ```
- Valida el número ingresado por el usuario.
  
**Si la línea es corta (`if`):**
1. Quita el Enter del final.
2. Cambia las comas por puntos.
3. Convierte el texto a número con `strtod`.
4. Marca el dato como válido solo si:
   - contiene solamente dígitos, `+`, `-` o `.` .
   - no está vacío.
   - no sobra texto después del número.
   - está entre el mínimo y el máximo.
   - si se pide entero, no tiene decimales.

**Si la línea es demasiado larga (`else`):**
- Descarta lo que quedó sin leer en el buffer.

Si el dato no es válido, se muestra el error y se vuelve a pedir. 

### Instrucciones de compilación y ejecución:

1. Ingresar al repositorio en github.com (`Laboratorio-C`).
2. En el repositorio, clic en el botón verde $\color{green}{\text{Code}}$ → pestaña **Codespaces** → **Create codespace on main**.
3. Esperar a que cargue la terminal.
4. Una vez cargado, en la terminal escribir  `make                
                                              ./artemis` y darle al enter.

### Menú Principal:

```text
      SIMULADOR MISION ARTEMIS
      1. Cambiar altitud y masa
      2. Mostrar orbita LEO 
      3. Pulso lateral 
      4. Simulacion por turnos
      0. Salir
```

| opciones | Qué hace |
|--------|-----------------|
| `1` | Pide al usuario ingresaar nuevos datos de altitud y masa y recalcula todo |
| `2` | Muestra los resultados ya calculados de: la diferencia relativa de fg y fc, demostración de \(v^2 = \frac{G \cdot M_t}{r}\) y la velocidad orbital |
| `3` | Pide aceleraación y duración dentro de un rango, calcula el cambio de velocidad y muestra dv, desviación lateral y los elementos orbitales |
| `4` | Juego |
| `0` | Termina |

### - ¿Cómo funciona la simulación? ( `opcion 4` )

  El objetivo principal es dejar la órbita casi circular (con la excentricidad menor o igual a 0,0001) después de 5 turnos.

  ### En Cada turno:
   1. Una perturbación aleatoria (-5.00 a +5.00m/s) desvía la nave y se suma a la velocidad radial.
   2. Pide al jugador ingresar una acelereción de entre -2 a +2m/s² y una duración en segundos de 0 a 30s.
   3. El programa calcula dv = a.t y se suuma a la velocidad radial.
   4. El programa recalcula excentricidad, perigeo y apogeo y se guardan en el arreglo `tab[turno]`.
   5. Al finalizar los 5 turnos, se muestra un `reporte final` con el historial completo y si la misión fue exitosa o incompleta/fallida.

  Para poder ganar el juego, en el último turno la velocidad radial debe ser casi **cero**.
    

### Ejemplo de ejecución:

---

Registro del uso de Inteligencia Artificial:



   



