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

    ListaCircularDoble<int> lista, otra;
    for (int i = 0; i < 5; i++)
    {
        lista.insertarEnPosicion(i,i);
    }
    
    otra = lista;
    cout<<endl<<otra.getLongitud()<<" "<<lista.getLongitud()<<endl;

    if(otra==lista)
        cout<<"\nlistas iguales\n";
    else
        cout<<"no iguales"<<endl;
    

    return 0;
}
