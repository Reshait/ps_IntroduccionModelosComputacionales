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

void PerceptronMulticapa::pesosAleatorios() {
	for(int i = 1; i < _mRed.size(); i++){
		for(int j = 1; j < _mRed[i].size(); j++){
			
			for(int k = 0; k < _mRed[i-1].size(); k++)
				_mRed[i][j].vW[k] = realAleatorio(-1,1);

			if(_bSesgo)
				_mRed[i][j].vW[_mRed[i-1].size()] = realAleatorio(-1,1);
			
		}
	}
}

// ------------------------------
// Alimentar las neuronas de vEntrada de la red con un patrón pasado como argumento
void PerceptronMulticapa::alimentarEntradas(vector <double> &vEntrada) {

	vector <Neurona> vCapa0;
	Neurona Naux;

	for(int i = 0; i < _mRed[0].size(); i++){
		Naux.x = vEntrada[i];
		vCapa0.push_back(Naux);
	}

	_mRed.push_back(vCapa0);
}

void PerceptronMulticapa::alimentarEntradas(double patron) {

	vector <Neurona> vCapa0;
	Neurona Naux;

	for(int i = 0; i < _mRed[0].size(); i++){
		Naux.x = patron;
		 vCapa0.push_back(Naux);
	}

	_mRed.push_back(vCapa0);
}

// ------------------------------
// Liberar memoria para las estructuras de datos
void PerceptronMulticapa::liberarMemoria() {
	_mRed.clear();
}

// ------------------------------
// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
void PerceptronMulticapa::recogerSalidas(vector <double> &vSalida) {
	for(int i = 0; i < _mRed[_mRed.size()-1].size(); i++){
		vSalida.push_back(_mRed[_mRed.size()-1][i].x);
	}
}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos() {
	for(int i = 0; i < _mRed.size(); i++){
		for(int j = 0; j < _mRed[i].size(); j++){
				_mRed[i][j].vW_Copia = _mRed[i][j].vW;
			}
		}
}

// ------------------------------
// Restaurar una copia de todos los pesos (copiar copiaW en w)
void PerceptronMulticapa::restaurarPesos() {
	for(int i = 0; i < _mRed.size(); i++){
		for(int j = 0; j < _mRed[i].size(); j++){
				_mRed[i][j].vW = _mRed[i][j].vW_Copia;
			}
		}
}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
void PerceptronMulticapa::propagarEntradas() {
	double net;

	for(int i = 1; i < _mRed.size(); i++){
		for(int j = 0; j < _mRed[i].size(); j++){
			net = 0.0;

			for(int k = 0; k < _mRed[i-1].size(); k++){
				net += _mRed[i][j].vW[k] * _mRed[i-1][k].x;
			}

			if(_bSesgo)
				net += _mRed[i][j].vW[i-1];

			_mRed[i][j].x = (1 / (1 + exp(-net)));
		}
	}
}

// ------------------------------
// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
double PerceptronMulticapa::calcularErrorSalida(vector <double>& target) {
	double error = 0.0;

	for(int i = 0; i < _mRed[_mRed.size()-1].size(); i++){
		error += pow( _mRed[_mRed.size()-1][i].x - target[i], 2);
	}

	return error / _mRed[_mRed.size()-1].size(); // Número de neuronas en la penúltima capa
}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
void PerceptronMulticapa::retropropagarError(vector <double>& objetivo) {
	for(int i = 0; i < _mRed[_mRed.size()-1].size(); i++){
		double salida = _mRed[_mRed.size()-1][i].x;
		_mRed[_mRed.size()-1][i].dX = (-1 * (objetivo[i] - salida) * salida * (1-salida));
	}

	for(int i = _mRed.size()-1; i > -1; i--){
		for(int j = 0; j < _mRed[i].size(); j++){
			double aux = 0.0;
			
			for(int k = 0; k < _mRed[i+1].size(); k++){
				aux += _mRed[i+1][k].vW[j] * _mRed[i+1][k].dX;
			}

			double sal = _mRed[i][j].x;
			_mRed[i][j].dX = aux * sal * (1 - sal);
		}
	}
}

// ------------------------------
// Acumular los cambios producidos por un patrón en deltaW
void PerceptronMulticapa::acumularCambio() {
	for(int i = 1; i < _mRed.size(); i++){
		for(int j = 0; j < _mRed[i].size(); j++){
			
			for(int k = 0; k < _mRed[i-1].size(); k++){
				_mRed[i][j].vDeltaW[k] += _mRed[i][j].dX * _mRed[i-1][k].x;
			}
			
			if(_bSesgo){
				_mRed[i][j].vDeltaW[_mRed[i-1].size()] += _mRed[i][j].dX; 
			}
		}
	}
}

