//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
// Author      : Teófilo Rojas Mata
// Version     :
// Copyright   : Universidad de Córdoba
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // Para coger la hora time()
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <string.h>
#include <math.h>
#include "imc/PerceptronMulticapa.h"

using namespace imc;
using namespace std;

int main(int argc, char **argv) {

    // Procesar la línea de comandos
    bool tflag = false;
    char *tvalue = NULL , *Tvalue = NULL;
    int i=0, l=0, h=0, b=0;
    float eta=0.0, mu=0.0;
    int c;    
    // ....

    // Leer iteraciones, capas y neuronas desde la línea de comandos

    // Leer sesgo, eta y mu de la línea desde comandos

    // Leer fichero de train y de test desde la línea de comandos

    PerceptronMulticapa mlp;

    Datos * pDatosTrain = mlp.leerDatos(tvalue);
    Datos * pDatosTest = mlp.leerDatos(Tvalue);

    // Inicializar el vector "topología"
    // (número de neuronas por cada capa, incluyendo la de entrada
    //  y la de salida)
    // ...

    // Sesgo
    mlp.bSesgo = bflag;

    // Eta
    mlp.dEta = eta;

    // Mu
    mlp.dMu = mu;

    // Inicialización propiamente dicha
    mlp.inicializar(numCapas+2,topologia);

    // Semilla de los números aleatorios
    int semillas[] = {10,20,30,40,50};
    double *erroresTest = new double[5];
    double *erroresTrain = new double[5];
    for(int i=0; i<5; i++){
        srand(semillas[i]);
    	cout << "**********" << endl;
    	cout << "SEMILLA " << semillas[i] << endl;
    	cout << "**********" << endl;
        mlp.ejecutarAlgoritmoOnline(pDatosTrain,pDatosTest,iteraciones,&(erroresTrain[i]),&(erroresTest[i]));
		cout << "Finalizamos => Error de test final: " << erroresTest[i] << endl;
    }

    cout << "HEMOS TERMINADO TODAS LAS SEMILLAS" << endl;

    // Calcular media y desviación típica de los errores de Train y de Test
    // ....

    cout << "INFORME FINAL" << endl;
    cout << "*************" << endl;
    cout << "Error de entrenamiento (Media +- DT): " << mediaErrorTrain << " +- " << desviacionTipicaErrorTrain << endl;
    cout << "Error de test (Media +- DT):          " << mediaErrorTest << " +- " << desviacionTipicaErrorTest << endl;
    return EXIT_SUCCESS;
}

