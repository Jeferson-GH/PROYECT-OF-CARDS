#include "Carta.h"
#include <random>
#include "color.h"


Carta::Carta()
{
	valor = 0;
	palo = 0;
	color = 0;
	tipo = ' ';
	bocaAbajo = true;
}

Carta::~Carta() {}

int Carta::getValor() {	return valor; }

int Carta::getPalo() { return palo; }

void Carta::voltear()
{
	if (bocaAbajo)
		bocaAbajo = false;
}
