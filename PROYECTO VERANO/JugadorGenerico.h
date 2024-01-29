#ifndef JUGADORGENERICO_H
#define JUGADORGENERICO_H
#include "Mano.h"

class JugadorGenerico {
protected:
	std::string nickname;
	Mano* mano;
public:
	JugadorGenerico();
	virtual ~JugadorGenerico() = 0;
	int getPuntos();
	Mano* getMano();
	virtual void pedirCarta(Mazo*) = 0;
	bool sePaso();
	std::string mostrarMano();
	std::string getNickname();
	
};


#endif 