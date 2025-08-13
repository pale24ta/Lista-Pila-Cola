#ifndef LISTA_HPP
#define LISTA_HPP



#include <iostream>
#include "nodo.hpp"
#include "cola.hpp"

using namespace std;


template <class Element>
class Lista{

	private:
		Nodo<Element> *head,*tail;
		int len;

	public:

		Lista(): head(NULL),tail(NULL),len(0) {}
		Lista(Element *array, int size);
		Lista(const Lista<Element> &target);
		~Lista();
		void copiar(const Lista<Element> &target);

		Nodo<Element>* getHead() {return head;}
		Nodo<Element>* getTail() {return tail;}
		int getLength() {return len;}

		// void setHead(Nodo<Element>* h) {head = h;}
		// void setTail(Nodo<Element>* t) {tail = t;}
		void setLength(int l) {len = l;}


		// Metodos principales


		void insertar(Element d, int pos);
		void remover(int pos);
		Element& consultar(int pos);
		void vaciar();

		bool esVacia() {return len == 0;}
		void invertir();
		Element& operator[](int index);
		void intercambiar(int pos1, int pos2);
		bool operator==(const Lista<Element> &target); // Compara dos listas
		Lista<Element> concat(const Lista<Element> &target); // concatena

		void leftShift(int shift);
		void invertirLista();

};

template<class Element>
Lista<Element>::~Lista(){
	this->vaciar();
}
template <class Element>
inline void Lista<Element>::copiar(const Lista<Element> &target)
{
	if(len != 0){
		vaciar();
	}
	if(target.len != 0){

		Nodo<Element> *ptr = target.head;
		Nodo<Element> *nuevo = new Nodo<Element>(ptr->getInfo());
		
		head = tail = nuevo;

		for(ptr = ptr->getNext(); ptr != NULL; ptr = ptr->getNext()){
			nuevo->setNext(new Nodo<Element>(ptr->getInfo()));
			tail = nuevo = nuevo->getNext();
		}

		len = target.len;
	}
	

}
// Sobrecarga del operador para imprimir >>
template<class Element>
std::ostream &operator<<(std::ostream &os, Lista<Element> list)
{

	os<<"[";

	for(Nodo<Element> *ptr = list.getHead(); ptr != NULL ; ptr = ptr->getNext())
	{
		os<<ptr->getInfo();

		if(ptr->getNext() != NULL){
			os<<",";
		}
	}
	os<<"]"<<std::endl;

	return os;
}

// Sobrecarga del operador para []

template<class Element>
Element& Lista<Element>::operator[](int index){
	return consultar(index);
}

template <class Element>
void Lista<Element>::intercambiar(int pos1, int pos2){

    if (this->length <= 1) {
        cout << "No se puede intercambiar, lista muy corta" << endl;
        return;
    }

    if(this->length > 0){
        if(pos1 >= 0 && pos1 < this->length && pos2 >= 0 && pos2 < this->length && pos1 != pos2){
            Nodo<Element> *ptrPos1, *ptrPos2, *anterior1, *anterior2;
            ptrPos1 = this->head;
            ptrPos2 = this->head;
            anterior1 = NULL;
            anterior2 = NULL;

            for (int i = 0; i < pos1; i++){
                anterior1 = ptrPos1;
                ptrPos1 = ptrPos1->getNext();
            }

            for (int i = 0; i < pos2; i++){
                anterior2 = ptrPos2;
                ptrPos2 = ptrPos2->getNext();
            }

            if (pos2 == pos1 + 1) {

                if (anterior1 != NULL) {
                    anterior1->setNext(ptrPos2);
                }else{
                    this->head = ptrPos2;
                }

                ptrPos1->setNext(ptrPos2->getNext());
                ptrPos2->setNext(ptrPos1);

            }else{ 

                if (anterior1 != NULL) {
                    anterior1->setNext(ptrPos2);
                } else {
                    this->head = ptrPos2;
                }

                if (anterior2 != NULL) {
                    anterior2->setNext(ptrPos1);
                } else {
                    this->head = ptrPos1;
                }

                Nodo<Element> *temp = ptrPos1->getNext();
                ptrPos1->setNext(ptrPos2->getNext());
                ptrPos2->setNext(temp);

            }
        }
    }
}

