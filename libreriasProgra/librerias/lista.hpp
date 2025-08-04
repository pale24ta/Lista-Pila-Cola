#ifndef LISTAHPP
#define LISTAHPP
#include<iostream>
#include "nodo.hpp" 

using namespace std;

template<typename T>
class Lista{
    private:
        Nodo<T> *head, *tail;
        int longitud;
    public:
        //constructor polimorfico
        Lista();
        ///constructor copia
        Lista(const Lista<T>  &target);
        //operador de asinacion
        Lista<T>& operator=(const Lista<T>& target);
        //destructor de lista 
         ~Lista();
         //metodos clasicos
        Nodo<T> *getHead(); 
        Nodo<T> *getTail(); 
        int getLongitud() const;
        T getElementoHead()const;
        T getElementoTail() const;
        void setHead(Nodo<T> *nuevaHead); 
        void setTail(Nodo<T> *nuevaTail); 
        //setLongitud no permitido modifica el tamaño de la lista
        void insertarEnPosicion(T elemnto, int pos);
        void insertarAlFinal(T elemento);
        void eliminarPorPosicion(int pos);
        void eliminarAlFinal();

        T consultar(int pos); //con logica para abordar errores 
        int buscar(T elemento); //devuelve -1 si no esta, devulve la posicion del elemento
        Lista<T> concatenar(Lista<T> &target); // toma la lista original y la concatena con la lista target y devuelve la lista concatenada
        bool esVacia() const;
        void liberarLista();
        void imprimirLista();
        void invertir(); // invierte el orden de la lista
        //funciones adicionales vistas en clases o en parciales
        void rightShift(int shift);
        void intercambiar(int pos1, int pos2); 
        static Lista<T> sortedIntersect(Lista<T> a, Lista<T> b); //funcion estatica usar operadores de ambito

};
//declaraciones de la clase lista 
template<typename T>
Lista<T>::Lista():head(nullptr), tail(nullptr), longitud(0){}
//implementacion constructor copia
template<typename T>
Lista<T>::Lista(const Lista<T> &target) : head(nullptr), tail(nullptr), longitud(0) {
    if (target.head == nullptr) 
        return; // La lista original está vacía, no hay nada que copiar.

    Nodo<T> *nodoActualTarget = target.head;
    // Crea el primer nodo de la nueva lista
    this->head = new Nodo<T>(nodoActualTarget->getElemento());
    this->tail = this->head; // Por ahora, head y tail apuntan al mismo nodo
    this->longitud = 1; // Ya tenemos un nodo

    nodoActualTarget = nodoActualTarget->getSiguiente(); // Avanza al siguiente nodo en la lista original
    // Copia los nodos restantes
    while (nodoActualTarget != nullptr) {
        insertarAlFinal(nodoActualTarget->getElemento()); // Reutiliza insertarAlFinal
        nodoActualTarget = nodoActualTarget->getSiguiente();
    }
}
//operador de asignacion
template<typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& target){
    //hacer una copia temporal
    Lista<T> aux(target); //usa el constructor de copia 
    //2. intercambiar los contenidos 
    swap(aux.head, head);
    swap(aux.tail, tail);
    swap(aux.longitud, longitud);
    //3. aux se destruye automaticamente, liberando la  memoria vieja
    return *this;
}
template<typename T>
Nodo<T>* Lista<T>::getHead(){ 
    return head;
}
template<typename T>
Nodo<T>* Lista<T>::getTail(){
    return tail;
}
template<typename T>
int Lista<T>::getLongitud() const{
    return longitud;
}
template<typename T>
void Lista<T>::setHead(Nodo<T> *nuevaHead){
    head=nuevaHead;
}
template<typename T>
void Lista<T>::setTail(Nodo<T> *nuevaTail){
    tail=nuevaTail;
 }
 template<typename T>
 T Lista<T>::getElementoHead() const{
    return head->getElemento();
 }
 template<typename T>
 T Lista<T>::getElementoTail() const{
    return tail->getElemento();
 }
 //implementacion metodos principales
