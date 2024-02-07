#ifndef JUGADORGENERICO_H
#define JUGADORGENERICO_H
#include "Mano.h"

class JugadorGenerico {

public:
	JugadorGenerico();
	~JugadorGenerico();

	int getPuntos();
	Mano* getMano();
	std::string getNickname();

	void pedirCarta(Mazo*);
	bool sePaso();
	void cambiarValorAS();
	std::string guardarMano();
	virtual std::string mostrar() = 0;

protected:
	std::string nickname;
	Mano* mano;

};

#endif 