template <class Element>
inline bool Lista<Element>::operator==(const Lista<Element> &target)
{
    if(len == target.len){
		Nodo<Element> *p = head, *q = target.head;

		while(p != NULL && q != NULL){
			if(p->getInfo() != q->getInfo())
				return false;
		}
		return true;
	}
	return false;
}
template<class Element>
Lista<Element> Lista<Element>::concat(const Lista<Element> &target) // concatena
{
	Lista<Element> nueva(*this);

	if(target.len > 0){

		Nodo<Element> *p = target.head;

		while(p != NULL){
			nueva.tail->setNext(new Nodo<Element>(p->getInfo()));
			nueva.tail = nueva.tail->getNext();
			p = p->getNext();
		}
	}

	nueva.len += target.len;
	return nueva;
}

template <class Element>
inline Lista<Element>::Lista(Element *array, int size)
{
	Nodo<Element>* nuevo;
	for(int i= 0; i < size ; i++){
		nuevo = new Nodo<Element>(array[i]);
		if(i == 0){
			head = tail = nuevo;
		}else{
			tail->setNext(nuevo);
			tail=nuevo;
		}
	}

	len = size;
}

template <class Element>
inline Lista<Element>::Lista(const Lista<Element> &target): head(NULL),tail(NULL),len(0)
{
	if(target.len > 0){

		Nodo<Element> *ptr = target.head;
		Nodo<Element> *nuevo = new Nodo<Element>(ptr->getInfo());
		
		head = tail = nuevo;

		for(ptr = ptr->getNext(); ptr != NULL; ptr = ptr->getNext()){
			nuevo->setNext(new Nodo<Element>(ptr->getInfo()));
			tail = nuevo = nuevo->getNext();
		}

		len = target.len;
	}
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


	if(pos > len){
		pos = len;
	}
	if(pos <= 0){
		pos = 1;
	}

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
template <class Element>
inline void Lista<Element>::vaciar()
{
	if(head != NULL){

		Nodo<Element> *del = NULL;
		while(head != NULL){
			del = head;
			head = head->getNext();
			delete del;
		}

		len = 0;
	}
}

template <class Element>
inline void Lista<Element>::leftShift(int shift)
{
	
	if(head == NULL || shift == 1)
		return;
		
	tail->setNext(head);	// Una lista circular temporalmente

	Nodo<Element> *pivote1 = NULL, *pivote2 = head;

	for(int i =1 ; i < shift; i++){
		pivote1 = pivote2;
		pivote2 = pivote2->getNext();
	}

	// El pivote2 es la cabeza y el pivote1 es la cola

	tail = pivote1;
	head = pivote2;

	tail->setNext(NULL);
}

template <class Element>
inline void Lista<Element>::invertirLista()
{
	// Tranformas la lista en una circular
	tail->setNext(head);

	Nodo<Element> *aux = head;
	head = tail;
	tail = aux;

}

// template <class Element>
// inline void Lista<Element>::rightShift(int shift)
// {
// 	if(head == NULL || shift == 0)
// 		return;
	

// 	shift = shitf - len;
// 	if(shift != 0){

// 		Nodo<ELement> *act = head;

// 		for()
// 	}
// }


template<typename Element>
void Lista<Element>::invertir(){
    if(head == NULL || head == tail) 
        return ;
    Nodo<Element>* anterior= NULL, *actual = head, *siguiente=NULL;

    while (actual != NULL){
        siguiente = actual->getNext();
        actual->setNext(anterior);
        anterior=actual;
        actual=siguiente;
    }
    Nodo<Element>* aux=head;
    head=tail;
    tail=aux;

}

#endif

