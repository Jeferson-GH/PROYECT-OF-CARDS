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
	void setJugadorActual(std::string);
	void agregarJugador(JugadorGenerico* n);
	void eliminarJugador(std::string);
	void pasarTurno();
	void agregarJugadores();
	void repartirCartas();
	std::string mostrarJuego();
	bool pierde();
	void resultados();
	void turnoDealer();
	bool partida();
	void restablecerPartida();
	void limpiarPartida();
};


#endif
