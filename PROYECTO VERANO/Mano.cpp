#include "Mano.h"
#include "sstream"

//Constructor y destructor
Mano::Mano() : inicio{ nullptr } {}
Mano::~Mano() { limpiar(); }

//Getters
int Mano::getCantidad() //Retorna la cantidad de nodos que hay en la lista
{
	int cant = 0;
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		cant++;
		tmp = tmp->next;
	}
	return cant;
}
Carta* Mano::getCarta(int pos) //Retorna la carta en la posicion 'pos'
{
	NodoMano* tmp = inicio;
	int cont = 0;

	while (tmp != nullptr and cont < pos) { //Sale del ciclo si la lista se acaba o si llega a la posicion
		tmp = tmp->next;
		cont++;
	}
	if (tmp != nullptr) {
		return tmp->carta; //Retorna la carta[pos]
	}
	else {
		return nullptr; //Retorna nullptr si se llega al final
	}
}
Carta* Mano::getAS() //Recorre la lista en busca de un AS
{
	if (hayAS()) {
		NodoMano* tmp = inicio;
		while (tmp != nullptr) {
			if (tmp->carta->getTipo() == 'A')
				return tmp->carta; //Si se encuentra, retorna la carta AS
			tmp = tmp->next;
		}
	}
	return nullptr; //Retorna nullptr si no se encuentra
}
int Mano::getPuntos() //Retorna la suma de los puntos de las cartas en mano
{
	int suma = 0;
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		suma += tmp->carta->getValor();
		tmp = tmp->next;
	}
	return suma;
}

bool Mano::hayAS() //Recorre la lista y confirma la existencia de un AS
{
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		if (tmp->carta->getTipo() == 'A')
			return true;
		tmp = tmp->next;
	}
	return false;
}

void Mano::agregarCarta(Carta* c) //Inserta una carta a la Mano
{
	if (inicio == nullptr) {
		inicio = new NodoMano; //Si esta vacia, se crea un Nodo
		inicio->carta = c; //Se asigna el parametro a la nueva carta
		inicio->next = nullptr;
	}
	else { //Si ya hay elementos, se inserta en la ultima posicion de la lista
		NodoMano* tmp = inicio;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = new NodoMano;
		tmp->next->carta = c;
		tmp->next->next = nullptr;
	}
}

void Mano::limpiar() //Limpia la mano actual, comparte funcionalidad con el destructor
{
	NodoMano* tmp;
	while (inicio != nullptr) {
		tmp = inicio;
		inicio = inicio->next;
		delete tmp;
	}
}

std::string Mano::mostrar() //Muestra la mano en una hilera
{
	std::stringstream s;
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		if (tmp->next != nullptr) {
			s << tmp->carta->mostrar() << " | ";
		}
		else {
			s << tmp->carta->mostrar();
		}
		tmp = tmp->next;
	}
	return s.str();
}

std::string Mano::guardarCartas() //Guarda los atributos de todas las cartas en mano
{
	int palo;
	std::stringstream s;
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		s << tmp->carta->getValor() << ' ';
		palo = tmp->carta->getPalo(); //Guarda el valor ascii del char
		s << palo << ' ';
		s << tmp->carta->getTipo() << ' ';
		s << tmp->carta->getBocaAbajo() << '\n';
		tmp = tmp->next;
	}
	return s.str();
}

