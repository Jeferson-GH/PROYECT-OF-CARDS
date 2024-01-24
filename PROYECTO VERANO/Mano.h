#ifndef MANO_H
#define MANO_H
#include "NodoMano.h"

class Mano {
private:
	NodoMano* inicio;
	int cant;
public:
	Mano();
	~Mano();
	void agregarCarta(Carta* c);
	void limpiar();
	int getPuntos();
	std::string mostrar();

};

#endif
