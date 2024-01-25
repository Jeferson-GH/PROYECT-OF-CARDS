#include "Lista.h"

Lista::Lista(): inicio{nullptr} {}

Lista::~Lista() 
{
	Nodo* tmp;
	while (inicio != nullptr) {
		tmp = inicio;
		inicio = inicio->next;
		delete tmp;
	}
}

Nodo* Lista::getInicio() { return inicio; }

void Lista::insertar(Nodo* c)
{
	if (inicio == nullptr) { //Si esta vacia, se crea un Nodo
		inicio = new Nodo;
		inicio->dato = c->dato;
		inicio->next = nullptr;
	}
	else { //Si hay un elemento, se inserta en la ultima posicion
		Nodo* tmp = inicio;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = new Nodo;
		tmp->next->dato = c->dato;
		tmp->next->next = nullptr;
	}
}

void Lista::limpiar()
{
	Nodo* tmp = inicio;
	while (tmp != nullptr) {
		Nodo* tmp2 = tmp->next;
		delete tmp->dato; // Libera la memoria de la carta individual
		delete tmp; // Libera la memoria del nodo actual
		tmp = tmp2;
	}
}
void Lista::borrar(Nodo* elim)
{
	if (!listaVacia()) {
		Nodo* tmp = inicio;
		Nodo* eliminar = elim;
		if (eliminar == inicio) {
			inicio = inicio->next;
			delete eliminar;
		}
		else {
			Nodo* anterior = nullptr;
			while (tmp != eliminar) {
				anterior = tmp;
				tmp = tmp->next;
			}
			anterior->next = eliminar->next;
			delete eliminar;
		}
	}
}

bool Lista::listaVacia() { return inicio == nullptr; }
