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
	Lista<int> nueva;
	nueva.insertar(2,1);
	otra.insertar(3,1);

	Lista<int> algo = nueva.concat(otra);
	cout<<algo;
	return 0;
}