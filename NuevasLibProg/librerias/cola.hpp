#ifndef COLAHPP
#define COLAHPP
#include "nodo.hpp"
#include<iostream>

using namespace std;


template<typename T>
class Cola{
    private:
        Nodo<T> *head, *tail;
        int longitud;

        void liberarCola(); 
        void swap(Nodo<T>*& a, Nodo<T>*& b);
        void swapT(int &a, int &b);
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
        T& getFrente() const; 
        T& getUltimo() const; 
        int getLongitud() const;
        //metodos clasicos
        void encolar(T elemento); 
        void desencolar(); //booleano , si esta vacia devuelve false
        bool esVacia() const; 
        int existe(T elemento); //verifica si un elemento esta en la cola , -1 sino esta, //este devuelve la posicion
        void imprimirCola();
        bool operator==(const Cola<T> &target) const;
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
        longitud++;
        //avanzar al siguiente nodo en la lista original
        original= original->getSiguiente();
        while(original!= NULL){
            Nodo<T> *nuevoNodo= new Nodo<T>(original->getElemento());
            tail->setSiguiente(nuevoNodo);
            tail= nuevoNodo;
            original = original->getSiguiente();
            longitud++;
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
        swap(aux.head, head);
        swap(aux.tail, tail);
        swapT(aux.longitud, longitud);
        
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
T& Cola<T> :: getFrente() const{
    static  T valorPorDefecto = T();
    if (head == NULL)
        return valorPorDefecto; 
    return head->getElemento(); 
}
template<typename T>
T& Cola<T>::getUltimo() const{
    static T valorPorDefecto = T();
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

    while (actual!=NULL){
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
bool Cola<T>::operator==(const Cola<T> &target) const{
    if(longitud == target.longitud ){
        Nodo<T> *thisActual, *targetActual;
        thisActual = head;
        targetActual = target.head;
        while (targetActual!=NULL && thisActual!=NULL){//la segunda comprobacion es opcional.. por seguridad la coloque
            if(targetActual->getElemento() != thisActual->getElemento())
                return false;
            targetActual=targetActual->getSiguiente();
            thisActual=thisActual->getSiguiente();
        }
    }else{
        return false;
    }
    return true;
}
template<typename T> 
void Cola<T>::swapT(int &a, int &b){
    int aux=a;
    a=b;
    b=aux;
}
template<typename T>
void Cola<T>::swap(Nodo<T>*& a, Nodo<T>*& b){
    Nodo<T>* aux = a;
    a = b;
    b = aux;
}
#endif