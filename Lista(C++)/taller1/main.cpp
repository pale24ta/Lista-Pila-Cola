#include<iostream>
#include <sstream>
#include "lista.hpp"
#include "cola.hpp"

using namespace std;

struct supervivientes{
	string nombre;
	int numero;
};

string elegirJugador(Lista<string> &jugadores, int k);


int main()
{
	int nCasos,k;
	Cola<int> kPruebas;
	Lista<Lista<string> > listaNombres;
	cin>>nCasos;	// Lee los n casos de prueba


	for(int i= 1; i <= nCasos; i++)
	{
		// listaNombres.insertar(Lista<string>(),1);	// Inserta una lista vacia
		cin>>k;
		kPruebas.encolar(k);	// Insertar en la cola los numeros de pruebas
	}

	// Leer los nombres

	// cout<<kPruebas;

	string leerLinea,nombre;
	int i=1;

	while(cin>>nombre){
		if(i > listaNombres.getLength()){
			listaNombres.insertar(Lista<string>(),listaNombres.getLength() + 1);	// add a new list<string> at the list
		}

		listaNombres[i].insertar(nombre,listaNombres[i].getLength()+1);
		i++;
		if(cin.get() == '\n')
		{
			i = 1;
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

	


	const int IZQUIERDA = 1,DERECHA =2;
	int dato = DERECHA;
	int pos = 1;
	while(!jugadores.esVacia() && jugadores.getLength() > 1){

		switch(dato){
			case DERECHA:
				pos += k;
				if(pos > jugadores.getLength()){
					pos = pos - jugadores.getLength();
				}
				dato = IZQUIERDA;
				break;
			case IZQUIERDA:
				pos -=k;
				if(pos <= 0){
					pos = pos + jugadores.getLength();
					if(pos == 0)
						pos  = 1;
				}
				dato = DERECHA;
				break;
		}

		jugadores.remover(pos);
		// cout<<jugadores;
	}

	return jugadores.consultar(1); // El ultimo en la lista

}
