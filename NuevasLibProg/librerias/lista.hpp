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

        void liberarLista();
        void swap(Nodo<T>*& a, Nodo<T>*& b);
        void swapT(int& a, int& b); //para operador de asignacion
    public:
        //constructor polimorfico
        Lista();
        ///constructor copia
        Lista(const Lista<T>  &target);
        //operador de asinacion
        Lista<T>& operator=( Lista<T>& target);
        //destructor de lista 
         ~Lista();
         //metodos clasicos
        int getLongitud() const;
        const T& getElementoHead()const;
        const T& getElementoTail() const;
        //metodos principales
        void insertarEnPosicion(T elemnto, int pos);
        void eliminarPorPosicion(int pos);
        //metodos de consulta
        T& consultar(int pos); //con logica para abordar errores 
        const T& consultar(int pos) const; //con logica para abordar errores
        int buscar(T elemento); //devuelve -1 si no esta, devulve la posicion del elemento
        Lista<T> concatenar(Lista<T> &target); // toma la lista original y la concatena con la lista target y devuelve la lista concatenada
        bool esVacia() const;
        int existe(T elemento); //verifica si el elemento existe y devuelve su posicion , -1 si no existe
        void imprimirLista();
        void invertir(); 
        //funciones adicionales vistas en clases o en parciales
        void rightShift(int shift);
        void intercambiar(int pos1, int pos2); 
        static Lista<T> sortedIntersect(Lista<T> a, Lista<T> b); //funcion estatica usar operadores de ambito
        bool operator==(const Lista<T> &target) const;

};
//declaraciones de la clase lista 
template<typename T>
Lista<T>::Lista():head(NULL), tail(NULL), longitud(0){}
//implementacion constructor copia
template<typename T>
Lista<T>::Lista(const Lista<T> &target) : head(NULL), tail(NULL), longitud(0) {
    if (target.head == NULL) 
        return; // La lista original está vacía, no hay nada que copiar.

    Nodo<T> *nodoActualTarget = target.head;
    // Crea el primer nodo de la nueva lista
    this->head = new Nodo<T>(nodoActualTarget->getElemento());
    this->tail = this->head; // Por ahora, head y tail apuntan al mismo nodo
    this->longitud = 1; // Ya tenemos un nodo

    nodoActualTarget = nodoActualTarget->getSiguiente(); // Avanza al siguiente nodo en la lista original
    // Copia los nodos restantes
    while (nodoActualTarget != NULL) {
        insertarEnPosicion(nodoActualTarget->getElemento(), longitud);
        nodoActualTarget = nodoActualTarget->getSiguiente();
    }
}
//operador de asignacion
template<typename T>
Lista<T>& Lista<T>::operator=(Lista<T>& target){
    
    if(this != &target){
        Lista<T> aux(target); 
    
        swap(aux.head, head);
        swap(aux.tail, tail);
        swapT(aux.longitud,longitud);
    }
    return *this;
}
template<typename T>
int Lista<T>::getLongitud() const{
    return longitud;
}

 template<typename T>
const T& Lista<T>::getElementoHead() const{
    static const T valorPorDefecto = T();
    if(head == NULL)
        return valorPorDefecto;
    return head->getElemento();
 }
 template<typename T>
const T& Lista<T>::getElementoTail() const{
    static const T valorPorDefecto = T();
    if(tail == NULL)
        return valorPorDefecto;
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
    else {
        Nodo<T> *actual = head;
        for(int i = 0; i < pos - 1; i++) 
            actual = actual->getSiguiente();
    
        //  El nuevo nodo apunta al siguiente del nodo actual
        nuevo->setSiguiente(actual->getSiguiente());
        // El nodo actual apunta al nuevo nodo
        actual->setSiguiente(nuevo);
    }
    longitud++;
}

