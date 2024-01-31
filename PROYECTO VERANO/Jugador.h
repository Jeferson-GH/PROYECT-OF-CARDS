#ifndef JUGADOR_H
#define JUGADOR_H
#include "JugadorGenerico.h"

class Jugador : public JugadorGenerico {
public: 
	Jugador();
	Jugador(std::string);
	virtual std::string mostrar();
};

#endif
