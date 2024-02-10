#ifndef JUEGO_H
#define JUEGO_H
#include "Lista.h"
#include "Mazo.h"
#include "Dealer.h"

class Juego {

public:

	Juego();
	~Juego();

	void jugar();
	void agregarJugador(JugadorGenerico* n);

	bool pierde();
	void pasarTurno();

	void agregarJugadores();
	void repartirCartas();
	void mostrarJuego();
	void mostrar();
	void resultados();
	void turnoDealer();
	bool partida();

	void restablecerPartida();
	void limpiarPartida();

private:

	Lista* listaJugadores;
	Mazo* baraja;
	Dealer* dealer;
	Nodo* jugadorActual;

};


#endif
