#ifndef LISTACIRCULARDOBLE
#define LISTACIRCULARDOBLE

#include "nodoDoble.hpp" 
#include <iostream>
#include <utility> // Para swap en c++ 11
#include <algorithm> //para swap en c++ 98

using namespace std; 

template<typename T>
class ListaCircularDoble { 
private:
    NodoDoble<T> *head;
    NodoDoble<T> *tail;
    int longitud;

    void liberarLista();

public:
    // Constructor por defecto
    ListaCircularDoble();
    // Constructor de copia
    ListaCircularDoble(const ListaCircularDoble<T> &target);
    // Operador de asignación
    ListaCircularDoble<T>& operator=(const ListaCircularDoble<T>& target);
    // Destructor
    ~ListaCircularDoble();

    // Métodos clásicos (getters)
    int getLongitud() const;

    const T& getElementoHead() const;
    const T& getElementoTail() const;

    // Métodos de modificación
    void insertarEnPosicion(T elemento, int pos);
    void eliminarPorPosicion(int pos);
    void intercambiar(int pos1, int pos2);

    // Métodos de consulta
    T& consultar(int pos); // Con lógica para abordar errores
    const T& consultar(int pos) const ; // Con lógica para abordar errores
    int existe(T elemento); // Devuelve -1 si no está, devuelve la posición del elemento
    ListaCircularDoble<T> concatenar(const ListaCircularDoble<T> &target); 
    bool esVacia() const;
    void imprimirLista();
    // Nuevo método para imprimir en sentido inverso 
    void imprimirListaInversa();
    void invertir();
};
// Constructor por defecto
template<typename T>
ListaCircularDoble<T>::ListaCircularDoble() : head(NULL), tail(NULL), longitud(0) {}

// Constructor de copia
template<typename T>
ListaCircularDoble<T>::ListaCircularDoble(const ListaCircularDoble<T> &target) : head(NULL), tail(NULL), longitud(0) {
    if (target.head == NULL) 
        return; // Lista original vacía, no hay nada que copiar.
    
    NodoDoble<T> *actualTarget = target.head;
    // Iterar longitud veces para copiar todos los elementos.
    for (int i = 0; i < target.longitud; ++i) {
        insertarEnPosicion(actualTarget->getElemento(), longitud);
        actualTarget = actualTarget->getSiguiente();
    }
}

template<typename T>
ListaCircularDoble<T>& ListaCircularDoble<T>::operator=(const ListaCircularDoble<T>& target) {
    if(this != &target){
        ListaCircularDoble<T> aux(target); // Usa el constructor de copia
        swap(aux.head, head);
        swap(aux.tail, tail);
        swap(aux.longitud, longitud);
    }
    return *this;
}

// Destructor de la lista
template<typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    liberarLista();
}
template<typename T>
void ListaCircularDoble<T>::liberarLista() {
    if (head == NULL)
        return; // La lista ya está vacía

    // Romper la circularidad para evitar bucles infinitos en el borrado.
    //  el puntero siguiente del tail a NULL para el borrado secuencial.
    tail->setSiguiente(NULL);

    NodoDoble<T> *actual = head;
    NodoDoble<T> *siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    head = NULL;
    tail = NULL;
    longitud = 0;
}

