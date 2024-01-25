#include "Carta.h"
#include <random>
#include <sstream>


Carta::Carta()
{
	valor = 0;
	palo = 0;
	tipo = ' ';
	bocaAbajo = true;
}
//Metodos simples

Carta::~Carta() {}

int Carta::getValor() const { return valor; }

char Carta::getPalo() const { return palo; }

bool Carta::getBocaAbajo() const { return bocaAbajo; }

void Carta::setValor(int nuevoValor) { valor = nuevoValor; }

void Carta::setPalo(int nuevoPalo) { palo = nuevoPalo; }

void Carta::setBocaAbajo(bool nuevoEstado) { bocaAbajo = nuevoEstado; }

void Carta::setTipo(char nuevoTipo) { tipo = nuevoTipo; }

void Carta::voltear() //Voltea la carta
{
	if (bocaAbajo)
		bocaAbajo = false;
	else
		bocaAbajo = true;
}

std::string Carta::mostrar() const
{
    std::stringstream s;
    if (bocaAbajo) //No se muestra si esta boca abajo
    {
        s << "???";
    }
    else 
    { //Muestra el color, palo, y valor de la carta
        s << "[" << palo << "] ";
        switch (tipo)
        {
        case 'A':
            s << "A ";
            break;
        case 'J':
            s << "J ";
            break;
        case 'Q':
            s << "Q ";
            break;
        case 'K':
            s << "K ";
            break;
        default:
            s << valor;
            break;
        }
    }
    return s.str();
}
