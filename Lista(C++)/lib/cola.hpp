#ifndef COLA_HPP
#define COLA_HPP

#include "nodo.hpp"
#include "iostream"

template <class Element>
class Cola{

    private:
        Nodo<Element> *front,*back;
        int len;

    public:

        Cola(): front(NULL),back(NULL),len(0){}

        Nodo<Element> *getFront() {return front;}
        Nodo<Element> *getBack() {return back;}
        int getLength() {return len;}

        void setFront(Nodo<Element> *f) {front = f;}
        void setBack(Nodo<Element> *b) {back = b;}
        void setLength(int i) {len = i;}

        void encolar(Element dato);
        void desencolar();
        Element& consultarFrente();
        bool esVacia() {return len == 0;}


        friend std::ostream &operator<<(std::ostream &os,const Cola<Element> &list)
        {

            os<<"[";

			for(Nodo<Element> *ptr = list.front; ptr != NULL ; ptr = ptr->getNext())
			{
				os<<ptr->getInfo();

				if(ptr->getNext() != NULL){
					os<<",";
				}
			}
			os<<"]"<<std::endl;

			return os;
        }
};

template <class Element>
inline void Cola<Element>::encolar(Element dato)
{
    Nodo<Element> *nuevo = new Nodo<Element>(dato);

    if(front == NULL){
        front = nuevo;
        back = nuevo;
    }else{
        back->setNext(nuevo);
        back = nuevo;
    }
    len += 1;
}
template <class Element>
inline void Cola<Element>::desencolar()
{
    Nodo<Element> *del =  front;
    front = front->getNext();
    delete del;

    len -= 1;
}
template <class Element>
inline Element& Cola<Element>::consultarFrente()
{
    if(front != NULL)
        return front->getInfo();

    throw std::out_of_range("No hay ningun elemento");
}
#endif