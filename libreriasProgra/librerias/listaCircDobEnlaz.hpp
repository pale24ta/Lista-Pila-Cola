#ifndef LISTACIRCULARDOBLE
#define LISTACIRCULARDOBLE

#include "nodoDoble.hpp" 
#include <iostream>
#include <utility> // Para std::swap

template<typename T>
class ListaCircularDoble { 
private:
    NodoDoble<T> *head;
    NodoDoble<T> *tail;
    int longitud;

    // Método auxiliar privado para liberar la memoria
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
    NodoDoble<T>* getHead() ;
    NodoDoble<T>* getTail() ;
    int getLongitud() const;

    // Métodos para obtener elementos (añadidos para conveniencia)
    T getElementoHead() const;
    T getElementoTail() const;

    // Métodos de modificación
    void insertarEnPosicion(T elemento, int pos);
    void insertarAlFinal(T elemento);
    void eliminarPorPosicion(int pos);
    void eliminarAlFinal();
    void intercambiar(int pos1, int pos2);

    // Métodos de consulta
    T consultar(int pos); // Con lógica para abordar errores
    int buscar(T elemento); // Devuelve -1 si no está, devuelve la posición del elemento
    ListaCircularDoble<T> concatenar(const ListaCircularDoble<T> &target); // Toma la lista original y la concatena con la lista target y devuelve la lista concatenada
    bool esVacia() const;
    void imprimirLista();
    // Nuevo método para imprimir en sentido inverso (para demostración de doble enlace)
    void imprimirListaInversa();
    void invertir();
};

// --- Implementaciones de los Métodos ---

// Constructor por defecto
template<typename T>
ListaCircularDoble<T>::ListaCircularDoble() : head(nullptr), tail(nullptr), longitud(0) {}

// Constructor de copia
template<typename T>
ListaCircularDoble<T>::ListaCircularDoble(const ListaCircularDoble<T> &target) : head(nullptr), tail(nullptr), longitud(0) {
    if (target.head == nullptr) {
        return; // Lista original vacía, no hay nada que copiar.
    }

    NodoDoble<T> *actualTarget = target.head;
    // Iteramos 'longitud' veces para copiar todos los elementos.
    // Reutilizamos insertarAlFinal, que ahora se adaptará a doble enlace.
    for (int i = 0; i < target.longitud; ++i) {
        insertarAlFinal(actualTarget->getElemento());
        actualTarget = actualTarget->getSiguiente();
    }
}

// Operador de asignación (usando la técnica copy-and-swap)
template<typename T>
ListaCircularDoble<T>& ListaCircularDoble<T>::operator=(const ListaCircularDoble<T>& target) {
    ListaCircularDoble<T> aux(target); // Usa el constructor de copia
    std::swap(aux.head, head);
    std::swap(aux.tail, tail);
    std::swap(aux.longitud, longitud);
    return *this;
}

// Destructor de la lista
template<typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    liberarLista();
}

// Método para liberar toda la memoria de la lista
template<typename T>
void ListaCircularDoble<T>::liberarLista() {
    if (head == nullptr)
        return; // La lista ya está vacía

    // Rompemos la circularidad para evitar bucles infinitos en el borrado.
    // Establecemos el puntero 'siguiente' del tail a nullptr para el borrado secuencial.
    tail->setSiguiente(nullptr);

    NodoDoble<T> *actual = head;
    NodoDoble<T> *siguiente = nullptr;

    while (actual != nullptr) {
        siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    head = nullptr;
    tail = nullptr;
    longitud = 0;
}

// Getters
template<typename T>
NodoDoble<T>* ListaCircularDoble<T>::getHead()  {
    return head;
}

template<typename T>
NodoDoble<T>* ListaCircularDoble<T>::getTail()  {
    return tail;
}

template<typename T>
int ListaCircularDoble<T>::getLongitud() const {
    return longitud;
}

// Métodos para obtener elementos de head/tail
template<typename T>
T ListaCircularDoble<T>::getElementoHead() const {
    if (longitud == 0) {
        return T();
    }
    return head->getElemento();
}

template<typename T>
T ListaCircularDoble<T>::getElementoTail() const {
    if (longitud == 0)
        return T();
    return tail->getElemento();
}

// Método para insertar un elemento en una posición específica
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
        nuevo->setSiguiente(head); // Se apunta a sí mismo
        nuevo->setAnterior(head);  // También se apunta a sí mismo por el anterior
    } else if (pos == 0) { // Caso 2: Insertar al principio (nueva head)
        nuevo->setSiguiente(head);
        head->setAnterior(nuevo); // El antiguo head apunta hacia atrás al nuevo nodo
        head = nuevo;
        head->setAnterior(tail);  // La nueva head apunta hacia atrás al tail
        tail->setSiguiente(head); // El tail apunta hacia adelante a la nueva head
    } else { // Caso 3: Insertar en otro lugar (medio o final)
        NodoDoble<T> *actual = head;
        for (int i = 0; i < pos - 1; i++)
            actual = actual->getSiguiente();

        // Enlace del nuevo nodo
        nuevo->setSiguiente(actual->getSiguiente());
        nuevo->setAnterior(actual);

        // Enlace del nodo anterior (actual)
        actual->setSiguiente(nuevo);

        // Enlace del nodo siguiente al nuevo
        nuevo->getSiguiente()->setAnterior(nuevo);

        if (pos == longitud) { // Si se insertó al final, actualizar tail
            tail = nuevo;
            // La circularidad ya está garantizada por los enlaces
            // tail->siguiente ya apunta a head, y head->anterior a tail.
        }
    }
    longitud++;
}

