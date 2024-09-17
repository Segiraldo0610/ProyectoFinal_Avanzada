#include "ProyectoFinal.h"
#include <iostream>
#include <fstream>  // Para manejar archivos
#include <cstdlib>  // Para usar la función std::rand y std::srand
#include <ctime>    // Para la semilla de la función std::srand

int main() {
    string nombre_archivo = "DS_Proyecto_01_Datos_Properati.csv"; // Nombre del archivo CSV
    string archivo_reporte = "reporte_analisis.txt"; // Nombre del archivo de reporte

    vector<Propiedad> propiedades = leerCSV(nombre_archivo);
    imprimirPropiedades(propiedades);

    if (!propiedades.empty()) {
        // Extraer variables para la regresión
        vector<double> numHabitaciones;
        vector<double> precios;

        for (auto&prop : propiedades) {
            numHabitaciones.push_back(prop.habitaciones);
            precios.push_back(prop.precio);
        }

        // Dividir los datos en conjunto de entrenamiento y prueba (80% entrenamiento,20% prueba)
        vector<double> habitaciones_entrenamiento, habitaciones_prueba;
        vector<double> precios_entrenamiento, precios_prueba;

        srand(static_cast<unsigned>(std::time(0))); // Inicializar la semilla aleatoria

        for (size_t i = 0; i < numHabitaciones.size(); ++i) {
            if (std::rand() % 100 < 80) {
                habitaciones_entrenamiento.push_back(numHabitaciones[i]);
                precios_entrenamiento.push_back(precios[i]);
            } else {
                habitaciones_prueba.push_back(numHabitaciones[i]);
                precios_prueba.push_back(precios[i]);
            }
        }


        

        // Ajustar el modelo de regresión lineal con el conjunto de entrenamiento
        ModeloRegresion modelo = ajustarModelo(habitaciones_entrenamiento, precios_entrenamiento);

        // Evaluar el modelo en el conjunto de entrenamiento
        double mse_entrenamiento = calcularMSE(habitaciones_entrenamiento, precios_entrenamiento, modelo);
        double r2_entrenamiento = calcularR2(habitaciones_entrenamiento, precios_entrenamiento, modelo);

        // Evaluar el modelo en el conjunto de prueba
        double mse_prueba = calcularMSE(habitaciones_prueba, precios_prueba, modelo);
        double r2_prueba = calcularR2(habitaciones_prueba, precios_prueba, modelo);

        // Guardar los resultados en un archivo de texto
        ofstream reporte(archivo_reporte);
        if (reporte.is_open()) {
            reporte << "Resultados en el conjunto de entrenamiento:" << endl;
            reporte << "Pendiente: " << modelo.pendiente << endl;
            reporte << "Intersección: " << modelo.interseccion << endl;
            reporte << "Error Cuadrático Medio (MSE): " << mse_entrenamiento << endl;
            reporte << "Coeficiente de Determinación (R²): " << r2_entrenamiento << endl;

            reporte << "\nResultados en el conjunto de prueba:" << endl;
            reporte << "Error Cuadrático Medio (MSE): " << mse_prueba << endl;
            reporte << "Coeficiente de Determinación (R²): " << r2_prueba << endl;

            // Análisis de los resultados
            reporte << "\nAnálisis de los resultados:" << endl;
            reporte << "El modelo parece ajustarse bien en el conjunto de entrenamiento, pero es importante comparar " 
                    << "los resultados del MSE y R² en el conjunto de prueba para evaluar su capacidad de generalización." << endl;

            if (r2_entrenamiento > r2_prueba) {
                reporte << "El modelo podría estar sobreajustado al conjunto de entrenamiento, lo que indica que su " 
                        << "rendimiento en datos no vistos (conjunto de prueba) es peor. Se podría considerar regularizar el modelo " 
                        << "o agregar más datos de entrenamiento para mejorar la generalización." << endl;
            } else {
                reporte << "El modelo parece tener una buena capacidad de generalización, pero siempre se puede investigar " 
                        << "más para ver si se pueden agregar más variables o mejorar el preprocesamiento de los datos." << endl;
            }

            reporte.close();
            cout << "El reporte ha sido guardado en " << archivo_reporte << endl;
        } else {
            cout << "No se pudo abrir el archivo para escribir el reporte." << endl;
        }

    } else {
        cout << "No se encontraron propiedades en el archivo." << endl;
    }

    return 0;
}
