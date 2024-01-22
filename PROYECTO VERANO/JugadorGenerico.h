#ifndef JUGADORGENERICO_H
#define JUGADORGENERICO_H
#include "Mano.h"

class JugadorGenerico {
protected:
	std::string nickname;
	Mano* mano;
public:
	JugadorGenerico();
	JugadorGenerico(std::string, Mano*);
	~JugadorGenerico();
	Carta* pedirCarta();
	bool sePaso();
};


#endif 