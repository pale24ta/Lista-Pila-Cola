#ifndef PILAHPP
#define PILAHPP

#include "nodo.hpp"
#include<iostream>
using namespace std;

template<typename T>
class Pila{
    private:
        Nodo<T> *tope;
        Nodo<T> *fondo;
        int longitud;
    public:
        Pila();//constructor 
        Pila(Pila<T> &target);//constructor copia
        Pila<T>& operator=(const Pila<T>& other); // Operador de asignación
        void apilar(T elemento);
        void desapilar(); //si la pila esta vacia no hace nada
        //getters y setters
        T getElementoTope() const; //retorna el elemento del tope
        T getElementoFondo() const;//devuelve el elemento del fondo de la pila
        int getLongitud() const;
        bool esVacia() const;
        T consultar(int pos); // con logica de verificacion de errores
        int existe(T elemento); //verifica si el elemento esta en la pila , devuelve -1 si no
        void liberarPila();
        ~Pila();//destructor de pila
        void imprimirPila();


};
//implementacion de metodos
template<typename T>
Pila<T>::Pila(): tope(nullptr), fondo(nullptr),longitud(0){}

//constructor copia
template<typename T>
Pila<T>::Pila(Pila<T> &target): tope(nullptr), fondo(nullptr), longitud(0){
    //si la pila original esta vacia, no hay nada que copiar
    if(target.tope == nullptr) return;

    Nodo<T> *actualTarget= target.tope;
    tope = new Nodo<T>(actualTarget->getElemento());
    fondo = tope;
    longitud++;
    actualTarget = actualTarget ->getSiguiente();
    //copiar el resto de nodos
    while(actualTarget!=nullptr){
        Nodo<T> * nuevoNodo= new Nodo<T>(actualTarget->getElemento());
        fondo->setSiguiente(nuevoNodo);
        fondo=nuevoNodo;
        longitud++;
        actualTarget = actualTarget->getSiguiente();
    }

}
template<typename T>
Pila<T>& Pila<T>::operator=(const Pila<T>& other) {
    if (this == &other) { // Manejo de auto-asignación: evita asignarse a sí mismo
        return *this;
    }

    // 1. Liberar los recursos actuales de 'this'
    this->liberarPila();

    // 2. Copiar los elementos de 'other' (reutilizando la lógica del constructor de copia)
    if (!other.esVacia()) {
        Pila<T> tempStack;
        Nodo<T>* current = other.tope;
        while (current != nullptr) {
            tempStack.apilar(current->getElemento());
            current = current->getSiguiente();
        }
        while (!tempStack.esVacia()) {
            this->apilar(tempStack.getElementoTope());
            tempStack.desapilar();
        }
    }
    return *this;
}

template<typename T>
T Pila<T>::getElementoTope() const{
    return tope->getElemento(); //retorna el elemento en tope
}
template<typename T>
T Pila<T>::getElementoFondo() const{
    return fondo->getElemento(); 
}

template<typename T>
void Pila<T>::apilar(T elemento){
    Nodo<T> *nuevo = new Nodo<T>(elemento);
    if (tope==nullptr)
        tope=fondo=nuevo;
    else{
        nuevo->setSiguiente(tope);
        tope=nuevo;
    }
    longitud++;
}
template<typename T>
void Pila<T>::desapilar(){

    if(!esVacia()){

        Nodo<T> *actual=tope;
   
        if(tope->getSiguiente()==nullptr){ //solo un elemento en la pila
            delete tope; //eliminamos el tope
            tope=fondo=nullptr; //si se elemina el unico elemento ahora tope y fondo apuntan a null
         }else{
            tope=tope->getSiguiente();
            delete actual;
         }
        longitud--;
    }
}
template<typename T>
bool Pila<T>::esVacia() const {
    return tope==nullptr;
}

template<typename T>
T Pila<T>::consultar(int pos){ 
    //logica para abordar errores
    if(!esVacia()){
        if (pos > longitud)
            pos=longitud;
        else {
            if(pos <= 0)
                return tope->getElemento();
        }
        Nodo<T>* actual = tope;
        for (int i = 1; i < pos ; ++i) { // Usa un bucle for y asegura que 'actual' no sea nullptr
            actual = actual->getSiguiente();
        }
        // En este punto, 'actual' no debería ser nullptr si pos es válido
        return actual->getElemento();
    }else{
        return T(); //valor por defecto
    }
}
template<typename T>
int Pila<T>::existe(T elemento){
    int pos=0;
    if(tope==nullptr)
        return -1; //pila vacia
    Nodo<T> *actual=tope;
    while (actual!=nullptr){
        if (actual->getElemento()==elemento)
            return pos;
        actual=actual->getSiguiente();
        pos++;
    }
    return -1; //elemento no encontrado
}
template<typename T>
void Pila<T>::liberarPila(){
    if (tope==nullptr)
        return; //lista vacia
    Nodo<T> *actual=tope, *aux=nullptr;
    while (actual!=nullptr){
        aux=actual;
        actual=actual->getSiguiente();
        delete aux;
    }
    tope=fondo=nullptr;
    longitud=0;
}
template<typename T>
Pila<T>::~Pila(){
    liberarPila(); //llama a liberar pila
}
template<typename T>
int Pila<T>::getLongitud() const{
    return longitud;
}
template<typename T>
void Pila<T>::imprimirPila(){
    if(tope==nullptr){
        cout<<"La pila esta vacia"<<endl;
        return;
    }
    Nodo<T> *actual = tope;
    cout<<endl;
    while (actual!=nullptr){
        cout<<actual->getElemento()<<endl;
        actual=actual->getSiguiente();
    }
}
#endif