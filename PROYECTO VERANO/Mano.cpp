#include "Mano.h"
#include "sstream"

//Constructor y destructor
Mano::Mano(): inicio{ nullptr } {}
Mano::~Mano() { limpiar(); }

Carta* Mano::getCarta(int n) //Retorna la carta en la posicion n
{
	NodoMano* tmp = inicio;
	int cont = 0;
	while (tmp->next != nullptr) {
		if (cont == n) { //Recorre la lista hasta llegar a n
			return tmp->carta;
		}
		tmp = tmp->next;
		cont++;
	}
	if (cont == n) { 
		return tmp->carta;
	}
	return nullptr;
}

Carta* Mano::getAS()
{
	if (hayAS()) {
		NodoMano* tmp = inicio;
		while (tmp != nullptr) {
			if (tmp->carta->getTipo() == 'A')
				return tmp->carta;
			tmp = tmp->next;
		}
	}
	return nullptr;
}

bool Mano::hayAS()
{
	NodoMano* tmp = inicio;
	while (tmp->next != nullptr) {
		if (tmp->carta->getTipo() == 'A')
			return true;
		tmp = tmp->next;
	}
	if (tmp->carta->getTipo() == 'A')
		return true;
	return false;
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
}

void Mano::limpiar() //Limpia la mano actual
{
	NodoMano* tmp;
	while (inicio != nullptr) {
		tmp = inicio;
		inicio = inicio->next;
		delete tmp;
	}
}

int Mano::getPuntos() //Suma los puntos de las cartas en Mano
{
	int suma = 0;
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		suma += tmp->carta->getValor();
		tmp = tmp->next;
	}
	return suma;
}

std::string Mano::mostrar() //Muestra la mano
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

std::string Mano::guardarCartas()
{
	std::stringstream s;
	NodoMano* tmp = inicio;
	int palo;
	while (tmp->next != nullptr) {
		s << tmp->carta->getValor() << ' ';
		palo = tmp->carta->getPalo();
		s << palo << ' ';
		s << tmp->carta->getTipo() << ' ';
		s << tmp->carta->getBocaAbajo() << '\n';
		tmp = tmp->next;
	}
	s << tmp->carta->getValor() << ' ';
	palo = tmp->carta->getPalo();
	s << palo << ' ';
	s << tmp->carta->getTipo() << ' ';
	s << tmp->carta->getBocaAbajo() << '\n';
	return s.str();
}

int Mano::getCantidad()
{
	int cant = 0;
	NodoMano* tmp = inicio;
	while (tmp != nullptr) {
		cant++;
		tmp = tmp->next;
	}
	return cant;
}
