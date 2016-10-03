/*********************************************************************
 * File  : PerceptronMulticapa.cpp
 * Date  : 2016
 *********************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <math.h>

#include "PerceptronMulticapa.h"

using namespace imc;
using namespace std;

// ------------------------------
// Obtener un número real aleatorio en el intervalo [Low,High]
double realAleatorio(double Low, double High)
{
	double aleatorio = ((double) rand() / RAND_MAX)*(High-Low) + Low;
	return aleatorio;
}

// ------------------------------
// CONSTRUCTOR: Dar valor por defecto a todos los parámetros
PerceptronMulticapa::PerceptronMulticapa()
{
	nNumCapas = 3;
	pCapas = NULL;
	dEta = 0.1;
	dMu = 0.9;
	bSesgo = true;
}

// Reservar memoria para las estructuras de datos
// nl tiene el numero de capas y npl es un vector que contiene el número de neuronas por cada una de las capas
// Rellenar vector Capa* pCapas
int PerceptronMulticapa::inicializar(int nl, int npl[]) {

}


// ------------------------------
// DESTRUCTOR: liberar memoria
PerceptronMulticapa::~PerceptronMulticapa() {
	liberarMemoria();
}


// ------------------------------
// Liberar memoria para las estructuras de datos
void PerceptronMulticapa::liberarMemoria() {

	for(int capas = 0; capas < nNumCapas; capas++)
	{
		for(int neuronas = 0; neuronas < pCapas[capas].nNumNeuronas; neuronas++)
		{
			delete [] pCapas[capas].pNeuronas[neuronas].deltaW;
			delete [] pCapas[capas].pNeuronas[neuronas].ultimoDeltaW;
			delete [] pCapas[capas].pNeuronas[neuronas].w;
			delete [] pCapas[capas].pNeuronas[neuronas].wCopia;
		}
		delete [] pCapas[capas].pNeuronas;
	}
	delete [] pCapas;
}

// ------------------------------
// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
void PerceptronMulticapa::pesosAleatorios() {
	//Añadiendo a la capa sus neuronas y pesos
	//poner los pesos aleatorios entre -1 y 1

	double aleatorio = 0.0;

	for(int i = 1; i<nNumCapas; i++)
	{
		for(int j = 0; j<pCapas[i].nNumNeuronas; j++)
		{
			for(int k = 0; k<pCapas[i-1].nNumNeuronas+bSesgo; k++)
			{
				aleatorio = realAleatorio(-1,1);
				pCapas[i].pNeuronas[j].w[k]=valor;
			}
		}
	}	
}

// ------------------------------
// Alimentar las neuronas de entrada de la red con un patrón pasado como argumento
void PerceptronMulticapa::alimentarEntradas(double* input) {

}

// ------------------------------
// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
void PerceptronMulticapa::recogerSalidas(double* output) {

}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos() {

}

// ------------------------------
// Restaurar una copia de todos los pesos (copiar copiaW en w)
void PerceptronMulticapa::restaurarPesos() {

}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
void PerceptronMulticapa::propagarEntradas() {

}

// ------------------------------
// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
double PerceptronMulticapa::calcularErrorSalida(double* target) {

}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
void PerceptronMulticapa::retropropagarError(double* objetivo) {

}

// ------------------------------
// Acumular los cambios producidos por un patrón en deltaW
void PerceptronMulticapa::acumularCambio() {

}

// ------------------------------
// Actualizar los pesos de la red, desde la primera capa hasta la última
void PerceptronMulticapa::ajustarPesos() {

}

// ------------------------------
// Imprimir la red, es decir, todas las matrices de pesos
void PerceptronMulticapa::imprimirRed() {

}

// ------------------------------
// Simular la red: propagar las entradas hacia delante, computar el error, retropropagar el error y ajustar los pesos
// entrada es el vector de entradas del patrón y objetivo es el vector de salidas deseadas del patrón
void PerceptronMulticapa::simularRedOnline(double* entrada, double* objetivo) {

}

// ------------------------------
// Leer una matriz de datos a partir de un nombre de fichero y devolverla
Datos* PerceptronMulticapa::leerDatos(const char *archivo) {

}

// ------------------------------
// Entrenar la red on-line para un determinado fichero de datos
void PerceptronMulticapa::entrenarOnline(Datos* pDatosTrain) {
	int i;
	for(i=0; i<pDatosTrain->nNumPatrones; i++)
		simularRedOnline(pDatosTrain->entradas[i], pDatosTrain->salidas[i]);
}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error MSE cometido
double PerceptronMulticapa::test(Datos* pDatosTest) {
	int i;
	double dAvgTestError = 0;
	for(i=0; i<pDatosTest->nNumPatrones; i++){
		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		dAvgTestError += calcularErrorSalida(pDatosTest->salidas[i]);
	}
	dAvgTestError /= pDatosTest->nNumPatrones;
	return dAvgTestError;
}

// ------------------------------
// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatosTrain
// Una vez terminado, probar como funciona la red en pDatosTest
// Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
void PerceptronMulticapa::ejecutarAlgoritmoOnline(Datos * pDatosTrain, Datos * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;

	// Inicialización de pesos
	pesosAleatorios();

	double minTrainError = 0;
	int numSinMejorar;
	double testError = 0;

	// Aprendizaje del algoritmo
	do {

		entrenarOnline(pDatosTrain);
		double trainError = test(pDatosTrain);
		// El 0.00001 es un valor de tolerancia, podría parametrizarse
		if(countTrain==0 || fabs(trainError - minTrainError) > 0.00001){
			minTrainError = trainError;
			copiarPesos();
			numSinMejorar = 0;
		}
		else{
			numSinMejorar++;
		}

		if(numSinMejorar==50){
			restaurarPesos();
			countTrain = maxiter;
		}

		countTrain++;

		cout << "Iteración " << countTrain << "\t Error de entrenamiento: " << trainError << endl;

	} while ( countTrain<maxiter );

	cout << "PESOS DE LA RED" << endl;
	cout << "===============" << endl;
	imprimirRed();

	cout << "Salida Esperada Vs Salida Obtenida (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nNumPatrones; i++){
		double* prediccion = new double[pDatosTest->nNumSalidas];

		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(prediccion);
		for(int j=0; j<pDatosTest->nNumSalidas; j++)
			cout << pDatosTest->salidas[i][j] << " -- " << prediccion[j];
		cout << endl;
		delete[] prediccion;

	}

	testError = test(pDatosTest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}