template<typename T>
int ListaCircularDoble<T>::getLongitud() const {
    return longitud;
}
template<typename T>
const T& ListaCircularDoble<T>::getElementoHead() const {
    static const T valorPorDefecto = T();
    if(head == NULL)
        return valorPorDefecto;
    return head->getElemento();
}
template<typename T>
const T& ListaCircularDoble<T>::getElementoTail() const {
    static const T valorPorDefecto = T();
    if(tail == NULL)
        return valorPorDefecto;
    return tail->getElemento();
}
template<typename T>
void ListaCircularDoble<T>::insertarEnPosicion(T elemento, int pos) {
    if (pos > longitud)
        pos = longitud; // Insertar al final
    if (pos < 0)
        pos = 0; // Insertar al principio

    NodoDoble<T> *nuevo = new NodoDoble<T>(elemento);

    if (longitud == 0) { // Caso 1: Lista vacía
        head = nuevo;
        tail = nuevo;
        nuevo->setSiguiente(nuevo); // Circularidad: apunta a sí mismo
        nuevo->setAnterior(nuevo);  // Circularidad: apunta a sí mismo
    } 
    else if (pos == 0) { // Caso 2: Insertar al principio
        nuevo->setSiguiente(head);
        nuevo->setAnterior(tail);  // La nueva head apunta hacia atrás al tail
        head->setAnterior(nuevo);   // El antiguo head ahora apunta al nuevo nodo
        tail->setSiguiente(nuevo);  // El tail apunta a la nueva head
        head = nuevo;               // Actualizar head
    } 
    else if (pos == longitud) { // Caso 3: Insertar al final se pudo optimizar debido al doble enlace
        nuevo->setSiguiente(head);  // El nuevo nodo apunta a head (circularidad)
        nuevo->setAnterior(tail);   // El nuevo nodo apunta al antiguo tail
        tail->setSiguiente(nuevo);  // El antiguo tail ahora apunta al nuevo nodo
        head->setAnterior(nuevo);   // El head apunta hacia atrás al nuevo tail
        tail = nuevo;               // Actualizar tail
    } 
    else { // Caso 4: Insertar en medio
        NodoDoble<T> *actual = head;
        for (int i = 0; i < pos - 1; i++)
            actual = actual->getSiguiente();

        nuevo->setSiguiente(actual->getSiguiente());
        nuevo->setAnterior(actual);
        actual->getSiguiente()->setAnterior(nuevo);
        actual->setSiguiente(nuevo);
    }
    longitud++;
}
template<typename T>
void ListaCircularDoble<T>::eliminarPorPosicion(int pos) {
    if (longitud == 0)
        return; // La lista está vacía, no se puede eliminar.

    if (pos < 0) {
        pos = 0;
    } else if (pos >= longitud) {
        pos = longitud - 1;
    }

    NodoDoble<T> *nodoAEliminar;

    if (longitud == 1) { // Caso 1: Eliminando el único elemento de la lista.
        nodoAEliminar = head;
        head = NULL;
        tail = NULL;
    } else { // Lista con más de un elemento
        NodoDoble<T> *previo = NULL;
        NodoDoble<T> *siguiente = NULL;

        if (pos == 0) { // Caso 2: Eliminando el head 
            nodoAEliminar = head;
            head = head->getSiguiente();
            head->setAnterior(tail);    // El nuevo head apunta hacia atrás al tail
            tail->setSiguiente(head);    // El tail apunta hacia adelante al nuevo head
        } else if (pos == longitud - 1) { // Caso 3: Eliminando el tail
            nodoAEliminar = tail;
            tail = tail->getAnterior();
            tail->setSiguiente(head);    // El nuevo tail apunta hacia adelante al head
            head->setAnterior(tail);    // El head apunta hacia atrás al nuevo tail
        } else { // Caso 4: Eliminando un nodo intermedio
            NodoDoble<T> *actual = head;
            for (int i = 0; i < pos; i++) {
                actual = actual->getSiguiente();
            }
            nodoAEliminar = actual;
            previo = nodoAEliminar->getAnterior();
            siguiente = nodoAEliminar->getSiguiente();

            previo->setSiguiente(siguiente);
            siguiente->setAnterior(previo);
        }
    }
    delete nodoAEliminar;
    longitud--;
}
template<typename T>
void ListaCircularDoble<T>::intercambiar(int pos1, int pos2) {
    if (longitud <= 1 || pos1 == pos2) 
        return;

    if (pos1 < 0 || pos2 < 0 || pos1 >= longitud || pos2 >= longitud) {
        cout << "\nPosiciones invalidas, imposible intercambiar\n";
        return;
    }

    NodoDoble<T> *actual = head;
    NodoDoble<T> *nodo1 = NULL;
    NodoDoble<T> *nodo2 = NULL;

    for (int i = 0; i < longitud; ++i) { // Recorrer todos los nodos de la circular
        if (i == pos1)
            nodo1 = actual;
        if (i == pos2)
            nodo2 = actual;
        if (nodo1 != NULL && nodo2 != NULL)
            break; // Salir si ambos nodos fueron encontrados

        actual = actual->getSiguiente();
    }
    // Intercambiar los elementos (valores) de los nodos
    T aux = nodo1->getElemento();
    nodo1->setElemento(nodo2->getElemento());
    nodo2->setElemento(aux);
}
template<typename T>
T& ListaCircularDoble<T>::consultar(int pos) {
    static T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;

    pos = pos % longitud;
    if (pos < 0) 
        pos += longitud; // Manejo de posiciones negativas
    
    if (pos == 0) 
        return head->getElemento();
    if (pos == longitud - 1) 
        return tail->getElemento();

    NodoDoble<T>* actual = head;
    int contador = 0;
    bool encontrado = false;
    
    while (contador < pos) {
        if (actual == NULL || actual->getSiguiente() == head) 
            break; 
        actual = actual->getSiguiente();
        contador++;
        encontrado = true;
    }

    if (encontrado && actual != NULL) 
        return actual->getElemento();
    
    return valorPorDefecto;
}
template<typename T>
const T& ListaCircularDoble<T>::consultar(int pos) const {
    static const T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;
    
    pos = pos % longitud;
    if (pos < 0) 
        pos += longitud; 
    
    if (pos == 0) 
        return head->getElemento();
    if (pos == longitud - 1) 
        return tail->getElemento();
    
    NodoDoble<T>* actual = head;
    int contador = 0;
    while (contador < pos) {
        if (actual == tail->getSiguiente()) 
            return valorPorDefecto; 
        actual = actual->getSiguiente();
        contador++;
    }

    return actual->getElemento();
    
}
template<typename T>
int ListaCircularDoble<T>::existe(T elemento) {
    if (longitud == 0)
        return -1; // Lista vacía

    NodoDoble<T> *actual = head;
    int pos = 0;

    for (int i = 0; i < longitud; ++i) { // Recorrer la lista circular longitud veces
        if (actual->getElemento() == elemento)
            return pos; // Elemento encontrado
        actual = actual->getSiguiente();
        pos++;
    }
    return -1; // Elemento no encontrado
}
// Método para concatenar dos listas circulares en una nueva
template<typename T>
ListaCircularDoble<T> ListaCircularDoble<T>::concatenar(const ListaCircularDoble<T> &target) {
    ListaCircularDoble<T> resultado(*this); // Inicia resultado como una copia de la lista actual.

    if (target.longitud == 0) 
        return resultado;

    NodoDoble<T> *actualTarget = target.head;
    for (int i = 0; i < target.longitud; ++i) {
        resultado.insertarAlFinal(actualTarget->getElemento());
        actualTarget = actualTarget->getSiguiente();
    }
    return resultado;
}

