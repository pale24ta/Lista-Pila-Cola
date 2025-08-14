#include<iostream>
#include <sstream>
#include <vector>
#include <string>
#include "lista.hpp"
#include "cola.hpp"
// #include "listaCircle.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;


int main(){
	int i,j;
	int input;
	Lista<Lista<int>> numeros;

	string leerLinea;
	while(getline(cin,leerLinea)){
		
		istringstream flujo(leerLinea);
		numeros.insertar(Lista<int>(),1); 

		while(flujo>>input){
			numeros.consultar(1).insertar(input,1);
		}

	}

	cout<<numeros;
	return 0;
}