#include<iostream>
#include <sstream>
#include "lista.hpp"
#include "cola.hpp"
// #include "listaCircle.hpp"
#include <ctime>
#include <cstdlib>


using namespace std;


// Clase invitado

class Invitado{
	private:
		string nombre;
		int casta;

	public:
		Invitado(): nombre(""),casta(0){}
		Invitado(string nombre, int casta): nombre(nombre), casta(casta){}
		string getNombre()const{return nombre;}
		// void setNombre(string nombre){th}
		int getCasta()const {return casta;}


	friend ostream& operator<<(ostream& os,const Invitado nuevo){
		os<<"("<<nuevo.nombre<<","<<nuevo.casta<<")";
		return os;
	}

};

Invitado elJuegoDeLasCastas(Lista<Invitado> &jugadores,int n, int k ,int t);
Lista<Invitado> leerListaDeInvitados();
void obtenerValor(Lista<Invitado> target , int n, int &pocoImp, int &muchoImp);



int main(){
	int nCasos;
	int n,k,t;
	Lista<Invitado> listaInvitados;
	Invitado ganador;

	cin>>nCasos;

	for(int i =1 ; i <= nCasos; i++){
		// Lee las 3 entradas
		cin>>n>>k>>t;

		listaInvitados = leerListaDeInvitados();

		// ganador = elJuegoDeLasCastas(listaInvitados,n,k,t);
		cout<<listaInvitados;
		
	}

	// cout<<listaInvitados;

	return 0;

}

void obtenerValor(Lista<Invitado> target , int n, int &pocoImp, int &muchoImp){
	pocoImp = 0;
	muchoImp = 0;

	while(!target.esVacia()){
		if(target[1].getCasta() >= n){
			muchoImp++;
		}else{
			pocoImp++;
		}
		target.remover(1);
	}
}

Invitado elJuegoDeLasCastas(Lista<Invitado> &jugadores, int n, int k, int t)
{
    // EL juego de las castas


	int muchosImportantes,menosImportantes;
	obtenerValor(jugadores,n,muchosImportantes,menosImportantes);
	int aux = t;
	bool inverse = true;
	

	while(jugadores.getLength() > 1){


		jugadores.leftShift(k);

		if(t > 0)	// Invertir Importancia de las castas
		{
			// Giramos al jugador

			if(jugadores[1].getCasta() >= n || (jugadores[1].getCasta() < n && menosImportantes <= 0)){
				if((jugadores[1].getCasta() < n && menosImportantes <= 0))
					muchosImportantes--;
				if(jugadores[1].getCasta() >= n )
					menosImportantes--;
				jugadores.remover(1);	// se elimina al jugador
			}
			t--;

		}else{

			// jugador de casta mayor 
			if(jugadores[1].getCasta() < n || (jugadores[1].getCasta() >= n && muchosImportantes <= 0)){
				
				if(jugadores[1].getCasta() < n)
					muchosImportantes--;
				if(jugadores[1].getCasta() >= n && muchosImportantes <= 0)
					menosImportantes--;

				jugadores.remover(1);	// se elimina al jugador
				t--;
			}
		}
	}

	return jugadores[1];	// Retorna al sobreviviente de la utopia
}

Lista<Invitado> leerListaDeInvitados()
{

    Lista<Invitado> registro;
		
		
	char caracteres;

	cin>>caracteres;	// lee [

	while(true)	// hasta llegar al siguiente ]
	{

		cin>>caracteres;	// lee (
		if(caracteres != '(')
			break;

		string nombre;
		getline(cin,nombre,',');

		int numero;

		cin>>numero;	// Lee el siguiente numero

		cin>>caracteres; // lee )
		if(caracteres == ')')
			registro.insertar(Invitado(nombre,numero),registro.getLength()+1);

		if(cin>>caracteres && caracteres == ']')	// lee o una coma o el ultimo corchete
			break;
	}

	return registro;
}
