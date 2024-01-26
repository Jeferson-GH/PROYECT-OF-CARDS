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

void Jugador::pedirCarta(Mazo* m) //Se toma una carta del mazo y se agrega a la mano del jugador
{
	mano->agregarCarta(m->tomarCarta());
}
