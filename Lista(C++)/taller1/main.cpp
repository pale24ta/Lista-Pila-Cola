#include<iostream>
#include <sstream>
#include "lista.hpp"
#include "cola.hpp"
// #include "listaCircle.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;

string elegirJugador(Lista<string> &jugadores, int k);


int main()
{
	int nCasos,k;
	Cola<int> kPruebas;
	Lista<Lista<string> > listaNombres;
	// Lista<string> vacia;
	cin>>nCasos;	// Lee los n casos de prueba


	for(int i= 1; i <= nCasos; i++)
	{
		cin>>k;
		kPruebas.encolar(k);	// Insertar en la cola los numeros de pruebas
	}

	string leerLinea,nombres;
	
	while(getline(cin,leerLinea)){
		int i = 1;

		stringstream flujo(leerLinea);

		while(flujo>>nombres){
			if(i > listaNombres.getLength())
				listaNombres.insertar(Lista<string>(),listaNombres.getLength()+1);

			listaNombres[i].insertar(nombres,listaNombres[i].getLength()+1);
			i++;
		}
	}

	while(!listaNombres.esVacia() && !kPruebas.esVacia()){
		cout<<elegirJugador(listaNombres[1],kPruebas.consultarFrente()-1)<<endl;
		listaNombres.remover(1);
		kPruebas.desencolar();
	}


	// cout<<listaNombres;

	return 0;

}


string elegirJugador(Lista<string> &jugadores, int k){

	bool sentido = true;
	int pos = 1;

	while(jugadores.getLength() > 1){


		if(sentido){		// Horario
			pos = pos + k;
			if(pos > jugadores.getLength()){
				pos = pos  % jugadores.getLength();
			}
			sentido = false;
		}else{	// AntiHorario
			pos = pos -k;
			if(pos <= 0){
				pos = pos + jugadores.getLength();
			}
			sentido = true;
		}


		jugadores.remover(pos);
		if(sentido){
			pos -=1;
		}
	}

	return jugadores[1];
}
