#ifndef PROYECTOFINAL_H
#define PROYECTOFINAL_H
#include <string>
#include <vector>

using namespace std;

// Definición de la estructura Propiedad
struct Propiedad {
    string fecha_inicio;      // Fecha de inicio
    string fecha_fin;         // Fecha de fin
    string fecha_creacion;    // Fecha de creación
    double latitud;           // Latitud
    double longitud;          // Longitud
    string ubicacion_nivel1;  // Primer nivel de ubicación
    string ubicacion_nivel2;  // Segundo nivel de ubicación
    string ubicacion_nivel3;  // Tercer nivel de ubicación
    double habitaciones;      // Número total de habitaciones
    double dormitorios;       // Número de dormitorios
    double banos;             // Número de baños
    double superficie_total;  // Superficie total
    double superficie_cubierta; // Superficie cubierta
    double precio;            // Precio
    string moneda;            // Moneda
    string descripcion;       // Descripción del anuncio
    string tipo_propiedad;    // Tipo de propiedad
    string tipo_operacion;    // Tipo de operación
};

// Definición de la estructura ModeloRegresion
struct ModeloRegresion {
    double pendiente;
    double interseccion;
};

// Funciones declaradas
vector<Propiedad> leerCSV(const string& nombre_archivo);
void imprimirPropiedades(const vector<Propiedad>& propiedades);
ModeloRegresion ajustarModelo(const vector<double>& x, const vector<double>& y);
double predecir(const ModeloRegresion& modelo, double x);
double calcularMSE(const vector<double>& x, const vector<double>& y, const ModeloRegresion& modelo);
double calcularR2(const vector<double>& x, const vector<double>& y, const ModeloRegresion& modelo);

#endif // PROYECTOFINAL_H