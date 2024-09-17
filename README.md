# Proyecto de Análisis de Datos del Mercado Inmobiliario

## Descripción

Este proyecto desarrolla una herramienta en C++ para analizar datos del mercado inmobiliario utilizando técnicas de **regresión lineal simple**. El objetivo es predecir el precio de una propiedad basado en una variable independiente (como el número de habitaciones o metros cuadrados). 

El proyecto incluye la implementación de un modelo de regresión lineal, así como un análisis exploratorio de datos (EDA) para comprender mejor las características del dataset proporcionado y optimizar el rendimiento del modelo.

## Requisitos

- **Lenguaje de Programación:** C++
- **Dataset:** `DS_Proyecto_01_Datos_Properati.csv` (disponible en Kaggle)
- **Librerías Necesarias:** Ninguna librería externa requerida, solo las estándar de C++.

## Instrucciones de Instalación y Ejecución

1. **Clonar el repositorio:**
   ```bash
   git clone https://github.com/tuusuario/nombre-del-proyecto.git
   cd nombre-del-proyecto
2. **Compilar el código:**
   Asegúrate de tener un compilador de C++ instalado (por ejemplo, g++).
   g++ -o analizadorInmobiliario main.cpp parser.cpp regresion.cpp -std=c++11
3. **Ejecutar el programa:**
   ./analizadorInmobiliario

## Resultados obtenidos

 1. Pendiente:
La pendiente del modelo significa que, según el modelo, por cada habitación adicional en una propiedad, el precio aumenta en aproximadamente (El valor de la pendiente) unidades de la moneda utilizada (por ejemplo, pesos argentinos si ese es el caso).
2. Intersección:
La intersección indica que, según el modelo, una propiedad sin habitaciones tendría un precio base de (El valor de la intersección) unidades de la moneda. Aunque este valor es teóricamente calculado, podría no tener sentido práctico (no es común que una propiedad no tenga habitaciones), pero es parte de cómo funciona el modelo lineal simple.
Evaluación del Modelo:
3. Error Cuadrático Medio (MSE):
El MSE mide la magnitud de los errores en las predicciones del modelo. Un error cuadrático medio de cientos de millones indica que las predicciones del modelo se desvían significativamente de los valores reales.
4. Coeficiente de Determinación (R²):
El R² mide qué tan bien el modelo explica la variabilidad de los datos. Un valor de R² cercano a 1 indica un buen ajuste, mientras que un valor cercano a 0 indica que el modelo no explica bien los datos.
