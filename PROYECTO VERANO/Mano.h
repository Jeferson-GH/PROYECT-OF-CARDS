#ifndef MANO_H
#define MANO_H
#include "NodoMano.h"

class Mano {
private:
	NodoMano* inicio;
public:
	Mano();
	~Mano();
	Carta* getCarta(int pos);
	Carta* getAS();
	int getPuntos();
	bool hayAS();
	void agregarCarta(Carta* c);
	void limpiar();
	std::string mostrar();
	std::string guardarCartas();
	int getCantidad();
};

#endif
