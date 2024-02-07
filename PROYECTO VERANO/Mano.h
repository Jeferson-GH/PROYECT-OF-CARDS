#ifndef MANO_H
#define MANO_H
#include "NodoMano.h"

class Mano {

public:

	Mano();
	~Mano();

	Carta* getCarta(int pos);
	Carta* getAS();
	int getPuntos();
	int getCantidad();

	void agregarCarta(Carta* c);
	bool hayAS();
	void limpiar();
	std::string mostrar();
	std::string guardarCartas();

private:

	NodoMano* inicio;

};

#endif
