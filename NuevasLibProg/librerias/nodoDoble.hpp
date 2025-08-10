#ifndef NODODOBLEHPP
#define NODODOBLEHPP

template<typename T>
class NodoDoble{
    private:
        NodoDoble<T> *siguiente;
        NodoDoble<T> *anterior; 
        T elemento;
    public:
        NodoDoble(T dato);
        T& getElemento();
        NodoDoble<T>* getSiguiente();
        NodoDoble<T>* getAnterior();
        void setElemento(T element);
        void setSiguiente(NodoDoble<T>* next);
        void setAnterior(NodoDoble<T>* previous);
};
template<typename T>
NodoDoble<T>::NodoDoble(T dato): siguiente(NULL), anterior(NULL), elemento(dato){}
template<typename T>
T& NodoDoble<T>::getElemento(){
    return elemento;
} 
template<typename T>
NodoDoble<T>* NodoDoble<T>::getSiguiente(){
    return siguiente;
}
template<typename T>
NodoDoble<T>* NodoDoble<T>::getAnterior(){
    return anterior;
}
template<typename T>
void NodoDoble<T>::setElemento(T element){
    elemento = element;
}
template<typename T>
void NodoDoble<T>::setSiguiente(NodoDoble<T>* next){
    siguiente = next;
}
template<typename T>
void NodoDoble<T>::setAnterior(NodoDoble<T>* previous){
    anterior = previous;
}

#endif