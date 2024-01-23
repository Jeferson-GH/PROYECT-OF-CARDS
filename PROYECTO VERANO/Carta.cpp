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

int Carta::getValor() const { return valor; }

int Carta::getPalo() const { return palo; }

bool Carta::getBocaAbajo() const { return bocaAbajo; }

void Carta::setValor(int nuevoValor) { valor = nuevoValor; }

void Carta::setPalo(int nuevoPalo) { palo = nuevoPalo; }

void Carta::setColor(bool nuevoColor) { color = nuevoColor; }

void Carta::setBocaAbajo(bool nuevoEstado) { bocaAbajo = nuevoEstado; }

void Carta::setTipo(char nuevoTipo) { tipo = nuevoTipo; }

void Carta::voltear()
{
	if (bocaAbajo)
		bocaAbajo = false;
	else
		bocaAbajo = true;
}

void Carta::mostrar() const
{
    std::cout << "[";
    if (color)
        std::cout << red << palo << white;
    else
        std::cout << palo;
    std::cout << "] | ";

    switch (tipo)
    {
    case 'A':
        std::cout << "AS " << valor << std::endl;
        break;
    case 'J':
        std::cout << "J " << valor << std::endl;
        break;
    case 'Q':
        std::cout << "Q " << valor << std::endl;
        break;
    case 'K':
        std::cout << "K " << valor << std::endl;
        break;
    }

    if (tipo == 'N')
        std::cout << valor << std::endl;
}