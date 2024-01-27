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
	void pedirCarta(Mazo*);
	bool sePaso();
	std::string mostrarMano();
	std::string getNickname();
	Mano* getMano();
};


#endif 