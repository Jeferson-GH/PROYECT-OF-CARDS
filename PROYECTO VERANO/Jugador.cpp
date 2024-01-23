#include "Jugador.h"

Jugador::Jugador(): JugadorGenerico()
{
	nickname = "";
	mano = nullptr;
}

Jugador::Jugador(std::string nombre) : JugadorGenerico()
{
	nickname = nombre;
	mano = nullptr;
}

Carta* Jugador::pedirCarta()
{
	return nullptr;
}
