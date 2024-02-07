#include "Jugador.h"
#include "Mazo.h"
#include <sstream>

//Constructores
Jugador::Jugador() : JugadorGenerico() {}
Jugador::Jugador(std::string nombre) : JugadorGenerico() { nickname = nombre; }

std::string Jugador::mostrar() //Muestra la informacion del jugador en una hilera
{
	std::stringstream s;
	s << "Jugador '" << nickname << "':" << '\n';
	s << mano->mostrar() << '\n' << '\n';
	s << "Puntos: " << getPuntos() << '\n' << '\n';
	return s.str();
}

