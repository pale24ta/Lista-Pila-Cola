#ifndef LISTADOBLEHPP
#define LISTADOBLEHPP

#include <iostream>
#include "nodoDoble.hpp" 

template<typename T>
class ListaDoble { // Renombrado para claridad: Lista Doblemente Enlazada
private:
    NodoDoble<T> *head;
    NodoDoble<T> *tail;
    int longitud;

    // Método auxiliar privado para liberar la memoria
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

    //setters y getters ( getHead y getTail rompen encapsulamiento)
    NodoDoble<T>* getHead() ;
    NodoDoble<T>* getTail() ;
    int getLongitud() const;
    T getElementoHead() const;
    T getElementoTail() const;

    // Setters para head/tail (usar con precaución, pueden romper la integridad de la lista si se usan mal)
    void setHead(NodoDoble<T> *nuevaHead);
    void setTail(NodoDoble<T> *nuevaTail);

    // Métodos de modificación
    void insertarEnPosicion(T elemento, int pos);
    void insertarAlFinal(T elemento);
    void eliminarPorPosicion(int pos);
    void eliminarAlFinal();

    // Métodos de consulta
    T consultar(int pos);
    int buscar(T elemento);

    ListaDoble<T> concatenar(const ListaDoble<T> &target);
    bool esVacia() const;
    void imprimirLista();
    void imprimirListaInversa(); // Nuevo: para listas doblemente enlazadas
    void invertir(); 
    // Funciones adicionales
    void intercambiar(int pos1, int pos2);
    static ListaDoble<T> sortedIntersect(ListaDoble<T> a, ListaDoble<T> b);
};

// --- Implementaciones ---

template<typename T>
ListaDoble<T>::ListaDoble() : head(nullptr), tail(nullptr), longitud(0) {}

template<typename T>
ListaDoble<T>::ListaDoble(const ListaDoble<T> &target) : head(nullptr), tail(nullptr), longitud(0) {
    if (target.head == nullptr)
        return;

    NodoDoble<T> *nodoActualTarget = target.head;
    while (nodoActualTarget != nullptr) {
        insertarAlFinal(nodoActualTarget->getElemento());
        nodoActualTarget = nodoActualTarget->getSiguiente();
    }
}

template<typename T>
ListaDoble<T>& ListaDoble<T>::operator=(const ListaDoble<T>& target) {
    ListaDoble<T> aux(target);
    std::swap(aux.head, head);
    std::swap(aux.tail, tail);
    std::swap(aux.longitud, longitud);
    return *this;
}

template<typename T>
ListaDoble<T>::~ListaDoble() {
    liberarLista();
}

