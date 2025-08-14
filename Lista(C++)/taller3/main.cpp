#include<iostream>
#include <sstream>
#include "lista.hpp"
#include "cola.hpp"
// #include "listaCircle.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;


int main(){


	Lista<int> otra;
	Lista<int> a1,a2;
	
	for(int i=2; i < 11; i++){
		otra.insertar(i*2,1);
	}

	otra.split(a1,a2);

	cout<<a1;
	return 0;
}