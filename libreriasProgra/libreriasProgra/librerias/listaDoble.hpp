#ifndef LISTADOBLEHPP
#define LISTADOBLEHPP

#include <iostream>
#include<utility> //para swap en c++11
#include <algorithm> //para swap en c++ 98
#include "nodoDoble.hpp" 

using namespace std;

template<typename T>
class ListaDoble { 
private:
    NodoDoble<T> *head;
    NodoDoble<T> *tail;
    int longitud;

    void liberarLista();

public:
    // Constructor por defecto
    ListaDoble();
    // Constructor de copia
    ListaDoble(const ListaDoble<T> &target);
    // Operador de asignación
    ListaDoble<T>& operator=(const ListaDoble<T>& target);
    // Destructor
    ~ListaDoble();

    int getLongitud() const;
    const T& getElementoHead() const;
    const T& getElementoTail() const;

    // Métodos de modificación
    void insertarEnPosicion(T elemento, int pos);
    void eliminarPorPosicion(int pos);
    // Métodos de consulta
    T& consultar(int pos);
    const T& consultar(int pos) const ;
    int buscar(T elemento);

    ListaDoble<T> concatenar(const ListaDoble<T> &target);
    bool esVacia() const;
    void imprimirLista();
    void imprimirListaInversa(); 
    void invertir(); 
    // Funciones adicionales
    void intercambiar(int pos1, int pos2);
    static ListaDoble<T> sortedIntersect(ListaDoble<T> a, ListaDoble<T> b);
};

template<typename T>
ListaDoble<T>::ListaDoble() : head(NULL), tail(NULL), longitud(0) {}
//constructor copia
template<typename T>
ListaDoble<T>::ListaDoble(const ListaDoble<T> &target) : head(NULL), tail(NULL), longitud(0) {
    if (target.head == NULL)
        return;

    NodoDoble<T> *nodoActualTarget = target.head;
    while (nodoActualTarget != NULL) {
        insertarAlFinal(nodoActualTarget->getElemento());
        nodoActualTarget = nodoActualTarget->getSiguiente();
    }
}

template<typename T>
ListaDoble<T>& ListaDoble<T>::operator=(const ListaDoble<T>& target) {
    if(this != target){
        ListaDoble<T> aux(target);
        swap(aux.head, head);
        swap(aux.tail, tail);
        swap(aux.longitud, longitud);
    }
    return *this;
}

template<typename T>
ListaDoble<T>::~ListaDoble() {
    liberarLista();
}

template<typename T>
void ListaDoble<T>::liberarLista() {
    NodoDoble<T> *actual = head;
    NodoDoble<T> *temp = NULL;
    while (actual != NULL) {
        temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    }
    head = NULL;
    tail = NULL;
    longitud = 0;
}
//metodos getters
template<typename T>
int ListaDoble<T>::getLongitud() const { return longitud; }

template<typename T>
const T& ListaDoble<T>::getElementoHead() const {
    static const T valorPorDefecto = T();
    if (head == NULL) 
        return valorPorDefecto; 
    return head->getElemento();
}
template<typename T>
const T& ListaDoble<T>::getElementoTail() const {
    static const T valorPorDefecto = T();
    if (tail == NULL) 
        return valorPorDefecto; 
    return tail->getElemento();
}
template<typename T>
void ListaDoble<T>::insertarEnPosicion(T elemento, int pos) {
    if (pos > longitud) 
        pos = longitud;
    if (pos < 0) 
        pos = 0;

    NodoDoble<T> *nuevo = new NodoDoble<T>(elemento);

    if (longitud == 0) { // Caso: Lista vacía
        head = nuevo;
        tail = nuevo;
    } else if (pos == 0) { // Caso: Insertar al principio
        nuevo->setSiguiente(head);
        head->setAnterior(nuevo);
        head = nuevo;
    } else if (pos == longitud) { // Caso: Insertar al final (optimizado)
        tail->setSiguiente(nuevo);
        nuevo->setAnterior(tail);
        tail = nuevo;
    } else { // Caso: Insertar en el medio
        NodoDoble<T> *actual = head;
        // Recorrer hasta el nodo ANTERIOR al punto de inserción
        for (int i = 0; i < pos - 1; i++) 
            actual = actual->getSiguiente();
        
        // Enlazar el nuevo nodo
        nuevo->setSiguiente(actual->getSiguiente());
        nuevo->setAnterior(actual);
        // Enlazar los nodos circundantes
        actual->getSiguiente()->setAnterior(nuevo);
        actual->setSiguiente(nuevo);
    }
    longitud++;
}
template<typename T>
void ListaDoble<T>::eliminarPorPosicion(int pos) {
    if (longitud == 0) return;

    if (pos < 0) 
        pos = 0;
    else if (pos >= longitud) 
        pos = longitud - 1;

    NodoDoble<T> *nodoAEliminar = NULL;

    if (longitud == 1) { // Caso: Un solo elemento
        nodoAEliminar = head;
        head = NULL;
        tail = NULL;
    } else if (pos == 0) { // Caso: Eliminar head
        nodoAEliminar = head;
        head = head->getSiguiente();
        head->setAnterior(NULL); // El anterior del nuevo head es nulo
    } else if (pos == longitud - 1) { // Caso: Eliminar tail
        nodoAEliminar = tail;
        tail = tail->getAnterior();
        tail->setSiguiente(NULL); // El siguiente del nuevo tail es nulo
    } else { // Caso: Eliminar del medio
        NodoDoble<T> *actual = head;
        for (int i = 0; i < pos; i++) { // Recorrer hasta el nodo A ELIMINAR
            actual = actual->getSiguiente();
        }
        nodoAEliminar = actual;
        NodoDoble<T> *previo = nodoAEliminar->getAnterior();
        NodoDoble<T> *siguiente = nodoAEliminar->getSiguiente();

        previo->setSiguiente(siguiente);
        siguiente->setAnterior(previo);
    }
    delete nodoAEliminar;
    longitud--;
}
template<typename T>
T& ListaDoble<T>::consultar(int pos) {
    static T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;

    if (pos <= 0) 
        return head->getElemento();
    if (pos >= longitud) 
        return tail->getElemento();
    
    NodoDoble<T>* actual = head;
    for (int i = 0; i < pos; ++i) {
        if (actual == NULL) 
            return valorPorDefecto;
        actual = actual->getSiguiente();
    }

    if (actual != NULL) 
        return actual->getElemento();
    
    return valorPorDefecto;
}
template<typename T>
const T& ListaDoble<T>::consultar(int pos) const {
    static const T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;
    
    if (pos <= 0) 
        return head->getElemento();
    if (pos >= longitud) 
        return tail->getElemento();
    
    NodoDoble<T>* actual = head;
    for (int i = 0; i < pos; ++i) {
        if (actual == NULL) 
            return valorPorDefecto;
        actual = actual->getSiguiente();
    }

    if (actual != NULL) 
        return actual->getElemento();
    
    return valorPorDefecto;
}
template<typename T>
int ListaDoble<T>::buscar(T elemento) {
    if (longitud == 0) return -1;

    NodoDoble<T> *actual = head;
    int pos = 0;
    while (actual != NULL) {
        if (actual->getElemento() == elemento)
            return pos;
        actual = actual->getSiguiente();
        pos++;
    }
    return -1;
}

