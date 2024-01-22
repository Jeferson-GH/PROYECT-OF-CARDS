#include "JugadorGenerico.h"

JugadorGenerico::JugadorGenerico() : nickname{ "" }, mano{ nullptr } {}

JugadorGenerico::JugadorGenerico(std::string name, Mano* ptr) : nickname{ name }, mano{ptr} {}

Carta* JugadorGenerico::pedirCarta()
{
	return nullptr;
}

bool JugadorGenerico::sePaso()
{
	return false;
}



