#ifndef COLAHPP
#define COLAHPP
#include "nodo.hpp"
#include<utility> //para swap
#include<algorithm> //para swap en c++ 98
#include<iostream>

using namespace std;


template<typename T>
class Cola{
    private:
        Nodo<T> *head, *tail;
        int longitud;

        void liberarCola(); 
    public:
        //constructor por defecto
        Cola();
        //constructor copia
        Cola(const Cola<T> &target);
        //operado de asignacion
        Cola<T>& operator=(const Cola<T> &target);
        //destructor
        ~Cola();
        //setters y getters
        const T& getFrente() const; 
        const T& getUltimo() const; 
        int getLongitud() const;
        //metodos clasicos
        void encolar(T elemento); 
        void desencolar(); //booleano , si esta vacia devuelve false
        bool esVacia() const; 
        int existe(T elemento); //verifica si un elemento esta en la cola , -1 sino esta
        void imprimirCola();
        T& consultar(int pos); //con logica para abordar errores
        const T& consultar(int pos) const; 
};
//constructor polimorfico
template<typename T>
Cola<T>::Cola():head(NULL), tail(NULL), longitud(0){} //lista de inicializacion
//constructor copia
template<typename T>
Cola<T>::Cola( const Cola<T> &target): head(NULL), tail(NULL), longitud(0) {
    //si la cola original esta vacia, proceder a copiar los elementos
    if(target.head != NULL){
        //copiar el primer nodo
        Nodo<T> *original = target.head;
        head = new Nodo<T>(original->getElemento());
        tail=head;
        //avanzar al siguiente nodo en la lista original
        original= original->getSiguiente();
        while(original!= NULL){
            Nodo<T> *nuevoNodo= new Nodo<T>(original->getElemento());
            tail->setSiguiente(nuevoNodo);
            tail= nuevoNodo;
            original = original->getSiguiente();
        }
    }
}
//operador de asignacion
template<typename T>
Cola<T>& Cola<T>::operator=(const Cola<T> &target){
    // este if veridica autoasignacion 
    if(this != &target){
        Cola<T> aux(target); // y aqui creo una copia temporal
        // intercambiar contenidos
        swap(head, aux.head);
        swap(tail, aux.tail);
        // aux se destrue automaticamente, liberando la memoria vieja
        // esto pasa por que se llama al destructor de la clasw
    }
    return *this; 
}
//destructor
template<typename T>
Cola<T>::~Cola(){
    liberarCola(); //liberar la cola
}
template<typename T>
int Cola<T> :: getLongitud() const{
    return longitud;
}
template<typename T>
const T& Cola<T> :: getFrente() const{
    static const T valorPorDefecto = T();
    if (head == NULL)
        return valorPorDefecto; 
    return head->getElemento(); 
}
template<typename T>
const T& Cola<T>::getUltimo() const{
    static const T valorPorDefecto = T();
    if(tail==NULL)
        return valorPorDefecto;
    return tail->getElemento();
}
//funciones principales
template<typename T>
void Cola<T>::encolar(T elemento){
    Nodo<T> *nuevoNodo = new Nodo<T>(elemento);

    if(head==NULL)
        head=tail=nuevoNodo;
    else{
        tail->setSiguiente(nuevoNodo);
        tail=nuevoNodo;
    }
    longitud++;
}
template<typename T>
void Cola<T>::desencolar(){

   if(!esVacia()){
        Nodo<T> *actual=head;
    if(head != NULL){
        if(head->getSiguiente()==NULL){ //solo un elemento en la cola
            delete actual;
        head=tail=NULL;
    }
    else      
        head=head->getSiguiente(); //establecer el nuevo head al siguinete elemento despues del head
    delete actual; //eliminar el nodo del frente actaul
    longitud--;
    }
   }else
        return; //no desencolar
}
template<typename T>
bool Cola<T>::esVacia() const{
    return head==NULL;
}
template<typename T>
int Cola<T>::existe(T elemento){
    if(head==NULL)
        return -1; //lista vacia no existe
    int pos=0;
    Nodo<T> *actual=head;

    while (actual->getSiguiente()!=NULL){
        if(actual->getElemento()==elemento)
            return pos;
        actual=actual->getSiguiente();
        pos++;
    }
    return -1; //elemento no encontrado 

}
template<typename T>
void Cola<T>::liberarCola(){
    if(head==NULL)
        return;
    Nodo<T> *actual=head, *aux=NULL;
    while (actual!=NULL){
        aux=actual;
        actual=actual->getSiguiente();
        delete aux;
    }
    head=tail=NULL;
    longitud=0;
}
template<typename T>
void Cola<T>::imprimirCola(){
    cout<<endl;
    if(head==NULL){
        cout<<"La cola esta vacia"<<endl;
        return;
    }
    Nodo<T> *actual = head;
    cout<<endl;
    while (actual != NULL){
        cout<<actual->getElemento()<<" ";
        actual=actual->getSiguiente();
    }
}
template<typename T>
T& Cola<T>::consultar(int pos) {
  
    static T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;
    
    if (pos <= 0) 
        return head->getElemento();
    if (pos >= longitud) 
        return tail->getElemento();

    Nodo<T>* actual = head;
    
    for (int i = 0; i < pos; ++i) 
        actual = actual->getSiguiente();
     
    return actual->getElemento();
    
}
template<typename T>
const T& Cola<T>::consultar(int pos) const {
  
    static const T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;

    if (pos <= 0) 
        return head->getElemento();
    if (pos >= longitud) 
        return tail->getElemento();

    Nodo<T>* actual = head;
    
    for (int i = 0; i < pos; ++i) 
        actual = actual->getSiguiente();

    
    return actual->getElemento();
    
}
#endif