template<typename T>
bool ListaCircularDoble<T>::esVacia() const {
    return head == NULL;
}

// Método para imprimir todos los elementos de la lista (sentido horario)
template<typename T>
void ListaCircularDoble<T>::imprimirLista() {
    cout << endl;

    if (head == NULL) {
        cout << "La lista esta vacia." ;
        return;
    }

    NodoDoble<T> *actual = head;
    do {
        cout << actual->getElemento()<<" ";
        actual = actual->getSiguiente();
    } while (actual != head);
}

// Nuevo método para imprimir en sentido inverso (anti-horario)
template<typename T>
void ListaCircularDoble<T>::imprimirListaInversa() {
    cout << endl;

    if (head == NULL) {
        cout << "La lista esta vacia." ;
        return;
    }

    NodoDoble<T> *actual = tail; // Comenzar desde tail para ir hacia atrás
    do {
        cout << actual->getElemento();
        actual = actual->getAnterior()<<" ";
    } while (actual != tail); // Iterar hasta volver al tail
}

template<typename T>
void ListaCircularDoble<T>::invertir(){
    if(head == NULL || head==tail)
        return;

    NodoDoble<T>* actual=head;
    NodoDoble<T>* aux=NULL;
    
    do
    {
        aux = actual->getAnterior();
        actual->setAnterior(actual->getSiguiente());
        actual->setSiguiente(aux);

        actual = actual->getAnterior();
    } while (actual !=head);

    aux=head;
    head=tail;
    tail=aux;
    head->setAnterior(tail);
    tail->setSiguiente(head);

}
#endif