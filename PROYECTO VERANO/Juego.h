#ifndef JUEGO_H
#define JUEGO_H
#include "Lista.h"
#include "Mazo.h"
#include "Dealer.h"

class Juego {
private:
	Lista* listaJugadores;
	Mazo *baraja;
	Dealer* dealer;
	Nodo* jugadorActual;
public:
	Juego();
	~Juego();
	void jugar();
	void agregarJugador(JugadorGenerico* n);
	void eliminarJugador(std::string);
	bool pasarTurno();
	int jugada(char);
	void agregarJugadores();
	void mostrarJuego();
	bool pierde();
};


#endif
