#ifndef COLAHPP
#define COLAHPP
#include "nodo.hpp"
#include<utility>
#include<iostream>

using namespace std;


template<typename T>
class Cola{
    private:
        Nodo<T> *head, *tail;
        int longitud;
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
        void setHead(Nodo<T> *nuevoHead);//establece un nuevo head
        void setTail(Nodo<T> *nuevoTail); //establece un nuevo tail
        T getFrente() const; //devulve el elemento en el head
        T getUltimo() const; ///devuelve el elemento en el tail
        int getLongitud() const;
        //estos metodos fueron eliminados por que rompen el encapsulamiento
        Nodo<T> getHead(); //devuelve puntero a head
        Nodo<T> getTail(); //devuelve un puntero al tail rompen encapsulamiento
        
        //metodos clasicos
        void encolar(T elemento); 
        void desencolar(); //booleano , si esta vacia devuelve false
        //Lista<Cola<T> split(int nPartes); //devuelve una lista de colas separadas en npartes
        bool esVacia() const; 
        int existe(T elemento); //verifica si un elemento esta en la cola , -1 sino esta
        void liberarCola(); // metodo para liberar la lista eliminar nodos
        void imprimirCola();
        T consultar(int pos); //con logica para abordar errores
};


//constructor polimorfico
template<typename T>
Cola<T>::Cola():head(nullptr), tail(nullptr), longitud(0){}
//constructor copia
template<typename T>
Cola<T>::Cola( const Cola<T> &target): head(nullptr), tail(nullptr), longitud(0) {
    //si la cola original esta vacia, proceder a copiar los elementos
    if(target.head != nullptr){
        //copiar el primer nodo
        Nodo<T> *original = target.head;
        head = new Nodo<T>(original->getElemento());
        tail=head;
        //avanzar al siguiente nodo en la lista original
        original= original->getSiguiente();
        while(original!= nullptr){
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
    //1. verificar auto-asignacion 
    if(this == &target){
        Cola<T> aux(target); //2. crear copia temporal (usa constructor copia)

        //3. intercambiar contenidos
        swap(head, aux.head);
        swap(tail, aux.tail);
        //4. aux se destrue automaticamente, liberando la memoria vieja
    }
    return *this; //5. devolver referencia a this
}
//destructor
template<typename T>
Cola<T>::~Cola(){
    liberarCola(); //liberar la cola
}

template<typename T>
void Cola<T>::setHead(Nodo<T> *nuevoHead){
    head=nuevoHead;
}
template<typename T>
void Cola<T>::setTail(Nodo<T> *nuevoTail){
    tail=nuevoTail;
}
template<typename T>
int Cola<T> :: getLongitud() const{
    return longitud;
}

template<typename T>
T Cola<T> :: getFrente() const{
    return head->getElemento(); 
}
template<typename T>
T Cola<T>::getUltimo() const{
    return tail->getElemento();
}
//metodos que devuelven punteros
template<typename T>
Nodo<T> Cola<T>::getHead(){
    return head;
}
template<typename T>
Nodo<T> Cola<T>::getTail(){
    return tail;
}
//funciones principales
template<typename T>
void Cola<T>::encolar(T elemento){
    Nodo<T> *nuevoNodo = new Nodo<T>(elemento);

    if(head==nullptr)
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
    if(head != nullptr){
        if(head->getSiguiente()==nullptr){ //solo un elemento en la cola
        delete actual;
        head=tail=nullptr;
    }
    else      
        head=head->getSiguiente(); //establecer el nuevo head al siguinete elemento despues del head
    delete actual; //eliminar el nodo del frente actaul
    longitud--;
    }
   }else
    return;
}

template<typename T>
bool Cola<T>::esVacia() const{
    return head==nullptr;
}
template<typename T>
int Cola<T>::existe(T elemento){
    if(head==nullptr)
        return -1; //lista vacia no existe
    int pos=0;
    Nodo<T> *actual=head;

    while (actual->getSiguiente()!=nullptr){
        if(actual->getElemento()==elemento)
            return pos;
        actual=actual->getSiguiente();
        pos++;
    }
    return -1; //elemento no encontrado 

}
template<typename T>
void Cola<T>::liberarCola(){
    if(head==nullptr)
        return;
    Nodo<T> *actual=head, *aux=nullptr;
    while (actual!=nullptr){
        aux=actual;
        actual=actual->getSiguiente();
        delete aux;
    }
    head=tail=nullptr;
    longitud=0;
}
template<typename T>
void Cola<T>::imprimirCola(){
    cout<<endl;
    if(head==nullptr){
        cout<<"La cola esta vacia"<<endl;
        return;
    }
    Nodo<T> *actual = head;
    cout<<endl;
    while (actual != nullptr){
        cout<<actual->getElemento()<<endl;
        actual=actual->getSiguiente();
    }
}
template<typename T>
T Cola<T>::consultar(int pos){
    if(!esVacia()){
        if(pos>=longitud)
            return tail->getElemento();
        else{
            if(pos <= 0)
                return head->getElemento();
        }
        Nodo<T>* actual=head;
        for (int i = 1; i < pos; i++)
            actual=actual->getSiguiente();
        
        return actual->getElemento();
    }else
        return T(); //valor por defecto

}
#endif