template<typename T>
void Lista<T>::insertarEnPosicion(T elemento, int pos){
    // Ajustar la posición si es inválida (fuera de rango)
    // Si pos es mayor que la longitud actual, se ajusta para insertar al final.
    if(pos > longitud) {
        pos = longitud;
    }
    // Si pos es menor que 0, se ajusta para insertar al inicio.
    if(pos < 0) {
        pos = 0;
    }
    Nodo<T> *nuevo = new Nodo<T>(elemento);
    // Caso 1: Insertar en la posición 0 (al inicio de la lista)
    if(pos == 0){
        nuevo->setSiguiente(head); // El nuevo nodo apunta a el antiguo head
        head = nuevo;              // El nuevo nodo se convierte en el nuevo head
        if(longitud == 0) // Si la lista estaba vacía, el tail también debe ser este nuevo nodo
            tail = nuevo;
    } 
    else if (pos == longitud) { 
        tail->setSiguiente(nuevo); // El último nodo actual (apuntado por tail) enlaza al nuevo nodo
        tail = nuevo;              // El tail se actualiza para apuntar al nuevo nodo, que ahora es el último
    }
    // Caso 3: Insertar en una posición intermedia
    else {
        Nodo<T> *actual = head;
        for(int i = 0; i < pos - 1; i++) {
            actual = actual->getSiguiente();
        }
        // 1. El nuevo nodo apunta al siguiente del nodo actual
        nuevo->setSiguiente(actual->getSiguiente());
        // 2. El nodo actual apunta al nuevo nodo
        actual->setSiguiente(nuevo);
    }
    longitud++;
}
template<typename T>
    void Lista<T>::insertarAlFinal(T elemento){
        Nodo<T> *nuevo = new Nodo<T>(elemento);
        if(longitud==0){
            head=tail=nuevo;
            longitud++;
        }else{
            tail->setSiguiente(nuevo);
            tail=nuevo;
            longitud++;
        }

}
template<typename T>
void Lista<T>::eliminarPorPosicion(int pos) {
    if (head == nullptr) 
        return; // La lista está vacía, no hay nada que eliminar.

    // Ajustar la posición para que esté dentro del rango válido [0, longitud - 1]
    if (pos < 0) {
        pos = 0;
    } else if (pos >= longitud) {
        pos = longitud - 1; // Si pos es igual o mayor que longitud, elimina el último elemento
    }

    Nodo<T> *nodoAEliminar;

    if (pos == 0) {
        nodoAEliminar = head;
        head = head->getSiguiente();
        if (head == nullptr) { // Si la lista queda vacía
            tail = nullptr;
        }
    } else {
        Nodo<T> *actual = head;
        for (int i = 0; i < pos - 1; i++) {
            actual = actual->getSiguiente();
        }
        nodoAEliminar = actual->getSiguiente();
        actual->setSiguiente(nodoAEliminar->getSiguiente());

        if (nodoAEliminar == tail) { // Si se elimina el último nodo
            tail = actual; // El nuevo tail es el nodo anterior al eliminado
        }
    }
    delete nodoAEliminar;
    longitud--;
}
template<typename T>
void Lista<T>::eliminarAlFinal() {
    if (head == nullptr)  // La lista está vacía
        return;
    Nodo<T> *nodoAEliminar;

    if (longitud == 1) { // Caso: un solo elemento
        nodoAEliminar = head;
        head = nullptr;
        tail = nullptr;
    } else {
        Nodo<T> *actual = head;
        while (actual != nullptr && actual->getSiguiente() != tail) { // Asegura que actual no sea nullptr
            actual = actual->getSiguiente();
        }
        // En este punto, 'actual' es el nodo anterior al 'tail'
        nodoAEliminar = tail;
        tail = actual;
        if (tail != nullptr) { 
            tail->setSiguiente(nullptr);
        }
    }
    delete nodoAEliminar;
    longitud--;
}
template<typename T>
T Lista<T>::consultar(int pos){ //propenso a errores
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
template<typename T>
int Lista<T>::buscar(T elemento){
    if(head==nullptr)
        return -1; //lista vacia
    Nodo<T> *actual=head;
    int pos=0;

    while(actual!=nullptr){
        if(actual->getElemento()==elemento)
            return pos; //retorna la posicion
        actual=actual->getSiguiente();
        pos++;
    }
    return -1; // return -1 sino la encuentra
}    
template<typename T>
bool Lista<T>::esVacia() const{
    return head==nullptr; 
}
template<typename T>
Lista<T> Lista<T>::concatenar(Lista<T> &target){
    //crear una nueva lista resultado
    Lista<T> resultado(*this);
    //solo se necesita agregar los elementos de target
    Nodo<T> *actual= target.head;
    while(actual!=nullptr){
        resultado.insertarAlFinal(actual->getElemento());
        actual= actual->getSiguiente();
    }
    return resultado;
}
template<typename T> 
Lista<T>::~Lista(){
    liberarLista();  
}
template<typename T>
void Lista<T>::liberarLista(){
    if(head==nullptr)
        return; //la lista ya esta vacia
    Nodo<T> *actual=head, *aux=nullptr;
    while (actual!=nullptr){
        aux=actual;
        actual=actual->getSiguiente();
        delete aux;
    }
    head=tail=nullptr; //asignar el tail y el head a null
    longitud=0;
}
template<typename T> 
void Lista<T>::imprimirLista(){
    cout<<endl;
    if(head==nullptr){
        cout<<"La lista esta vacia"<<endl;
    }else{
        Nodo<T> *actual  = head;
        cout<<"[";
        while (actual!=nullptr){
            cout<<actual->getElemento()<<endl;
            if(actual->getSiguiente() != nullptr){
                cout<<",";
            }
            actual=actual->getSiguiente();
        }

        cout<<"]"<<endl;
    }
    
}
template<typename T>
void Lista<T>::invertir(){
    if(head == nullptr || head == tail) 
        return ;
    Nodo<T>* anterior= nullptr;
    Nodo<T>* actual = head;
    Nodo<T>*siguiente=nullptr;

    while (actual != nullptr){
        siguiente = actual->getSiguiente();
        actual->setSiguiente(anterior);
        anterior=actual;
        actual=siguiente;
    }
    Nodo<T>* aux=head;
    head=tail;
    tail=aux;

}
//funciones echas en clase
template<typename T>
void Lista<T>::rightShift(int shift){
    Nodo<T> *actual=nullptr , *nuevoHead=nullptr;
    int i;

    if(head==nullptr || head->getSiguiente()==nullptr || shift==0)
        return; //lista vacia o shift 0
    actual=head;
    //hacer la lista circular temporalment
    tail->getSiguiente()=head;
    shift = shift % longitud;

    for (i= 0; i < longitud - shift; i++)
        actual=actual->getSiguiente();
    nuevoHead=actual->getSiguiente();
    head=nuevoHead;
    tail=actual;
    tail->setSiguiente(nullptr);
        
}
template<typename T>
void Lista<T>::intercambiar(int pos1, int pos2){
    if(head == nullptr)
        return; // lista vacia
    if(longitud == 1)
        return; // lista con un solo elemento imposible de hacer swap
    if(pos1 == pos2)
        return; // posiciones iguales
    if(pos1 < 0 || pos2 < 0 || pos1 >= longitud || pos2 >= longitud){
        cout << "\nPosiciones invalidas, imposible intercambiar\n";
        return;
    }

    Nodo<T> *actual = head;
    Nodo<T> *nodo1 = nullptr;
    Nodo<T> *nodo2 = nullptr;
    int contador = 0;

    while(actual != nullptr){ // Solo necesitamos recorrer hasta encontrar ambos nodos
        if(contador == pos1)
            nodo1 = actual;
        if(contador == pos2)
            nodo2 = actual;
        // Si ya encontramos ambos nodos, podemos salir del bucle para optimizar
        if (nodo1 != nullptr && nodo2 != nullptr) 
            break;
        actual = actual->getSiguiente();
        contador++;
    }
    // Una vez encontrados los nodos, intercambiar sus elementos
    if (nodo1 != nullptr && nodo2 != nullptr) {
        T aux = nodo1->getElemento();
        nodo1->setElemento(nodo2->getElemento());
        nodo2->setElemento(aux);
    }
}
template<typename T>
Lista<T> Lista<T>::sortedIntersect(Lista<T> a, Lista<T> b){
    Lista<T> resultado;
    while (!a.esVacia() && !b.esVacia()){
        if(a.consultar(0) == b.consultar(0)){
            resultado.insertarAlFinal(a.consultar(0));
            a.eliminarPorPosicion(0);
            b.eliminarPorPosicion(0);
        }else{
            if(a.consultar(0) > b.consultar(0))
                b.eliminarPorPosicion(0);
            else
                a.eliminarPorPosicion(0);
        }
    }
    return resultado;
}

#endif