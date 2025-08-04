#ifndef NODOHPP
#define NODOHPP

template<typename T>
class Nodo{
    private:
        Nodo<T> *siguiente;
        T elemento;
    public:
        Nodo(T dato);
        T getElemento();
        Nodo<T>* getSiguiente();
        T setElemento(T element);
        void setSiguiente(Nodo<T>*  next);

};


//implementaciones para nodo
template<typename T>
Nodo<T>::Nodo(T dato):siguiente(nullptr), elemento(dato){}

template<typename T>
T Nodo<T>::getElemento(){
    return elemento;
}
template<typename T>
Nodo<T>* Nodo<T>::getSiguiente(){
    return siguiente;
}
template<typename T>
T Nodo<T>::setElemento(T element){ 
    elemento = element;
    return elemento; 
}

template<typename T>
void Nodo<T>::setSiguiente(Nodo<T>* next){ // Debe tomar un puntero
    siguiente = next;
}
#endif