#ifndef NODODOBLEHPP
#define NODODOBLEHPP

template<typename T>
class NodoDoble{
    private:
        NodoDoble<T> *siguiente;
        NodoDoble<T> *anterior; // Añadido
        T elemento;
    public:
        // Constructor que inicializa el elemento y los punteros a nullptr
        NodoDoble(T dato) : siguiente(nullptr), anterior(nullptr), elemento(dato) {}

        T getElemento()  { return elemento; } // Hice const
        NodoDoble<T>* getSiguiente() { return siguiente; } // Hice const
        NodoDoble<T>* getAnterior()  { return anterior; } // Hice const

        T setElemento(T element) {
            elemento = element;
            return elemento;
        }
        void setSiguiente(NodoDoble<T>* next) {
            siguiente = next;
        }
        void setAnterior(NodoDoble<T>* previous) {
            anterior = previous;
        }
};

#endif