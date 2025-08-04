#ifndef LISTACIRCULAR
#define LISTACIRCULAR

#include "nodo.hpp" 
#include <iostream>  
#include <utility>   // Para std::swap

using namespace std; 

template<typename T>
class ListaCircular{
private:
    Nodo<T> *head, *tail;
    int longitud;

    // Método auxiliar privado para liberar la memoria
    void liberarLista(); 

public:
    // Constructor por defecto
    ListaCircular();
    // Constructor de copia
    ListaCircular(const ListaCircular<T> &target);
    // Operador de asignación
    ListaCircular<T>& operator=(const ListaCircular<T>& target);
    // Destructor
    ~ListaCircular();
    // Métodos clásicos (getters y setters)
    Nodo<T> *getHead(); 
    Nodo<T> *getTail(); 
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
    ListaCircular<T> concatenar(const ListaCircular<T> &target); // Toma la lista original y la concatena con la lista target y devuelve la lista concatenada
    bool esVacia() const;
    void imprimirLista();
    void invertir();// invierte el orden de la lista
};

// --- Implementaciones de los Métodos ---
// Constructor por defecto
template<typename T>
ListaCircular<T>::ListaCircular():head(nullptr), tail(nullptr), longitud(0){}
// Constructor de copia
template<typename T>
ListaCircular<T>::ListaCircular(const ListaCircular<T> &target) : head(nullptr), tail(nullptr), longitud(0) {
    if (target.head == nullptr) {
        return; // Lista original vacía, no hay nada que copiar.
    }

    Nodo<T> *actualTarget = target.head;
    // Itera 'longitud' veces para copiar todos los elementos.
    for (int i = 0; i < target.longitud; ++i) {
        insertarAlFinal(actualTarget->getElemento()); // Reutiliza insertarAlFinal
        actualTarget = actualTarget->getSiguiente();
    }
}
// Operador de asignación (usando la técnica copy-and-swap)
template<typename T>
ListaCircular<T>& ListaCircular<T>::operator=(const ListaCircular<T>& target){
    ListaCircular<T> aux(target); // Usa el constructor de copia
    std::swap(aux.head, head);
    std::swap(aux.tail, tail);
    std::swap(aux.longitud, longitud);
    return *this;
}
// Destructor de la lista
template<typename T>
ListaCircular<T>::~ListaCircular(){ 
    liberarLista();
}
// Método para liberar toda la memoria de la lista
template<typename T>
void ListaCircular<T>::liberarLista(){
    if (head == nullptr) 
        return; // La lista ya está vacía
    Nodo<T> *actual = head;
    Nodo<T> *siguiente = nullptr;

    for (int i = 0; i < longitud; ++i) {
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
Nodo<T>* ListaCircular<T>::getHead(){ 
    return head;
}
template<typename T>
Nodo<T>* ListaCircular<T>::getTail(){
    return tail;
}
template<typename T>
int ListaCircular<T>::getLongitud() const{
    return longitud;
}
// Métodos para obtener elementos de head/tail (implementados para conveniencia)
template<typename T>
T ListaCircular<T>::getElementoHead() const {
    if (longitud == 0) {
        return T(); 
    }
    return head->getElemento();
}
template<typename T>
T ListaCircular<T>::getElementoTail() const {
    if (longitud == 0)
        return T(); 
    return tail->getElemento();
}
// Método para insertar un elemento en una posición específica
template<typename T>
void ListaCircular<T>::insertarEnPosicion(T elemento, int pos) {
    // Si pos es mayor que la longitud actual, se ajusta para insertar al final.
    if (pos > longitud) 
        pos = longitud;
    // Si pos es menor que 0, se ajusta para insertar al principio.
    if (pos < 0) 
        pos = 0;
    Nodo<T> *nuevo = new Nodo<T>(elemento);

    if (longitud == 0) { // Caso 1: ListaCircular vacía
        head = nuevo;
        tail = nuevo;
        nuevo->setSiguiente(head); // Se apunta a sí mismo para ser circular
    } else if (pos == 0) { // Caso 2: Insertar al principio (nueva head)
        nuevo->setSiguiente(head);
        head = nuevo;
        tail->setSiguiente(head); //el siguiente de tail debe apuntar a la nueva head
    } else { // Caso 3: Insertar en otro lugar (medio o final)
        Nodo<T> *actual = head;
        // Avanzamos hasta el nodo ANTERIOR a la posición de inserción
        for (int i = 0; i < pos - 1; i++) 
            actual = actual->getSiguiente();
        
        nuevo->setSiguiente(actual->getSiguiente()); // El nuevo nodo apunta al siguiente del actual
        actual->setSiguiente(nuevo);                 // El actual apunta al nuevo nodo

        if (pos == longitud) { // Si la inserción fue al final, actualizamos tail
            tail = nuevo;
            // No es necesario: tail->setSiguiente(head); porque ya lo hizo insertarAlFinal
            // o porque el nuevo nodo fue insertado justo antes de donde tail apuntaba a head.
            // La circularidad se mantiene si el 'actual' previo a 'nuevo' era el viejo tail,
            // o si el 'nuevo' se convierte en el nuevo tail, su setSiguiente debería ser head.
            // Dada la lógica, si pos == longitud, 'actual' era el viejo tail.
            // Ahora 'nuevo' es el último, y su siguiente ya apunta al antiguo siguiente de tail (que era head).
            // Por lo tanto, nuevo es el nuevo tail, y su siguiente es head. Esto es correcto.
        }
    }
    longitud++;
}
// Método para insertar un elemento al final de la lista
template<typename T>
void ListaCircular<T>::insertarAlFinal(T elemento) {
    Nodo<T> *nuevo = new Nodo<T>(elemento);

    if (longitud == 0) { // Caso 1: ListaCircular vacía
        head = nuevo;
        tail = nuevo;
        nuevo->setSiguiente(head); // El único nodo se apunta a sí mismo
    } else { // Caso 2: La lista no está vacía
        tail->setSiguiente(nuevo); // El 'siguiente' del tail actual debe apuntar al nuevo nodo
        tail = nuevo;              // El nuevo nodo se convierte en el nuevo tail
        tail->setSiguiente(head); // El 'siguiente' del nuevo tail debe apuntar de nuevo a head
    }
    longitud++;
}
// Método para eliminar un elemento por su posición
template<typename T>
void ListaCircular<T>::eliminarPorPosicion(int pos){
    if (longitud == 0) 
        return; // La lista está vacía, no se puede eliminar.
    // Asegurar que 'pos' esté dentro de los límites válidos para eliminación: [0, longitud - 1].
    if (pos < 0) { 
        pos = 0; // Si la posición es negativa, elimina el primer elemento.
    } else if (pos >= longitud) { 
        pos = longitud - 1; // Si la posición es igual o mayor a la longitud, elimina el último elemento.
    }
    Nodo<T> *nodoAEliminar;
    if (longitud == 1) { // Caso 1: Eliminando el único elemento de la lista.
        nodoAEliminar = head;
        head = nullptr;
        tail = nullptr;
    } else if (pos == 0) { // Caso 2: Eliminando el head (posición 0) de una lista con más de un elemento.
        nodoAEliminar = head;
        head = head->getSiguiente(); // El nuevo head es el siguiente del anterior head
        tail->setSiguiente(head);    //  el tail debe apuntar al nuevo head para mantener la circularidad
    } else { // Caso 3: Eliminando un nodo en una posición intermedia o el tail.
        Nodo<T> *actual = head;
        for (int i = 0; i < pos - 1; i++)
            actual = actual->getSiguiente();
        nodoAEliminar = actual->getSiguiente(); // El nodo a eliminar es el siguiente de 'actual'
        actual->setSiguiente(nodoAEliminar->getSiguiente()); // Conectar el nodo anterior con el nodo posterior
        if (nodoAEliminar == tail) { // Si el nodo eliminado era el tail, actualizamos el puntero 'tail'
            tail = actual;           // El nuevo tail es el nodo anterior al eliminado
            // No es necesario: tail->setSiguiente(head); porque ya está enlazado a head por la circularidad previa
            // y porque 'actual' es ahora el nuevo tail, y su siguiente ya apunta al head.
        }
    }
    delete nodoAEliminar;
    longitud--;
}
// Método para eliminar el último elemento de la lista
template<typename T>
void ListaCircular<T>::eliminarAlFinal(){
    if (longitud == 0) 
        return; // La lista está vacía, no se puede eliminar.
    Nodo<T> *nodoAEliminar;

    if (longitud == 1) { // Caso 1: La lista tiene un solo elemento.
        nodoAEliminar = head;
        head = nullptr;
        tail = nullptr;
    } else { // Caso 2: La lista tiene múltiples elementos.
        Nodo<T> *actual = head;
        // El bucle se detiene cuando 'actual->getSiguiente()' es el 'tail'.
        while (actual->getSiguiente() != tail) 
            actual = actual->getSiguiente();
        
        nodoAEliminar = tail;     // El nodo a eliminar es el actual 'tail'.
        tail = actual;            // El nodo 'actual' se convierte en el nuevo 'tail'.
        tail->setSiguiente(head); // El nuevo tail debe apuntar a head para mantener la circularidad.
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
        std::cout << "\nPosiciones invalidas, imposible intercambiar\n"; 
        return;
    }

    Nodo<T> *actual = head;
    Nodo<T> *nodo1 = nullptr;
    Nodo<T> *nodo2 = nullptr;

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
T ListaCircular<T>::consultar(int pos){ //propenso a errores
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
        Nodo<T>* actual = head;
        for (int i = 1; i < pos; i++)
            actual=actual->getSiguiente();
        
        return actual->getElemento();
        

    }
    else
        return T(); //retorna valor por defecto
}
// Método para buscar un elemento y devolver su posición
template<typename T>
int ListaCircular<T>::buscar(T elemento) {
    if (longitud == 0) 
        return -1; // Lista vacía
    Nodo<T> *actual = head;
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
ListaCircular<T> ListaCircular<T>::concatenar(const ListaCircular<T> &target){
    ListaCircular<T> resultado(*this); // Inicia 'resultado' como una copia de la lista actual.
                                       // Esto maneja el caso donde la lista actual está vacía o no.
    if (target.longitud == 0) {
        return resultado; // Si 'target' está vacía, 'resultado' es solo la copia de la lista actual.
    }
    
    // Si la lista actual estaba vacía, 'resultado' es una lista vacía.
    // En ese caso, necesitamos que 'resultado' contenga los elementos de 'target'.
    // Esto ya lo maneja el bucle de inserción siguiente.

    Nodo<T> *actual_target = target.head;
    // Recorremos los elementos de 'target' e los insertamos al final de 'resultado'.
    // El bucle va de 0 a longitud-1 de target para copiar todos sus elementos.
    for (int i = 0; i < target.longitud; ++i) {
        resultado.insertarAlFinal(actual_target->getElemento());
        actual_target = actual_target->getSiguiente();
    }
    return resultado;
}
// Método para verificar si la lista está vacía
template<typename T>
bool ListaCircular<T>::esVacia() const{
    return head == nullptr; 
}

// Método para imprimir todos los elementos de la lista
template<typename T> 
void ListaCircular<T>::imprimirLista(){
    cout <<endl; 
    
    if (head == nullptr) {
        cout << "La lista esta vacia." <<endl;
        return;
    }

    Nodo<T> *actual = head;
    
    // Usamos un bucle do-while para asegurar que el 'head' se imprima
    // y para detenernos cuando volvamos a él.
    do {
        cout << actual->getElemento() << endl; 
        actual = actual->getSiguiente();     
    } while (actual != head); 
}
template<typename T>
void ListaCircular<T>::invertir(){

    if(head == nullptr || head==tail)
        return;
    
    Nodo<T>* anterior=nullptr;
    Nodo<T>* siguiente=nullptr;
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