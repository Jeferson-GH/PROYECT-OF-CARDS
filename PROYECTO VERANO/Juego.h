#ifndef JUEGO_H
#define JUEGO_H
#include "Lista.h"
#include "Mazo.h"

class Juego {
private:
	Lista listaJugadores;
	Mazo baraja;
public:
	Juego();
	~Juego();
	void jugar();
};


#endif
