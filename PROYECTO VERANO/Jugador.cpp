#include "Jugador.h"

Jugador::Jugador(std::string nombre) : JugadorGenerico(nombre)
{
	mano = nullptr;
}

Jugador::~Jugador()
{
	delete mano;
}
