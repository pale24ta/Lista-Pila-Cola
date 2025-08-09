#ifndef PILAHPP
#define PILAHPP

#include "nodo.hpp"
#include<iostream>
#include <algorithm> //para swap en c++ 98
#include<utility> //para swap en c++ 11
using namespace std;

template<typename T>
class Pila{
    private:
        Nodo<T> *tope;
        Nodo<T> *fondo;
        int longitud;

        void liberarPila();
    public:
        Pila();//constructor 
        Pila(Pila<T> &target);//constructor copia
        Pila<T>& operator=(const Pila<T>& target);
        void apilar(T elemento);
        void desapilar(); //si la pila esta vacia no hace nada
        //getters y setters
        const T& getElementoTope() const; //retorna el elemento del tope
        const T& getElementoFondo() const;//devuelve el elemento del fondo de la pila
        int getLongitud() const;
        bool esVacia() const;
        T& consultar(int pos); 
        const T& consultar(int pos) const;// con logica de verificacion de errores
        int existe(T elemento); //verifica si el elemento esta en la pila , devuelve -1 si no
        ~Pila();//destructor de pila
        void imprimirPila();


};
//implementacion de metodos
template<typename T>
Pila<T>::Pila(): tope(NULL), fondo(NULL),longitud(0){}
//constructor copia
template<typename T>
Pila<T>::Pila(Pila<T> &target): tope(NULL), fondo(NULL), longitud(0){
    //si la pila original esta vacia, no hay nada que copiar
    if(target.tope == NULL) return;
    Nodo<T> *actualTarget= target.tope;
    tope = new Nodo<T>(actualTarget->getElemento());
    fondo = tope;
    longitud++;
    actualTarget = actualTarget ->getSiguiente();
    //copiar el resto de nodos
    while(actualTarget!=NULL){
        Nodo<T> * nuevoNodo= new Nodo<T>(actualTarget->getElemento());
        fondo->setSiguiente(nuevoNodo);
        fondo=nuevoNodo;
        longitud++;
        actualTarget = actualTarget->getSiguiente();
    }
}
template<typename T>
Pila<T>& Pila<T>::operator=(const Pila<T>& target) { 
    if (this != &target) {
        Pila<T> copia(target); // Usa el constructor de copia
        swap(tope, copia.tope);
        swap(longitud, copia.longitud);
    }
    return *this; 
}
template<typename T>
const T& Pila<T>::getElementoTope() const{
    static const T valorPorDefecto = T();
    if(tope == NULL)
        return valorPorDefecto;
    return tope->getElemento();
}
template<typename T>
const T& Pila<T>::getElementoFondo() const{
    return fondo->getElemento(); 
}
template<typename T>
void Pila<T>::apilar(T elemento){
    Nodo<T> *nuevo = new Nodo<T>(elemento);
    if (tope==NULL)
        tope=fondo=nuevo;
    else{
        nuevo->setSiguiente(tope);
        tope=nuevo;
    }
    longitud++;
}
template<typename T>
void Pila<T>::desapilar(){
    Nodo<T> *actual=tope;

    if(!esVacia()){
        if(tope->getSiguiente()==NULL){ //solo un elemento en la pila
            delete tope; //eliminamos el tope
            tope=fondo=NULL; //si se elemina el unico elemento ahora tope y fondo apuntan a null
         }else{
            tope=tope->getSiguiente();
            delete actual;
         }
        longitud--;
    }else
        return;
    
}
template<typename T>
bool Pila<T>::esVacia() const {
    return tope==NULL;
}

template<typename T>
T& Pila<T>::consultar(int pos) {
    static T valorPorDefecto = T();  // Variable estática para retorno seguro
    
    if (esVacia()) 
        return valorPorDefecto;  
    
    // Ajustar posición si es inválida
    if (pos <= 0) 
        return tope->getElemento();  // Retorna referencia al tope
    
    if (pos >= longitud) 
        pos = longitud - 1;  // Ajusta al último elemento
    
    Nodo<T>* actual = tope;
    for (int i = 0; i < pos && actual != NULL; ++i) 
        actual = actual->getSiguiente();

    if (actual != NULL) 
        return actual->getElemento();  
    
    return valorPorDefecto;  
}
template<typename T>
const T& Pila<T>::consultar(int pos) const {
    // Variable estática para retornar en caso de error
    static const T valorPorDefecto = T();
    
    if (esVacia()) {
        return valorPorDefecto;
    }

    // Ajustar posición si es inválida
    if (pos <= 0) {
        return tope->getElemento(); 
    }
    if (pos >= longitud) {
        pos = longitud - 1; 
    }

    Nodo<T>* actual = tope;
    for (int i = 0; i < pos; ++i) {
        if (actual == NULL) {
            return valorPorDefecto; // Seguridad adicional
        }
        actual = actual->getSiguiente();
    }

    if (actual != NULL) {
        return actual->getElemento();
    }
    return valorPorDefecto;
}
template<typename T>
int Pila<T>::existe(T elemento){
    int pos=0;
    if(tope==NULL)
        return -1; //pila vacia
    Nodo<T> *actual=tope;
    while (actual!=NULL){
        if (actual->getElemento()==elemento)
            return pos;
        actual=actual->getSiguiente();
        pos++;
    }
    return -1; //elemento no encontrado
}
template<typename T>
void Pila<T>::liberarPila(){
    if (tope==NULL)
        return; //lista vacia
    Nodo<T> *actual=tope, *aux=NULL;
    while (actual!=NULL){
        aux=actual;
        actual=actual->getSiguiente();
        delete aux;
    }
    tope=fondo=NULL;
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
    if(tope==NULL){
        cout<<"La pila esta vacia"<<endl;
        return;
    }
    Nodo<T> *actual = tope;
    cout<<endl;
    while (actual!=NULL){
        cout<<actual->getElemento();
        actual=actual->getSiguiente();
    }
}
#endif