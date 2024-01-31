#ifndef JUGADORGENERICO_H
#define JUGADORGENERICO_H
#include "Mano.h"

class JugadorGenerico {
protected:
	std::string nickname;
	Mano* mano;
public:
	JugadorGenerico();
	~JugadorGenerico();
	int getPuntos();
	Mano* getMano();
	std::string getNickname();
	void pedirCarta(Mazo*) ;
	bool sePaso();
	virtual std::string mostrar() = 0;
	
	
};


#endif 