// Método para insertar un elemento al final de la lista
template<typename T>
void ListaCircularDoble<T>::insertarAlFinal(T elemento) {
    NodoDoble<T> *nuevo = new NodoDoble<T>(elemento);

    if (longitud == 0) { // Caso 1: Lista vacía
        head = nuevo;
        tail = nuevo;
        nuevo->setSiguiente(head); // Se apunta a sí mismo
        nuevo->setAnterior(head);  // También se apunta a sí mismo
    } else { // Caso 2: La lista no está vacía
        tail->setSiguiente(nuevo); // El 'siguiente' del tail actual apunta al nuevo nodo
        nuevo->setAnterior(tail);  // El nuevo nodo apunta hacia atrás al tail actual
        tail = nuevo;              // El nuevo nodo se convierte en el nuevo tail
        tail->setSiguiente(head);  // El 'siguiente' del nuevo tail apunta a head
        head->setAnterior(tail);   // Y el 'anterior' de head apunta al nuevo tail
    }
    longitud++;
}

// Método para eliminar un elemento por su posición
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
        head = nullptr;
        tail = nullptr;
    } else { // Lista con más de un elemento
        NodoDoble<T> *previo = nullptr;
        NodoDoble<T> *siguiente = nullptr;

        if (pos == 0) { // Caso 2: Eliminando el head (posición 0)
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

// Método para eliminar el último elemento de la lista
template<typename T>
void ListaCircularDoble<T>::eliminarAlFinal() {
    eliminarPorPosicion(longitud - 1); // Reutilizamos eliminarPorPosicion
}

// Método para intercambiar elementos entre dos posiciones
template<typename T>
void ListaCircularDoble<T>::intercambiar(int pos1, int pos2) {
    if (longitud <= 1 || pos1 == pos2) {
        return;
    }

    if (pos1 < 0 || pos2 < 0 || pos1 >= longitud || pos2 >= longitud) {
        std::cout << "\nPosiciones invalidas, imposible intercambiar\n";
        return;
    }

    NodoDoble<T> *actual = head;
    NodoDoble<T> *nodo1 = nullptr;
    NodoDoble<T> *nodo2 = nullptr;

    for (int i = 0; i < longitud; ++i) { // Recorrer todos los nodos de la circular
        if (i == pos1)
            nodo1 = actual;
        if (i == pos2)
            nodo2 = actual;
        if (nodo1 != nullptr && nodo2 != nullptr)
            break; // Salir si ambos nodos fueron encontrados

        actual = actual->getSiguiente();
    }
    // Intercambiar los elementos (valores) de los nodos
    T aux = nodo1->getElemento();
    nodo1->setElemento(nodo2->getElemento());
    nodo2->setElemento(aux);
}

// Método para consultar el elemento en una posición específica
template<typename T>
T ListaCircularDoble<T>::consultar(int pos){ //propenso a errores
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

// Método para buscar un elemento y devolver su posición
template<typename T>
int ListaCircularDoble<T>::buscar(T elemento) {
    if (longitud == 0)
        return -1; // Lista vacía

    NodoDoble<T> *actual = head;
    int pos = 0;

    for (int i = 0; i < longitud; ++i) { // Recorrer la lista circular 'longitud' veces
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
    ListaCircularDoble<T> resultado(*this); // Inicia 'resultado' como una copia de la lista actual.

    if (target.longitud == 0) {
        return resultado;
    }

    NodoDoble<T> *actualTarget = target.head;
    for (int i = 0; i < target.longitud; ++i) {
        resultado.insertarAlFinal(actualTarget->getElemento());
        actualTarget = actualTarget->getSiguiente();
    }
    return resultado;
}

// Método para verificar si la lista está vacía
template<typename T>
bool ListaCircularDoble<T>::esVacia() const {
    return head == nullptr;
}

// Método para imprimir todos los elementos de la lista (sentido horario)
template<typename T>
void ListaCircularDoble<T>::imprimirLista() {
    std::cout << std::endl;

    if (head == nullptr) {
        std::cout << "La lista esta vacia." << std::endl;
        return;
    }

    NodoDoble<T> *actual = head;
    do {
        std::cout << actual->getElemento() << std::endl;
        actual = actual->getSiguiente();
    } while (actual != head);
}

// Nuevo método para imprimir en sentido inverso (anti-horario)
template<typename T>
void ListaCircularDoble<T>::imprimirListaInversa() {
    std::cout << std::endl;

    if (head == nullptr) {
        std::cout << "La lista esta vacia." << std::endl;
        return;
    }

    NodoDoble<T> *actual = tail; // Comenzamos desde tail para ir hacia atrás
    do {
        std::cout << actual->getElemento() << std::endl;
        actual = actual->getAnterior();
    } while (actual != tail); // Iteramos hasta volver al tail
}

template<typename T>
void ListaCircularDoble<T>::invertir(){
    if(head == nullptr || head==tail)
        return;

    NodoDoble<T>* actual=head;
    NodoDoble<T>* aux=nullptr;
    
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