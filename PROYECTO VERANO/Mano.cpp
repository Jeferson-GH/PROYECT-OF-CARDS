#include "Mano.h"
#include "sstream"

//Constructor y destructor
Mano::Mano(): inicio{ nullptr }, cant {0} {}
Mano::~Mano()
{
	limpiar(); //Se libera memoria de toda la lista
}

void Mano::agregarCarta(Carta* c) //Inserta una carta a la Mano
{
	if (inicio == nullptr) { //Si esta vacia, se crea un Nodo
		inicio = new NodoMano;
		inicio->carta = c;
		inicio->next = nullptr;
	}
	else { //Si hay un elemento, se inserta en la ultima posicion
		NodoMano* tmp = inicio;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = new NodoMano;
		tmp->next->carta = c;
		tmp->next->next = nullptr;
	}
	cant++;
}

void Mano::limpiar()
{
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		NodoMano* tmp2 = tmp->next;
		delete tmp->carta; // Libera la memoria de la carta individual
		delete tmp; // Libera la memoria del nodo actual
		tmp = tmp2;
	}
	inicio = nullptr;
	cant = 0;
}

int Mano::getPuntos()
{
	return 0;
}

std::string Mano::mostrar()
{
	std::stringstream s;
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		if (tmp->next != nullptr) {
			s << tmp->carta->mostrar() << " --> ";
		}
		else {
			s << tmp->carta->mostrar();
		}
		tmp = tmp->next;
	}
	return s.str();
}
