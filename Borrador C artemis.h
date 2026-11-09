       //constantes
#define G   6.674e-11        //gravitacion universal [N.m2/kg2]
#define MT  5.972e24         //masa de la Tierra [kg] 
#define RT  6371000.0        //radio medio de la Tierra [m] 
#define PI  3.141592653589793
     // Datos de la prbita circular
typedef struct {
    double altitudKm;              //h [km]  (entrada)
    double masa;                   //m [kg]  (entrada) 
    double radioOrbital;           //r = RT + h [m] 
    double fuerzaGravitatoria;     // Fg [N] 
    double fuerzaCentripeta;       //Fc [N]  (para demostrar q Fg = Fc) 
    double velocidadOrbital;       // v [m/s]
    double periodoSegundos;        // T [s] 
    double aceleracionCentripeta;  // ac [m/s2] 
} DatosOrbita;

  void calcula_Or(DatosOrbita *datos);
  void conf_par(DatosOrbita *datos);
  void muestra_result(const DatosOrbita *datos);
  void eltos(double r, double vr, double vt, Elementos *elem);
  void mostrar_eltos(Elementos elem);
  void pulso_lateral(const DatosOrbita *datos);
  void simulaJ(const DatosOrbita *datos);

#endif
