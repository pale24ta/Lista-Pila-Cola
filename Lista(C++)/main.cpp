/*
IMPORTANTE: las posiciones comienzan en 0 por lo que las funciones como consultar o 
inseryar en la primera posicion serian insertarPorPosicion(0), para la primera funcion
las funciones que reciben una posicion como parametro convierten el parametro para que no 
sobrepasen los limite de la estructura
*/
#include<iostream>
#include<sstream> //para usar extracion ss
#include<string>
#include "cola.hpp"
#include "pila.hpp"
#include "lista.hpp"
#include "listaCircular.hpp"
#include  "listaCircDobEnlaz.hpp"
#include "listaDoble.hpp"

using namespace std;

int main(){

    Lista<int> totalCasos;
    Lista<Lista<string>> listaNombres;
    int numCasos, caso;
    cin >> numCasos;
    for (int i = 0; i < numCasos; i++){
        cin>>caso;
        totalCasos.insertarEnPosicion(caso, totalCasos.getLongitud());
    }
    //crear una lista de listas
    for (int i = 0; i < numCasos; i++){
        Lista<string> nombres;
        listaNombres.insertarEnPosicion(nombres, i);
    }
    cin.ignore();
    
    string linea;
    while (getline(cin,linea)){
        istringstream iss(linea);
        string dato;
        int indice=0;
        while (iss >> dato && indice < numCasos){
            listaNombres.consultar(indice).insertarEnPosicion(dato, listaNombres.consultar(indice).getLongitud());
            indice ++;
        }
    }
    for (int i = 0; i < numCasos; i++)
    {
        listaNombres.consultar(i).imprimirLista();
    }
    
    
    
    

    return 0;
}
