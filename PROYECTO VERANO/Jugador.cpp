#include "Jugador.h"
#include "Mazo.h"
#include <sstream>

Jugador::Jugador() : JugadorGenerico()
{
	nickname = "";
	mano = new Mano;
}
Jugador::Jugador(std::string nombre) : JugadorGenerico()
{
	nickname = nombre;
	mano = new Mano;
}

std::string Jugador::mostrar()
{
	std::stringstream s;
	s << "Jugador '" << nickname << "':" << '\n';
	s << mano->mostrar() << '\n' << '\n';
	return s.str();
}

