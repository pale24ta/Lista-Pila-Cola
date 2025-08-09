#ifndef LISTACIRCULAR
#define LISTACIRCULAR

#include "nodo.hpp" 
#include <iostream>  
#include <utility>   // para swap c++ 11
#include <algorithm> //para swap c++ 98

using namespace std; 

template<typename T>
class ListaCircular{
private:
    Nodo<T> *head, *tail;
    int longitud;

    void liberarLista(); 

public:
    ListaCircular();
    // Constructor de copia
    ListaCircular(const ListaCircular<T> &target);
    // Operador de asignación
    ListaCircular<T>& operator=(const ListaCircular<T>& target);
    // Destructor
    ~ListaCircular();
    // Métodos clásicos (getters y setters)
    int getLongitud() const;

    const T& getElementoHead() const;
    const T& getElementoTail() const;
    // Métodos de modificación
    void insertarEnPosicion(T elemento, int pos);
    void eliminarPorPosicion(int pos);
    bool esVacia()const;
    void intercambiar(int pos1, int pos2);
    // Métodos de consulta
    T& consultar(int pos); // Con lógica para abordar errores
    const T& consultar(int pos) const; 
    int buscar(T elemento); // Devuelve -1 si no está, devuelve la posición del elemento
    ListaCircular<T> concatenar(const ListaCircular<T> &target); 
    void imprimirLista();
    void invertir()
};
template<typename T>
ListaCircular<T>::ListaCircular():head(NULL), tail(NULL), longitud(0){}
// Constructor de copia
template<typename T>
ListaCircular<T>::ListaCircular(const ListaCircular<T> &target) : head(NULL), tail(NULL), longitud(0) {
    if (target.head == NULL) 
        return; // Lista original vacía, no hay nada que copiar.
    Nodo<T> *actualTarget = target.head;
    // Itera 'longitud' veces para copiar todos los elementos.
    for (int i = 0; i < target.longitud; ++i) {
        insertarEnPosicion(actualTarget->getElemento(), longitud);
        actualTarget = actualTarget->getSiguiente();
    }
}
template<typename T>
ListaCircular<T>& ListaCircular<T>::operator=(const ListaCircular<T>& target){
    if(this != target){
        ListaCircular<T> aux(target); // Usa el constructor de copia
        swap(aux.head, head);
        swap(aux.tail, tail);
        swap(aux.longitud, longitud);
    
    }
    return *this;
}
// Destructor de la lista
template<typename T>
ListaCircular<T>::~ListaCircular(){ 
    liberarLista();
}
template<typename T>
void ListaCircular<T>::liberarLista(){
    if (head == NULL) 
        return; // La lista ya está vacía
    Nodo<T> *actual = head;
    Nodo<T> *siguiente = NULL;

    for (int i = 0; i < longitud; ++i) {
        siguiente = actual->getSiguiente(); 
        delete actual; 
        actual = siguiente;
    }
    head = NULL;
    tail = NULL;
    longitud = 0;
}
// Getters
template<typename T>
int ListaCircular<T>::getLongitud() const{
    return longitud;
}
template<typename T>
const T& ListaCircular<T>::getElementoHead() const {
    static const T valorPorDefecto = T();
    if(head == NULL)
        return valorPorDefecto;
    return head->getElemento();
}
template<typename T>
const T& ListaCircular<T>::getElementoTail() const {
    static const T valorPorDefecto = T();
    if(tail == NULL)
        return valorPorDefecto;
    return tail->getElemento();
}
template<typename T>
void ListaCircular<T>::insertarEnPosicion(T elemento, int pos) {
    // Ajustar posición si es inválida
    if (pos > longitud) 
        pos = longitud;
    if (pos < 0) 
        pos = 0;

    Nodo<T> *nuevo = new Nodo<T>(elemento);

    if (longitud == 0) { // Caso 1: Lista vacía
        head = nuevo;
        tail = nuevo;
        nuevo->setSiguiente(head);
    } 
    else if (pos == 0) { // Caso 2: Insertar al principio
        nuevo->setSiguiente(head);
        head = nuevo;
        tail->setSiguiente(head);
    } 
    else if (pos == longitud) { // Caso 3: Insertar al final 
        nuevo->setSiguiente(head); 
        tail->setSiguiente(nuevo);
        tail = nuevo;
    } 
    else { // Caso 4: Insertar en medio
        Nodo<T> *actual = head;
        for (int i = 0; i < pos - 1; i++) 
            actual = actual->getSiguiente();
        
        nuevo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevo);
    }
    longitud++;
}
template<typename T>
void ListaCircular<T>::eliminarPorPosicion(int pos) {
    if (longitud == 0) 
        return; // Lista vacía, nada que eliminar.
    // Ajustar posición si es inválida
    if (pos < 0) 
        pos = 0;
    else if (pos >= longitud) 
        pos = longitud - 1; //se coloca en longitud - 1 por que el actual debe posicionarse
        //un nodo antes del nodo a eliminar
    Nodo<T> *nodoAEliminar;

    if (longitud == 1) { // Caso 1: Eliminar el único nodo
        nodoAEliminar = head;
        head = NULL;
        tail = NULL;
    } 
    else if (pos == 0) { // Caso 2: Eliminar el head (posición 0)
        nodoAEliminar = head;
        head = head->getSiguiente();
        tail->setSiguiente(head); // Mantener circularidad
    } 
    else if (pos == longitud - 1) { // Caso 3: Eliminar el tail 
        Nodo<T> *actual = head;
        //se usa un while por que actual debe apuntar a un nodo antes que el tail para eliminar
        while (actual->getSiguiente() != tail) // Avanzar hasta el nodo anterior al tail
            actual = actual->getSiguiente();
        
        nodoAEliminar = tail;
        actual->setSiguiente(head); // El nuevo tail es 'actual'
        tail = actual;
    } 
    else { // Caso 4: Eliminar nodo intermedio
        Nodo<T> *actual = head;
        for (int i = 0; i < pos - 1; i++)
            actual = actual->getSiguiente();
        
        nodoAEliminar = actual->getSiguiente();
        actual->setSiguiente(nodoAEliminar->getSiguiente());
    }

    delete nodoAEliminar;
    longitud--;
}
// Método para intercambiar elementos entre dos posiciones
template<typename T>
void ListaCircular<T>::intercambiar(int pos1, int pos2){
    if (longitud <= 1 || pos1 == pos2) 
        return;

    if (pos1 < 0 || pos2 < 0 || pos1 >= longitud || pos2 >= longitud) {
        cout << "\nPosiciones invalidas, imposible intercambiar\n"; 
        return;
    }

    Nodo<T> *actual = head;
    Nodo<T> *nodo1 = NULL;
    Nodo<T> *nodo2 = NULL;

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
T& ListaCircular<T>::consultar(int pos) {
    
    static T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;

    if (pos <= 0) 
        return head->getElemento();
    if (pos > longitud) {
        pos = pos % longitud;  
        if (pos == 0) return tail->getElemento();
    }

    Nodo<T>* actual = head;
    for (int i = 0; i < pos; ++i) {
        if (actual == NULL) 
            return valorPorDefecto;  
        actual = actual->getSiguiente();
        
        if (actual == head) 
            return valorPorDefecto;
    }

    if (actual != NULL) 
        return actual->getElemento();
    
    return valorPorDefecto;
}
template<typename T>
const T& ListaCircular<T>::consultar(int pos) const {
    
    static const T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;

    
    if (pos <= 0) 
        return head->getElemento();
    if (pos > longitud) {
        pos = pos % longitud;  // Aprovecharr la circularidad
        if (pos == 0) 
            return tail->getElemento();
    }

    Nodo<T>* actual = head;
    for (int i = 0; i < pos; ++i) {
        if (actual == NULL) 
            return valorPorDefecto;
        actual = actual->getSiguiente();
        if (actual == head) 
            return valorPorDefecto;
    }

    if (actual != NULL) 
        return actual->getElemento();
    
    return valorPorDefecto;
}
template<typename T>
int ListaCircular<T>::buscar(T elemento) {
    if (longitud == 0) 
        return -1; // Lista vacía
    Nodo<T> *actual = head;
    int pos = 0;

    for (int i = 0; i < longitud; ++i) { // Recorrer la lista circular longitud veces
        if (actual->getElemento() == elemento) 
            return pos; 
        actual = actual->getSiguiente();
        pos++;
    }
    return -1; // Elemento no encontrado
}
// Método para concatenar dos listas circulares en una nueva
template<typename T>
ListaCircular<T> ListaCircular<T>::concatenar(const ListaCircular<T> &target){
    ListaCircular<T> resultado(*this); // Inicia resultado como una copia de la lista actual.
    // Esto maneja el caso donde la lista actual está vacía o no.
    if (target.longitud == 0) 
        return resultado; // Si target está vacía, resultado es solo la copia de la lista actual.

    // Si la lista actual estaba vacía, resultado es una lista vacía.
    // En ese caso se nevesita contenga los elementos de target.

    Nodo<T> *actual_target = target.head;
    // El bucle va de 0 a longitud-1 de target para copiar todos sus elementos.
    for (int i = 0; i < target.longitud; ++i) {
        resultado.insertarEnPosicion(actual_target->getElemento(), longitud);
        actual_target = actual_target->getSiguiente();
    }
    return resultado;
}
template<typename T>
bool ListaCircular<T>::esVacia() const{
    return head == NULL; 
}
template<typename T> 
void ListaCircular<T>::imprimirLista(){
    cout <<endl; 
    
    if (head == NULL) {
        cout << "La lista esta vacia." <<endl;
        return;
    }
    Nodo<T> *actual = head;
    // Usamos un bucle do-while para asegurar que el head se imprima
    // y para detenerse cuando se vuelvaa a él.
    do {
        cout << actual->getElemento(); 
        actual = actual->getSiguiente();     
    } while (actual != head); 
}
template<typename T>
void ListaCircular<T>::invertir(){

    if(head == NULL || head==tail)
        return;
    
    Nodo<T>* anterior=NULL;
    Nodo<T>* siguiente=NULL;
    Nodo<T>* actual=head;
    Nodo<T>* headOriginal=head;

    do{
        siguiente = actual->getSiguiente();
        actual->setSiguiente(anterior);
        anterior=actual;
        actual=siguiente;
    } while (actual != headOriginal);// termina cuando vuelve al inicio

    head = tail;
    head=anterior;
    tail->setSiguiente(head);
}

#endif 