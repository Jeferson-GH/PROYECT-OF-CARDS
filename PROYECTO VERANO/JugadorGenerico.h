#ifndef JUGADORGENERICO_H
#define JUGADORGENERICO_H
#include "Mano.h"

class JugadorGenerico {
private:
	std::string nickname;
public:
	JugadorGenerico();
	~JugadorGenerico();
	Carta* pedirCarta();
	bool sePaso();
};


#endif 