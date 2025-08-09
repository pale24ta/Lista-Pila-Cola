#ifndef LISTA_HPP
#define LISTA_HPP



#include <iostream>
#include "nodo.hpp"
#include "cola.hpp"


template <class Element>
class Lista{

	private:
		Nodo<Element> *head,*tail;
		int len;

	public:

		Lista(): head(NULL),tail(NULL),len(0) {}
		Lista(Element *array, int size);
		~Lista() {}

		Nodo<Element>* getHead() {return head;}
		Nodo<Element>* getTail() {return tail;}
		int getLength() {return len;}

		void setHead(Nodo<Element>* h) {head = h;}
		void setTail(Nodo<Element>* t) {tail = t;}
		void setLength(int l) {len = l;}


		// Metodos principales


		void insertar(Element d, int pos);
		void remover(int pos);
		Element& consultar(int pos);
		void vaciar();

		bool esVacia() {return len == 0;}


		// Operador para imprimir lista en pantalla

		Element& operator[](int index){
			return consultar(index);
		}
		
        friend std::ostream &operator<<(std::ostream &os, Lista<Element> list)
        {

            os<<"[";

			for(Nodo<Element> *ptr = list.head; ptr != NULL ; ptr = ptr->getNext())
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
inline Lista<Element>::Lista(Element *array, int size)
{
	Nodo<Element>* nuevo;
	for(int i= 0; i < size ; i++){
		nuevo = new Nodo<Element>(array[i]);
		if(i == 0){
			head = nuevo;
			tail = nuevo;
		}else{
			tail->setNext(nuevo);
			tail=nuevo;
		}
	}

	len = size;
}

template <class Element>
void Lista<Element>::insertar(Element d, int pos)
{

    Nodo<Element> *nuevo = new Nodo<Element>(d);

	if(pos <= len+1)
	{

		// O(1)

		if(pos == len+1 || pos == 1)
		{

			if(tail == NULL || head == NULL){
				head = nuevo;
				tail = nuevo;
			}else{
				if(pos == 1){
					nuevo->setNext(head);
					head = nuevo;
				}else{
					tail->setNext(nuevo);
					tail = nuevo;
				}
			}
		}else{


			// O(n)
			Nodo<Element> *ant = head, *act = head->getNext();

			for(int i=2; i < pos && act->getNext() != NULL; i++){
				ant = act;
				act = act->getNext();
			}

			ant->setNext(nuevo);
			nuevo->setNext(act);
		}

		len += 1;
	}
}

template<class Element>
void Lista<Element>::remover(int pos){


	if(pos <= len && !esVacia())
	{	
		Nodo<Element> *del;


		if(pos == 1){
			del = head;
			head = head->getNext();
		}else{

			Nodo<Element> *ant = head, *act = head->getNext();
			

			for(int i=2; i < pos && act != NULL; i++){
				ant = act;
				act = act->getNext();
			}

			del = act;

			ant->setNext(act->getNext());

			if(pos == len){
				tail = ant;
			}
		}

		delete del;
		len -= 1;
	}	
}

template<class Element>
Element& Lista<Element>::consultar(int pos){

	if(pos > 0 && pos <= len){

		if(pos == 1){
			return head->getInfo();
		}else if(pos == len){
			return tail->getInfo();
		}else{

			Nodo<Element> *act = head->getNext();

			for(int i = 2; i < pos && act->getNext() != NULL; i++)
			{
				act = act->getNext();
			}

			return act->getInfo();
		}
	}

	// En caso de no cumplir con la condicion y no devolver nada, se lanza una excepcion
	throw std::out_of_range("Fuera de rango");

}
template <class Element>
inline void Lista<Element>::vaciar()
{
	if(head != NULL){
		while(head != NULL){
			remover(1);
		}
	}
}

#endif

