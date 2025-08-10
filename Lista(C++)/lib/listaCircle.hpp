#ifndef LISTACIR_HPP
#define LISTACIR_HPP


#include "nodo.hpp"
#include<iostream>

using namespace std;


template <class Element>
class ListaCircular{

    private:
        Nodo<Element> *head,*tail;
        int len;

    public:

        ListaCircular();
        ListaCircular(const ListaCircular<Element> &target);
        void copiar(const ListaCircular<Element> &target);
        int getLength();

        void insertar(Element e, int pos);
        void remover(int pos);
        Element& consultar(int pos);
        void vaciar();
        bool esVacia() {return len == 0;}


		Element& operator[](int index){
			return consultar(index);
		}
		
        friend std::ostream &operator<<(std::ostream &os,const Lista<Element> &list)
        {

            os<<"[";

            Nodo<Element> *ptr = list.head;

			for(int i = 1; i <= list.len ; i++)
			{
				os<<ptr->getInfo();

				if(i + 1 < list.len){
					os<<",";
				}
                ptr = ptr->getNext();
			}
			os<<"]"<<std::endl;

			return os;
        }
};

template<class Element>
ListaCircular<Element>::ListaCircular(): head(NULL),tail(NULL),len(0){
}

template <class Element>
inline ListaCircular<Element>::ListaCircular(const ListaCircular<Element> &target): head(NULL),tail(NULL),len(0)
{
    if(target.len > 0){

        Nodo<Element> *p = target.head;

        Nodo<Element> *nuevo = new Nodo<Element>(p->getInfo());
        head = tail = nuevo;
        p = p->getNext();
        
        for(; p != target.head ; p = p->getNext()){
            nuevo->setNext(new Nodo<Element>(p->getInfo()));
            tail = nuevo = nuevo->getNext();
        }

        tail->setNext(head);    // Circular
        len = target.len;
    }
}

template<class Element>
int ListaCircular<Element>::getLength(){
    return len;
}

template<class Element>
void ListaCircular<Element>::insertar(Element e, int pos){

    if(pos >= 0 && pos <= len+1){

        Nodo<Element> *nuevo = new Nodo<Element>(e);

        if(pos == 1 || pos == len+1){

            if(head == NULL || tail ==NULL){

                head = tail = nuevo;
            }else{
                if(pos == 1){
                    nuevo->setNext(head);
                    head = nuevo;
                }else if(pos == len+1){
                    tail->setNext(nuevo);
                    tail = nuevo;
                }
            }
        }else{

            Nodo<Element> *ant = NULL, *act = head;

            for(int i=1; i < pos; i++){
                ant = act;
                act = act->getNext();
            }

            ant->setNext(nuevo);
            nuevo->setNext(act);
        }

        tail->setNext(head);    // Circular
        len += 1;
    }
}
template<class Element>
void ListaCircular<Element>::remover(int pos){
    if(len >0){
        Nodo<Element> *del = NULL;

        if(pos == 1){
            del = head;
        }else{
            Nodo<Element> *ant = head, *act = head->getNext();
            
            for(int i=2; i < pos; i++){
                ant = act;
                act = act->getNext();
            }

            del = act;

            if(pos == len){
                tail = ant;
            }else{
                ant->setNext(act->getNext());
            }
        }
        delete del;
        tail->setNext(head);
        len -= 1;
    }
}
template<class Element>
Element& ListaCircular<Element>::consultar(int pos){
    if(pos >= 1 && pos <= len && len > 0){

        if(pos == 1){
            return head->getInfo();
        }else if(pos == len){
            return tail->getInfo();
        }else{

            Nodo<Element> *p = head;

            for(int i = 1; i < pos; i++){
                p = p->getNext();
            }

            return p->getInfo();
        }

    }

    throw out_of_range("Fuera de rango");
}
#endif