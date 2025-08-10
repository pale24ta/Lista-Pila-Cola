#ifndef LISTACRLHPP
#define LISTACRLHPP


#include"lista.hpp"
#include "nodo.hpp"
// template <class Element>
// namespace Lista<Element>;

template<class Element>
class ListaCircular: public Lista<Element>{


    public:
        ListaCircular();
        ListaCircular(const ListaCircular<Element> &target);
        void insertar(Element dato, int pos);
        void remover(int pos);
        Element& consultar(int pos);
        void vaciar();
};


template<class Element>
ListaCircular<Element>::ListaCircular():Lista<Element>()
{}

template<class Element>
ListaCircular<Element>::ListaCircular(const ListaCircular<Element> &target): Lista<Element>()
{
    if(target.head != NULL){

        Nodo<Element> *ptr = target.getHead();
        Nodo<Element> *nuevo = new Nodo<Element>(ptr->getInfo());

        Lista<Element>::head = nuevo;
        Lista<Element>::tail = nuevo;

        // Copiamos todos los nodos de la lista por referencia circular

        for(ptr = ptr->getNext() ; ptr != target.getHead() ; ptr = ptr->getNext())
        {
            nuevo->setNext(new Nodo<Element>(ptr->getInfo()));
            nuevo = nuevo->getNext();
            Lista<Element>::tail = nuevo;
        }

        // Una ves hecho eso, la cola apuntara a la cabeza

        Lista<Element>::getTail()->setNext(Lista<Element>::getHead());
        Lista<Element>::setLength(target.getLength());
    }
}
template<class Element>
std::ostream &operator<<(std::ostream &os, ListaCircular<Element> &list)
{

	os<<"[";

    if(!list.esVacia()){

        os<<list.getHead()->getInfo()<<",";

        for(Nodo<Element> *ptr = list.getHead()->getNext(); ptr != list.getHead() ; ptr = ptr->getNext())
        {
            os<<ptr->getInfo();

            if(ptr->getNext() != list.getHead()){
                os<<",";
            }
        }                                                               
	os<<"]"<<std::endl;
    }
	return os;
}

template<class Element>
void ListaCircular<Element>::insertar(Element dato, int pos)
{

    if(pos > 0 && pos <= Lista<Element>::getLength()){

        Nodo<Element> *nuevo = new Nodo<Element>(dato);
        if(pos == 1 || pos == Lista<Element>::getLength() + 1){



            if(Lista<Element>::getHead() == NULL){

                Lista<Element>::setHead(nuevo);
                Lista<Element>::setTail(nuevo);
            }else{
                if(pos == 1){
                    nuevo->setNext(Lista<Element>::getHead());
                    Lista<Element>::setHead(nuevo);
                }else if(pos == Lista<Element>::getLength() +1){
                    Lista<Element>::getTail()->setNext(nuevo);
                    Lista<Element>::setTail(nuevo);
                }
            }
        }else{

            Nodo<Element> *ant = Lista<Element>::getHead(), *act = Lista<Element>::getHead()->getNext();


            for(int i=2; i < pos && act != Lista<Element>::getHead(); i++){
                ant = act;
                act = act->getNext();
            }

            ant->setNext(nuevo);
            nuevo->setNext(act);

        }

        // En caso de no ser anteriormente circular
        Lista<Element>::getTail()->setNext(Lista<Element>::getHead());
        Lista<Element>::setLength(Lista<Element>getLength() + 1);

    }
}

template<class Element>
void ListaCircular<Element>::remover(int pos)
{
    if(Lista<Element>::getHead() != NULL){

        Nodo<Element> *del = NULL;

        if(pos == 1){
            del = Lista<Element>::getHead();
            Lista<Element>::setHead(getHead()->getNext());
        }else{
            Nodo<Element> *ant = Lista<Element>::getHead();

            Nodo<Element> *act = ant->getNext();

            for(int i= 2; i < pos && act != Lista<Element>::getHead() ; i++){
                ant = act;
                act = act->getNext();
            }

            del = act;
            if(pos == Lista<Element>::getLength()){
                Lista<Element>::setTail(ant);
            }else{
                ant->setNext(act->getNext());
            }
        }
        delete del;

        if(Lista<Element>::getTail()->getNext() != Lista<Element>::getHead())
            Lista<Element>getTail()->setNext(Lista<Element>::getHead());

        Lista<Element>::setLength(Lista<Element>::getLength()-1);
    }
}

template<class Element>
Element& ListaCircular<Element>::consultar(int pos)
{
    if(pos > 0 && pos <= Lista<Element>::getLength()){

        if(pos == 1){
            return Lista<Element>::getHead()->getInfo();
        }else if(pos == Lista<Element>::getLength()){
            return Lista<Element>::getTail()->getInfo();
        }else{

            Nodo<Element> *ptr = Lista<Element>::getHead()->getNext();

            for(int i = 2; i < pos && ptr != Lista<Element>::getTail() ; i++){
                ptr = ptr->getNext();
            }

            
        }
    }
}

template<class Element>
void ListaCircular<Element>::vaciar()
{}

#endif