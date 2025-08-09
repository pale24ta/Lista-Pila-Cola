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

    cout<<"/nhola mundo";
    Lista<Lista<int>> lista;
    Lista<int> aux;
    aux.insertarEnPosicion(1,0);
    lista.insertarEnPosicion(aux,0);
    Lista<int> otra = lista.consultar(1);
    otra.imprimirLista();
    
    Lista<Cola<int>> listaCola;
    Cola<int> cola;
    cola.encolar(1);
    listaCola.insertarEnPosicion(cola,0);
    Cola<int> aux1;
    aux1 = listaCola.consultar(1);
    aux1.imprimirCola();

    return 0;
}
