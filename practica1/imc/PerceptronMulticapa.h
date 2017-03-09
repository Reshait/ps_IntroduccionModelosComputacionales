/*********************************************************************
 * File  : PerceptronMulticapa.cpp
 * Date  : 2016
 *********************************************************************/


#ifndef _PERCEPTRONMULTICAPA_H_
#define _PERCEPTRONMULTICAPA_H_

#include <vector>

using std::vector;
using namespace std;

namespace imc{

// Estructuras sugeridas
// ---------------------
struct Neurona {
	double  x;            /* Salida producida por la neurona (out_j^h)*/
	double  dX;           /* Derivada de la salida producida por la neurona (delta_j)*/
	vector <double> vW;            /* Vector de pesos de entrada (w_{ji}^h)*/
	vector <double> vDeltaW;       /* Cambio a aplicar a cada peso de entrada (\Delta_{ji}^h (t))*/
	vector <double> vUltimoDeltaW; /* Último cambio aplicada a cada peso (\Delta_{ji}^h (t-1))*/
	vector <double> vW_Copia;       /* Copia de los pesos de entrada */
};


//struct Capa {
//	vector <Neurona> vNeuronas;     /* Vector con las neuronas de la capa*/
//};

struct Datos {
//	int nEntradas;     /* Número de entradas */
//	int nSalidas;      /* Número de salidas */
	int nPatrones;     /* Número de patrones */
	vector< vector<double> > mEntradas;    /* Matriz con las entradas del problema */
	vector< vector<double> > vSalidas;     /* Matriz con las salidas del problema */
};

class PerceptronMulticapa {
private:
//	int    nNumCapas;     /* Número de capas total en la red */
	vector< vector<Neurona> > _vRed;         /* pCapas Vector con cada una de las capas */

	// Liberar memoria para las estructuras de datos
	void liberarMemoria();

	// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
	void pesosAleatorios(Neurona &N);

	// Alimentar las neuronas de entrada de la red con un patrón pasado como argumento
	void alimentarEntradas(vector <double> &vEntrada);

	// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
	void recogerSalidas(vector <double> &vSalida);

	// Hacer una copia de todos los pesos (copiar w en copiaW)
	void copiarPesos();

	// Restaurar una copia de todos los pesos (copiar copiaW en w)
	void restaurarPesos();

	// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
	void propagarEntradas();

	// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
	double calcularErrorSalida(vector <double>& target);

	// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
	void retropropagarError(vector <double>& objetivo);

	// Acumular los cambios producidos por un patrón en deltaW
//	void acumularCambio();

	// Actualizar los pesos de la red, desde la primera capa hasta la última
//	void ajustarPesos();

	// Imprimir la red, es decir, todas las matrices de pesos
//	void imprimirRed();

	// Simular la red: propagar las entradas hacia delante, retropropagar el error y ajustar los pesos
	// entrada es el vector de entradas del patrón y objetivo es el vector de salidas deseadas del patrón
//	void simularRedO_nCapasine(vector <double> entrada, vector <double> objetivo);


public:
	// Valores de parámetros (son públicos, para que puedan ser actualizados desde fuera)
	double _dEta;        // Tasa de aprendizaje
	double _dMu;         // Factor de momento
	bool   _bSesgo;      // ¿Van a tener sesgo las neuronas?
	int _nCapas;

	// CONSTRUCTOR: Dar valor por defecto a todos los parámetros
	PerceptronMulticapa();

	// DESTRUCTOR: liberar memoria
	~PerceptronMulticapa();

	// Reservar memoria para las estructuras de datos
    // _nCapas tiene el numero de capas y vNeuronasPorCapa es un vector que contiene el número de neuronas por cada una de las capas
    // Rellenar vector Capa* pCapas
	int inicializar(int _nCapas, vector <int> &vNeuronasPorCapa);

	void aniadeCapa(vector <Neurona> &vCapa){
		_vRed.push_back(vCapa);
	}

	// Leer una matriz de datos a partir de un nombre de fichero y devolverla
	vector <Datos> leerDatos(const char *archivo);

	// Entrenar la red on-line para un determinado fichero de datos
	void entrenarO_nCapasine(vector <Datos> & pDatosTrain);

	// Probar la red con un conjunto de datos y devolver el error MSE cometido
	double test(vector <Datos> & pDatosTest);

	// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatosTrain
    // Una vez terminado, probar como funciona la red en pDatosTest
    // Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
	void ejecutarAlgoritmoO_nCapasine(vector <Datos> & vDatosTrain, vector <Datos> & vDatosTest, int maxiter, vector <double> vErrorTrain, vector <double> vErrorTest);

};

};

#endif
