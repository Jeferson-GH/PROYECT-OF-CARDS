#ifndef MANO_H
#define MANO_H
#include "Mazo.h"

class Mano {
private:
	Carta* carta;
public:
	Mano();
	~Mano();
	void agregarCarta(Mazo*);
	void limpiar();
	int getPuntos();

};

#endif
