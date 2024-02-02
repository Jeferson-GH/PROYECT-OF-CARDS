#include "Lista.h"

Lista::Lista(): inicio{ nullptr } {}

Lista::~Lista() { limpiar(); }

Nodo* Lista::getInicio() { return inicio; }

Nodo* Lista::getJugador(std::string n)
{
	if (!listaVacia()) {
		Nodo* tmp = inicio;
		while (tmp != nullptr) {
			if (tmp->dato->getNickname() == n) {
				return tmp;
			}
			tmp = tmp->next;
		}
	}
	return nullptr;
}

void Lista::insertar(JugadorGenerico* c)
{
	if (inicio == nullptr) { //Si esta vacia, se crea un Nodo
		inicio = new Nodo;
		inicio->dato = c;
		inicio->next = nullptr;
	}
	else { //Si hay un elemento, se inserta en la ultima posicion
		Nodo* tmp = inicio;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = new Nodo;
		tmp->next->dato = c;
		tmp->next->next = nullptr;
	}
}

void Lista::limpiar()
{
	Nodo* tmp;
	while (inicio != nullptr) {
		tmp = inicio;
		inicio = inicio->next;
		delete tmp;
	}
}
void Lista::borrar(std::string elim)
{
	if (!listaVacia()) {
		Nodo* eliminar = getJugador(elim);
		if (eliminar != nullptr) {
			Nodo* tmp = inicio;
			if (eliminar->dato == inicio->dato) {
				inicio = inicio->next;
				delete tmp;
			}
			else {
				Nodo* anterior = nullptr;
				while (tmp != eliminar) {
					anterior = tmp;
					tmp = tmp->next;
				}
				if (anterior != nullptr) {
					anterior->next = eliminar->next;
					delete eliminar;
				}
			}
		}
	}
}

bool Lista::listaVacia() { return inicio == nullptr; }