template<typename T>
bool ListaDoble<T>::esVacia() const {
    return head == NULL;
}

template<typename T>
ListaDoble<T> ListaDoble<T>::concatenar(const ListaDoble<T> &target) {
    ListaDoble<T> resultado(*this); // Inicia con una copia de la lista actual.

    NodoDoble<T> *actualTarget = target.head;
    while (actualTarget != NULL) {
        resultado.insertarAlFinal(actualTarget->getElemento());
        actualTarget = actualTarget->getSiguiente();
    }
    return resultado;
}

template<typename T>
void ListaDoble<T>::imprimirLista() {
    cout << std::endl;
    if (head == NULL) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    NodoDoble<T> *actual = head;
    while (actual != NULL) {
        cout << actual->getElemento();
        actual = actual->getSiguiente();
    }
}

template<typename T>
void ListaDoble<T>::imprimirListaInversa() {
    cout << endl;
    if (tail == NULL) { // Verificar tail, ya que comenzamos desde él
        cout << "La lista esta vacia." << endl;
        return;
    }
    NodoDoble<T> *actual = tail;
    while (actual != NULL) {
        cout << actual->getElemento();
        actual = actual->getAnterior();
    }
}
template<typename T>
void ListaDoble<T>::invertir(){
    if(head== NULL || head == tail)
        return;
    
    NodoDoble<T>* actual=head;
    NodoDoble<T>* aux=NULL;

    while(actual != NULL){
        aux=actual->getAnterior();
        actual->setAnterior(actual->getSiguiente());
        actual->setSiguiente(aux);

        actual=actual->getAnterior();
    }

    aux = head;
    head = tail;
    tail=aux;
}
// --- Funciones adicionales ---
template<typename T>
void ListaDoble<T>::intercambiar(int pos1, int pos2) {
    if (longitud <= 1 || pos1 == pos2) return;

    if (pos1 < 0 || pos2 < 0 || pos1 >= longitud || pos2 >= longitud) {
        cout << "\nPosiciones invalidas, imposible intercambiar\n";
        return;
    }

    // Asegurarse de que pos1 sea el menor para simplificar la lógica de recorrido
    if (pos1 > pos2) {
        swap(pos1, pos2);
    }

    // Buscar los nodos en las posiciones
    NodoDoble<T> *nodo1 = head;
    for (int i = 0; i < pos1; ++i) {
        nodo1 = nodo1->getSiguiente();
    }

    NodoDoble<T> *nodo2 = head;
    for (int i = 0; i < pos2; ++i) {
        nodo2 = nodo2->getSiguiente();
    }

    // Intercambiar solo los elementos (datos) de los nodos, no los nodos en sí.
    // Esto es mucho más simple en listas enlazadas.
    if (nodo1 != NULL && nodo2 != NULL) {
        T aux = nodo1->getElemento();
        nodo1->setElemento(nodo2->getElemento());
        nodo2->setElemento(aux);
    }
}

template<typename T>
ListaDoble<T> ListaDoble<T>::sortedIntersect(ListaDoble<T> a, ListaDoble<T> b) {
    ListaDoble<T> resultado;
    // Las listas 'a' y 'b' se pasan por valor, lo que crea copias.
    // Modificarlas (eliminar elementos) en este contexto no afectará a las originales.

    while (!a.esVacia() && !b.esVacia()) {
        if (a.getElementoHead() == b.getElementoHead()) { // Usar getElementoHead
            resultado.insertarAlFinal(a.getElementoHead());
            a.eliminarPorPosicion(0);
            b.eliminarPorPosicion(0);
        } else {
            if (a.getElementoHead() > b.getElementoHead())
                b.eliminarPorPosicion(0);
            else
                a.eliminarPorPosicion(0);
        }
    }
    return resultado;
}

#endif