// ------------------------------
// Actualizar los pesos de la red, desde la primera capa hasta la última
void PerceptronMulticapa::ajustarPesos() {
	for(int i = 1; i < _mRed.size(); i++){
		for(int j = 0; j < _mRed[i].size(); j++){
			
			for(int k = 0; k < _mRed[i-1].size(); k++){
				_mRed[i][j].vW[k] += -_dEta * _mRed[i][j].vDeltaW[k] - _dMu * (_dEta * _mRed[i][j].vUltimoDeltaW[k]);
			}

			if(_bSesgo){
				_mRed[i][j].vW[_mRed[i-1].size()] += -_dEta * _mRed[i][j].vDeltaW[_mRed[i-1].size()] - _dMu * (_dEta * _mRed[i][j].vUltimoDeltaW[_mRed[i-1].size()]);
			}
		}
	}
}

// ------------------------------
// Imprimir la red, es decir, todas las matrices de pesos
void PerceptronMulticapa::imprimirRed() {
	for(int i = 1; i < _mRed.size(); i++){
		for(int j = 0; j < _mRed[i].size(); j++){
			if(_bSesgo)
				cout << _mRed[i][j].vW[_mRed[i-1].size()] << " ";

			for(int k = 0; k < _mRed[i-1].size(); k++)
				cout << _mRed[i][j].vW[k] << " ";

			cout << endl;
		}
	}
}

// ------------------------------
// Simular la red: propagar las entradas hacia delante, computar el error, retropropagar el error y ajustar los pesos
// vEntrada es el vector de entradas del patrón y vObjetivo es el vector de salidas deseadas del patrón
void PerceptronMulticapa::simularRedOnline(vector <double>& vEntrada, vector <double>& vObjetivo) {
	for(int i = 1; i < _mRed.size(); i++){
		for(int j = 0; j < _mRed[i].size(); j++){
			for(int k = 0; k < _mRed[i-1].size(); k++){
				_mRed[i][j].vUltimoDeltaW[k] = _mRed[i][j].vDeltaW[k];
				_mRed[i][j].vDeltaW[k] = 0;
			}
		}
	}

	alimentarEntradas(vEntrada);
	propagarEntradas();
	retropropagarError(vObjetivo);
	acumularCambio();
	ajustarPesos();
}

// ------------------------------
// Leer una matriz de datos a partir de un nombre de fichero y devolverla
Datos& PerceptronMulticapa::leerDatos(const char *fichero) {

	fstream f;
	Datos D;
	double aux;

	f.open(fichero);

	f >> D.nEntradas >> D.nSalidas >> D.nPatrones;

	for(int i = 0; i < D.nPatrones; i++){

		for(int j = 0; j < D.nEntradas; j++){
			f >> aux;
			D.vEntradas.push_back(aux);
		}

		for(int j = 0; j < D.nSalidas; j++){
			f >> aux;
			D.vSalidas.push_back(aux);
		}

	}

	f.close();

	return D;
}

// ------------------------------
// Entrenar la red on-line para un determinado fichero de datos
void PerceptronMulticapa::entrenarOnline(Datos& D) {
	int i;
	//for(i=0; i < D.nPatrones; i++)
		simularRedOnline(D.vEntradas, D.vSalidas);
}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error MSE cometido
double PerceptronMulticapa::test(Datos& Dtest) {
	int i;
	double dAvgTestError = 0;
	for(i = 0; i < Dtest.nPatrones; i++){
		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(Dtest.vEntradas[i]);
		propagarEntradas();
		dAvgTestError += calcularErrorSalida(Dtest.vSalidas);
	}
	dAvgTestError /= Dtest.nPatrones;
	return dAvgTestError;
}


// ------------------------------
// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando Dtrain
// Una vez terminado, probar como funciona la red en Dtest
// Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
void PerceptronMulticapa::ejecutarAlgoritmoOnline(Datos& Dtrain, Datos& Dtest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;

	// Inicialización de pesos
	pesosAleatorios();

	double minTrainError = 0;
	int numSinMejorar;
	double testError = 0;

	// Aprendizaje del algoritmo
	do {

		entrenarOnline(Dtrain);
		double trainError = test(Dtrain);
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
	for(int i = 0; i < Dtest.nPatrones; i++){
		vector <double> prediccion;

		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(Dtest.vEntradas[i]);
		propagarEntradas();
		recogerSalidas(prediccion);
		for(int j=0; j<Dtest.nSalidas; j++)
			cout << Dtest.vSalidas[i][j] << " -- " << prediccion[j];
		cout << endl;
		prediccion.clear();

	}

	testError = test(Dtest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}


