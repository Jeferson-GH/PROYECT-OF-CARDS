#include <sstream>
#include "Lista.h"

//Constructor y destructor
Lista::Lista(): inicio{ nullptr } {}
Lista::~Lista() { limpiar(); }

//Getters
Nodo* Lista::getInicio() { return inicio; }
Nodo* Lista::getJugador(std::string n) //Busca al jugador con el nombre ingresado por parametro
{
	if (inicio != nullptr) {
		Nodo* tmp = inicio;
		while (tmp != nullptr) {
			if (tmp->dato->getNickname() == n) {
				return tmp;
			}
			tmp = tmp->next;
		}
	}
	return nullptr; //Si no se encuentra, retorna nullptr
}
Nodo* Lista::getJugador(int pos) //Busca al jugador con la posicion ingresada por parametro
{
	int cont = 0;
	Nodo* tmp = inicio;
	while (tmp != nullptr and cont < pos) { //Recorre el ciclo hasta la posicion o hasta que se termine la lista
		tmp = tmp->next;
		cont++;
	}

	if (tmp != nullptr) {
		return tmp;
	}
	else {
		return nullptr; 
	}
}
int Lista::getCantidad() //Retorna la cantidad de elementos en la lista
{
	int cont = 0;
	Nodo* tmp = inicio;
	while (tmp != nullptr) {
		cont++;
		tmp = tmp->next;
	}
	return cont;
}

void Lista::insertar(JugadorGenerico* c) //Inserta un jugador al final de la lista
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

void Lista::borrar(std::string elim) //Borra el nodo del jugador con el nombre pasado por parametro
{
	if (inicio == nullptr)
		return; //Sale del metodo si la lista esta vacia

	Nodo* eliminar = getJugador(elim); //Se asigna el nodo que se quiere eliminar
	if (eliminar == nullptr) { //Si no se encontro el jugador, sale del metodo
		return;
	}

	Nodo* tmp = inicio;
	if (eliminar->dato == inicio->dato) { //Se elimina la primera posicion
		inicio = inicio->next;
		delete tmp;
	}
	else { //Se recorre la lista, ubica el nodo a eliminar y se ajustan los 'next'
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

void Lista::limpiar() //Limpia el contenido de la lista, comparte funcionalidad con el destructor
{
	Nodo* tmp;
	while (inicio != nullptr) {
		tmp = inicio;
		inicio = inicio->next;
		delete tmp;
	}
}

std::string Lista::guardarNicknames() //Guarda todos los nicknames de la lista en una hilera
{
	std::stringstream s;
	Nodo* tmp = inicio;
	while (tmp->next != nullptr) { //Al llegar al ultimo jugador, sale del ciclo ya que el ultimo sera el Dealer
		s << tmp->dato->getNickname() << '\n';
		tmp = tmp->next;
	}
	return s.str();
}