template<typename T>
void ListaDoble<T>::liberarLista() {
    NodoDoble<T> *actual = head;
    NodoDoble<T> *temp = nullptr;
    while (actual != nullptr) {
        temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    longitud = 0;
}

template<typename T>
NodoDoble<T>* ListaDoble<T>::getHead(){ return head; }

template<typename T>
NodoDoble<T>* ListaDoble<T>::getTail() { return tail; }

template<typename T>
int ListaDoble<T>::getLongitud() const { return longitud; }

template<typename T>
void ListaDoble<T>::setHead(NodoDoble<T> *nuevaHead) { head = nuevaHead; }

template<typename T>
void ListaDoble<T>::setTail(NodoDoble<T> *nuevaTail) { tail = nuevaTail; }

template<typename T>
T ListaDoble<T>::getElementoHead() const {
    if (head == nullptr) return T(); // Devuelve un valor por defecto si la lista está vacía
    return head->getElemento();
}

template<typename T>
T ListaDoble<T>::getElementoTail() const {
    if (tail == nullptr) return T(); // Devuelve un valor por defecto si la lista está vacía
    return tail->getElemento();
}

template<typename T>
void ListaDoble<T>::insertarEnPosicion(T elemento, int pos) {
    if (pos > longitud) pos = longitud;
    if (pos < 0) pos = 0;

    NodoDoble<T> *nuevo = new NodoDoble<T>(elemento);

    if (longitud == 0) { // Caso: Lista vacía
        head = nuevo;
        tail = nuevo;
    } else if (pos == 0) { // Caso: Insertar al principio
        nuevo->setSiguiente(head);
        head->setAnterior(nuevo);
        head = nuevo;
    } else if (pos == longitud) { // Caso: Insertar al final (optimización, también puede manejarse por el caso general)
        tail->setSiguiente(nuevo);
        nuevo->setAnterior(tail);
        tail = nuevo;
    } else { // Caso: Insertar en el medio
        NodoDoble<T> *actual = head;
        // Recorrer hasta el nodo ANTERIOR al punto de inserción
        for (int i = 0; i < pos - 1; i++) {
            actual = actual->getSiguiente();
        }
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
void ListaDoble<T>::insertarAlFinal(T elemento) {
    NodoDoble<T> *nuevo = new NodoDoble<T>(elemento);
    if (longitud == 0) {
        head = nuevo;
        tail = nuevo;
    } else {
        tail->setSiguiente(nuevo);
        nuevo->setAnterior(tail);
        tail = nuevo;
    }
    longitud++;
}

template<typename T>
void ListaDoble<T>::eliminarPorPosicion(int pos) {
    if (longitud == 0) return;

    if (pos < 0) pos = 0;
    else if (pos >= longitud) pos = longitud - 1;

    NodoDoble<T> *nodoAEliminar = nullptr;

    if (longitud == 1) { // Caso: Un solo elemento
        nodoAEliminar = head;
        head = nullptr;
        tail = nullptr;
    } else if (pos == 0) { // Caso: Eliminar head
        nodoAEliminar = head;
        head = head->getSiguiente();
        head->setAnterior(nullptr); // El 'anterior' del nuevo head es nulo
    } else if (pos == longitud - 1) { // Caso: Eliminar tail
        nodoAEliminar = tail;
        tail = tail->getAnterior();
        tail->setSiguiente(nullptr); // El 'siguiente' del nuevo tail es nulo
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
void ListaDoble<T>::eliminarAlFinal() {
    eliminarPorPosicion(longitud - 1); // Reutiliza la eliminación por posición
}
template<typename T>
T ListaDoble<T>::consultar(int pos){ //propenso a errores
    // Si la posición es válida, se procede a buscar el nodo.
    if(!esVacia()){
        if(pos > longitud){
            return tail->getElemento();
        }
        else{
            if(pos <= 0){
                return head->getElemento();
            }
        }
        NodoDoble<T>* actual = head;
        for (int i = 1; i < pos; i++)
            actual=actual->getSiguiente();
        
        return actual->getElemento();
        

    }
    else
        return T(); //retorna valor por defecto
}
template<typename T>
int ListaDoble<T>::buscar(T elemento) {
    if (longitud == 0) return -1;

    NodoDoble<T> *actual = head;
    int pos = 0;
    while (actual != nullptr) {
        if (actual->getElemento() == elemento)
            return pos;
        actual = actual->getSiguiente();
        pos++;
    }
    return -1;
}

template<typename T>
bool ListaDoble<T>::esVacia() const {
    return head == nullptr;
}

template<typename T>
ListaDoble<T> ListaDoble<T>::concatenar(const ListaDoble<T> &target) {
    ListaDoble<T> resultado(*this); // Inicia con una copia de la lista actual.

    NodoDoble<T> *actualTarget = target.head;
    while (actualTarget != nullptr) {
        resultado.insertarAlFinal(actualTarget->getElemento());
        actualTarget = actualTarget->getSiguiente();
    }
    return resultado;
}

template<typename T>
void ListaDoble<T>::imprimirLista() {
    std::cout << std::endl;
    if (head == nullptr) {
        std::cout << "La lista esta vacia." << std::endl;
        return;
    }
    NodoDoble<T> *actual = head;
    while (actual != nullptr) {
        std::cout << actual->getElemento() << std::endl;
        actual = actual->getSiguiente();
    }
}

template<typename T>
void ListaDoble<T>::imprimirListaInversa() {
    std::cout << std::endl;
    if (tail == nullptr) { // Verificar tail, ya que comenzamos desde él
        std::cout << "La lista esta vacia." << std::endl;
        return;
    }
    NodoDoble<T> *actual = tail;
    while (actual != nullptr) {
        std::cout << actual->getElemento() << std::endl;
        actual = actual->getAnterior();
    }
}
template<typename T>
void ListaDoble<T>::invertir(){
    if(head== nullptr || head == tail)
        return;
    
    NodoDoble<T>* actual=head;
    NodoDoble<T>* aux=nullptr;

    while(actual != nullptr){
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
    if (nodo1 != nullptr && nodo2 != nullptr) {
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