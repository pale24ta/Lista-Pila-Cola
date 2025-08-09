#ifndef PILAHPP
#define PILAHPP

#include<iostream>

using namespace std;


template<class Element>
class Pila{

    private:

        Nodo<Element> *top,*deep;
        int length;


    public:

        Pila(); // Pila vacia
        Pila(const Pila<Element> &target);  // Constructor copia
        void copiar(const Pila<Element> &target);

        Nodo<Element> *getTop()const;
        int getLength()const;
        void apilar(Element dato);
        void desapilar();
        Element& consultarDesapilar();
        Element& consultarTope();
        void vaciarPila();

        bool esVacia();
        ~Pila();    // Destructor de pila

        ostream& operator<<(ostream& os, const Pila<Element> &pila);
};

template<class Element>
Pila<Element>::Pila(): top(NULL),deep(NULL),length(0){}

template<class Element>
Pila<Element>::Pila(const Pila<Element> &target): top(NULL),deep(NULL),length(0){

    Nodo<Element> *nuevo = NULL, *pTarget = target.top;

    deep = top;

    while(pTarget != NULL)
    {
        nuevo = new Nodo<Element>(pTarget.getInfo());
        if(deep == NULL){
            deep = top = nuevo;
        }else{
            deep->setNext(nuevo);
            deep = nuevo;
        }
        pTarget = pTarget->getNext();
    }

    length = target.length;
}

template<class Element>
void Pila<Element>::apilar(Element dato)
{
    Nodo<Element> *nuevo = new Nodo<Element>(dato);

    nuevo->getNext(tope);
    tope = nuevo;
    length += 1;
}


#endif