#include "ProyectoFinal.h"
#include <fstream>
#include <sstream>
#include <iostream>


// Función para leer el CSV y almacenar los datos en un vector de Propiedad
vector<Propiedad> leerCSV(const string& nombre_archivo) {
    ifstream archivo(nombre_archivo);
    vector<Propiedad> propiedades;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return propiedades;
    }

    string linea;
    getline(archivo, linea); // Leer la primera línea (cabecera)

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Propiedad prop;

        getline(ss, prop.fecha_inicio, ',');
        getline(ss, prop.fecha_fin, ',');
        getline(ss, prop.fecha_creacion, ',');
        ss >> prop.latitud; ss.ignore(); // Ignorar la coma
        ss >> prop.longitud; ss.ignore(); // Ignorar la coma
        getline(ss, prop.ubicacion_nivel1, ',');
        getline(ss, prop.ubicacion_nivel2, ',');
        getline(ss, prop.ubicacion_nivel3, ',');
        ss >> prop.habitaciones; ss.ignore(); // Ignorar la coma
        ss >> prop.dormitorios; ss.ignore(); // Ignorar la coma
        ss >> prop.banos; ss.ignore(); // Ignorar la coma
        ss >> prop.superficie_total; ss.ignore(); // Ignorar la coma
        ss >> prop.superficie_cubierta; ss.ignore(); // Ignorar la coma
        ss >> prop.precio; ss.ignore(); // Ignorar la coma
        getline(ss, prop.moneda, ',');
        getline(ss, prop.descripcion, ',');
        getline(ss, prop.tipo_propiedad, ',');
        getline(ss, prop.tipo_operacion);

        propiedades.push_back(prop);
    }

    archivo.close();
    return propiedades;
}

// Función para imprimir la información de las propiedades
void imprimirPropiedades(const vector<Propiedad>& propiedades) {
    for (const auto& prop : propiedades) {
        cout << "Fecha de inicio: " << prop.fecha_inicio << endl;
        cout << "Fecha de fin: " << prop.fecha_fin << endl;
        cout << "Fecha de creación: " << prop.fecha_creacion << endl;
        cout << "Latitud: " << prop.latitud << ", Longitud: " << prop.longitud << endl;
        cout << "Ubicación: " << prop.ubicacion_nivel1 << ", " << prop.ubicacion_nivel2 << ", " << prop.ubicacion_nivel3 << endl;
        cout << "Habitaciones: " << prop.habitaciones << ", Dormitorios: " << prop.dormitorios << ", Baños: " << prop.banos << endl;
        cout << "Superficie total: " << prop.superficie_total << ", Superficie cubierta: " << prop.superficie_cubierta << endl;
        cout << "Precio: " << prop.precio << " " << prop.moneda << endl;
        cout << "Descripción: " << prop.descripcion << endl;
        cout << "Tipo de propiedad: " << prop.tipo_propiedad << endl;
        cout << "Tipo de operación: " << prop.tipo_operacion << endl;
        cout << "-----------------------------" << endl;
    }
}

// Función para ajustar el modelo de regresión lineal
ModeloRegresion ajustarModelo(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double sumaX = 0, sumaY = 0, sumaXY = 0, sumaX2 = 0;

    for (int i = 0; i < n; ++i) {
        sumaX += x[i];
        sumaY += y[i];
        sumaXY += x[i] * y[i];
        sumaX2 += x[i] * x[i];
    }

    double pendiente, interseccion;
    double denominador = n * sumaX2 - sumaX * sumaX;

    if (denominador != 0) {
        pendiente = (n * sumaXY - sumaX * sumaY) / denominador;
        interseccion = (sumaY - pendiente * sumaX) / n;
    } else {
        cerr << "Error: no se puede ajustar un modelo de regresión lineal, divisor es cero." << endl;
        pendiente = 0; // Otras estrategias podrían ser utilizadas aquí
        interseccion = 0;
    }


    return { pendiente, interseccion };
}

// Función para hacer una predicción con el modelo de regresión lineal
double predecir(const ModeloRegresion& modelo, double x) {
    return modelo.pendiente * x + modelo.interseccion;
}

// Función para calcular el error cuadrático medio (MSE)
double calcularMSE(const vector<double>& x, const vector<double>& y, const ModeloRegresion& modelo) {
    double mse = 0;
    int n = x.size();

    for (int i = 0; i < n; ++i) {
        double prediccion = predecir(modelo, x[i]);
        mse += (prediccion - y[i]) * (prediccion - y[i]);
    }


        return mse / n;


}

// Función para calcular el coeficiente de determinación (R²)
double calcularR2(const vector<double>& x, const vector<double>& y, const ModeloRegresion& modelo) {
    double media_y = 0;
    int n = y.size();

    for (int i = 0; i < n; ++i) {
        media_y += y[i];
    }
    media_y /= n;

    double ss_total = 0, ss_residual = 0;

    for (int i = 0; i < n; ++i) {
        double prediccion = predecir(modelo, x[i]);
        ss_total += (y[i] - media_y) * (y[i] - media_y);
        ss_residual += (y[i] - prediccion) * (y[i] - prediccion);
    }


        return 1 - (ss_residual / ss_total);

    }