template<typename T>
void Lista<T>::eliminarPorPosicion(int pos) {
    if (head == NULL) 
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
        if (head == NULL) { // Si la lista queda vacía
            tail = NULL;
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
T& Lista<T>::consultar(int pos) {
    // Variable estática para retorno seguro en casos de error
    static T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;
    
    // Ajustar posición si es inválida
    if (pos <= 0) 
        return head->getElemento(); 
    if (pos >= longitud) 
        return tail->getElemento(); 
    

    Nodo<T>* actual = head;
    for (int i = 0; i < pos ; ++i) 
        actual = actual->getSiguiente();
    
    return actual->getElemento();
    
}
template<typename T>
const T& Lista<T>::consultar(int pos) const {
    // Variable estática const para retorno seguro
    static const T valorPorDefecto = T();
    
    if (esVacia()) 
        return valorPorDefecto;
    
    if (pos <= 0) 
        return head->getElemento();
    if (pos >= longitud) 
        return tail->getElemento();
    
    Nodo<T>* actual = head;
    
    for (int i = 0; i < pos; ++i) {
        actual = actual->getSiguiente();
    }

        return actual->getElemento();
}
template<typename T> 
int Lista<T>::existe(T elemento) {
    if(head == NULL)
        return -1;
    int pos=0;
    Nodo<T> *actual=head;
    while (actual != NULL){
        if(actual->getElemento()==elemento)
            return pos;
        actual = actual->getSiguiente();
        pos++;
    }
    return -1;
}
template<typename T>
int Lista<T>::buscar(T elemento){
    if(head==NULL)
        return -1; //lista vacia
    Nodo<T> *actual=head;
    int pos=0;

    while(actual!=NULL){
        if(actual->getElemento()==elemento)
            return pos; //retorna la posicion
        actual=actual->getSiguiente();
        pos++;
    }
    return -1; // return -1 sino la encuentra
}    
template<typename T>
bool Lista<T>::esVacia() const{
    return head==NULL; 
}
template<typename T>
Lista<T> Lista<T>::concatenar(Lista<T> &target){
    //crear una nueva lista resultado
    Lista<T> resultado(*this);
    //solo se necesita agregar los elementos de target
    Nodo<T> *actual= target.head;
    while(actual!=NULL){
        resultado.insertarEnPosicion(actual->getElemento(), resultado.getLongitud());
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
    if(head==NULL)
        return; //la lista ya esta vacia
    Nodo<T> *actual=head, *aux=NULL;
    while (actual!=NULL){
        aux=actual;
        actual=actual->getSiguiente();
        delete aux;
    }
    head=tail=NULL; //asignar el tail y el head a null
    longitud=0;
}
template<typename T> 
void Lista<T>::imprimirLista(){
    cout<<endl;
    if(head==NULL){
        cout<<"La lista esta vacia"<<endl;
    }
    Nodo<T> *actual  = head;
    cout<<endl;
    while (actual!=NULL){
        cout<<actual->getElemento()<<" ";
        actual=actual->getSiguiente();
    }
    
}
template<typename T>
void Lista<T>::invertir(){
    if(head == NULL || head == tail) 
        return ;
    Nodo<T>* anterior= NULL;
    Nodo<T>* actual = head;
    Nodo<T>*siguiente=NULL;

    while (actual != NULL){
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

    int realShift, movements, i;
    Nodo<T> *first, *actual;

    realShift = shift % longitud;
    movements = longitud - realShift;
    first = head;
    actual = head;
    i=0;
    while (i < movements-1){ //restar uno para ubicarse detras del nodo que sera el nuevo head
        i++;
        actual=actual->getSiguiente();
    }
    head=actual->getSiguiente();
    actual->setSiguiente(NULL); 
    tail->setSiguiente(first);
    tail=actual;     
}
template<typename T>
void Lista<T>::intercambiar(int pos1, int pos2){
    if(head == NULL)
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
    Nodo<T> *nodo1 = NULL;
    Nodo<T> *nodo2 = NULL;
    int contador = 0;

    while(actual != NULL){ // Solo necesitamos recorrer hasta encontrar ambos nodos
        if(contador == pos1)
            nodo1 = actual;
        if(contador == pos2)
            nodo2 = actual;
        // Si ya encontramos ambos nodos, podemos salir del bucle para optimizar
        if (nodo1 != NULL && nodo2 != NULL) 
            break;
        actual = actual->getSiguiente();
        contador++;
    }
    // Una vez encontrados los nodos, intercambiar sus elementos
    if (nodo1 != NULL && nodo2 != NULL) {
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
template<typename T>
void Lista<T>::swap(Nodo<T>*& a, Nodo<T>*& b){
    Nodo<T>* aux = a;
    a = b;
    b = aux;
}
template<typename T> 
void Lista<T>::swapT(int &a, int &b){
    int aux=a;
    a=b;
    b=aux;
}
template<typename T>  
bool Lista<T>::operator==(const Lista<T> &target) const{
    if(longitud == target.longitud ){
        Nodo<T> *thisActual, *targetActual;
        thisActual = head;
        targetActual = target.head;
        while (targetActual!=NULL && thisActual!=NULL){//la segunda comprobacion es opcional.. por seguridad la coloque
            if(targetActual->getElemento() != thisActual->getElemento())
                return false;
            targetActual=targetActual->getSiguiente();
            thisActual=thisActual->getSiguiente();
        }
    }else{
        return false;
    }
    return true;
}
#endif