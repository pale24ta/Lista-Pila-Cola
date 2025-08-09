#ifndef NODO_HPP
#define NODO_HPP


template<class Element>
class Nodo{

	private:

		Element info;
		Nodo<Element> *next,*back;

	public:

		Nodo(Element info, Nodo<Element>* next, Nodo<Element>*back): info(info), next(next),back(back){}
		// ~Nodo() { }
		Nodo(Element info): info(info), next(NULL),back(NULL) {}
		Element& getInfo() {return info;}
		Nodo<Element>* getNext() {return next;}
		Nodo<Element>* geBack() {return back;}
		void setInfo(Element dato) {info = dato;}
		void setNext(Nodo<Element> *n) {next = n;}
		void setBack(Nodo<Element> *b){back = b;}
};


#endif
