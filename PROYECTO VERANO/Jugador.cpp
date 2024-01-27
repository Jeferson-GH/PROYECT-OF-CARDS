#include "Jugador.h"
#include "Mazo.h"

Jugador::Jugador() : JugadorGenerico()
{
	nickname = "";
	mano = nullptr;
}
Jugador::Jugador(std::string nombre) : JugadorGenerico()
{
	nickname = nombre;
	mano = nullptr;
}

