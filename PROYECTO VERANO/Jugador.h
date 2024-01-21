#ifndef JUGADOR_H
#define JUGADOR_H
#include "JugadorGenerico.h"

class Jugador : public JugadorGenerico {
	Jugador();
	~Jugador();
	Carta* pedirCarta();
};

#endif
