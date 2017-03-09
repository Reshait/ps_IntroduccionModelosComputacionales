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
#include <vector>

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
	_nCapas = 3;
	_dEta = 0.1;
	_dMu = 0.9;
	_bSesgo = true;
}

// ------------------------------
// Reservar memoria para las estructuras de datos
// nCapas tiene el numero de capas y vNeuronasPorCapa es un vector que contiene el número de neuronas por cada una de las capas
// Rellenar vector Capa* pCapas
int PerceptronMulticapa::inicializar(int nCapas, vector <int> &vNeuronasPorCapa) {
	vector <Neurona> vCapa;
	Neurona Naux;

	Naux.x = 0.0;
	Naux.dX = 0.0;

	for(int i = 0; i < vNeuronasPorCapa[i]; i++)
		Naux.vW_Copia.push_back(vNeuronasPorCapa[i] + _bSesgo);

	if(nCapas > 3)
		_nCapas = nCapas;

	for(int i = 0; i < _nCapas; i++){

		for(int j = 0; j < vNeuronasPorCapa[i]; j++){
			PerceptronMulticapa::pesosAleatorios(Naux);
			vCapa.push_back(Naux);
		}

		PerceptronMulticapa::aniadeCapa(vCapa);
		vCapa.clear();
	}

	return 1;
}

// ------------------------------
// DESTRUCTOR: liberar memoria
PerceptronMulticapa::~PerceptronMulticapa() {
	liberarMemoria();
}

// ------------------------------
// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
void PerceptronMulticapa::pesosAleatorios(Neurona &N) {
	//poner los pesos aleatorios entre -1 y 1
		double aux = realAleatorio(-1,1);
		N.vW.push_back(aux); 
		N.vW_Copia.push_back(aux);
}

// ------------------------------
// Alimentar las neuronas de vEntrada de la red con un patrón pasado como argumento
void PerceptronMulticapa::alimentarEntradas(vector <double> &vEntrada) {

	vector <Neurona> vCapa0;
	Neurona Naux;

	for(int i = 0; i < _vRed[0].size(); i++){
		Naux.x = vEntrada[i];
		Naux.dX = vEntrada[i];
		 vCapa0.push_back(Naux);
	}

	_vRed.push_back(vCapa0);
}

// ------------------------------
// Liberar memoria para las estructuras de datos
void PerceptronMulticapa::liberarMemoria() {
	_vRed.clear();
}

// ------------------------------
// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
void PerceptronMulticapa::recogerSalidas(vector <double> &vSalida) {
	for(int i = 0; i < _vRed[_vRed.size()-1].size(); i++){
		vSalida.push_back(_vRed[_vRed.size()-1][i].x);
	}
}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos() {
	for(int i = 0; i < _vRed.size(); i++){
		for(int j = 0; j < _vRed[i].size(); j++){
				_vRed[i][j].vW_Copia = _vRed[i][j].vW;
			}
		}
}

// ------------------------------
// Restaurar una copia de todos los pesos (copiar copiaW en w)
void PerceptronMulticapa::restaurarPesos() {
	for(int i = 0; i < _vRed.size(); i++){
		for(int j = 0; j < _vRed[i].size(); j++){
				_vRed[i][j].vW = _vRed[i][j].vW_Copia;
			}
		}
}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
void PerceptronMulticapa::propagarEntradas() {
	double net;

	for(int i = 1; i < _vRed.size(); i++){
		for(int j = 0; j < _vRed[i].size(); j++){
			net = 0.0;

			for(int k = _bSesgo; k < _vRed[i-1].size() + _bSesgo; k++){
				net += _vRed[i][j].vW[k] * _vRed[i-1][k - _bSesgo].x;
			}

			if(_bSesgo)
				net += _vRed[i][j].vW[0];

			_vRed[i][j].x = (1 / (1 + exp(-net)));
		}
	}
}
/*========================= Poco a poco joder





// ------------------------------
// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
double PerceptronMulticapa::calcularErrorSalida(vector <double> target) {

}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
void PerceptronMulticapa::retropropagarError(vector <double> objetivo) {

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
// vEntrada es el vector de entradas del patrón y objetivo es el vector de salidas deseadas del patrón
void PerceptronMulticapa::simularRedOnCapasine(vector <double> vEntrada, vector <double> objetivo) {

}

// ------------------------------
// Leer una matriz de datos a partir de un nombre de fichero y devolverla
Datos* PerceptronMulticapa::leerDatos(const char *archivo) {

}

// ------------------------------
// Entrenar la red on-line para un determinado fichero de datos
void PerceptronMulticapa::entrenarOnCapasine(vector <Datos> pDatosTrain) {
	int i;
	for(i=0; i<pDatosTrain->nNumPatrones; i++)
		simularRedOnCapasine(pDatosTrain->entradas[i], pDatosTrain->salidas[i]);
}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error MSE cometido
double PerceptronMulticapa::test(vector <Datos> pDatosTest) {
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
void PerceptronMulticapa::ejecutarAlgoritmoOnCapasine(vector <Datos> pDatosTrain, vector <Datos> pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;

	// Inicialización de pesos
	pesosAleatorios();

	double minTrainError = 0;
	int numSinMejorar;
	double testError = 0;

	// Aprendizaje del algoritmo
	do {

		entrenarOnCapasine(pDatosTrain);
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
		vector <double> prediccion = new double[pDatosTest->nNumSalidas];

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

FIN Poco a poco joder ======================*/

