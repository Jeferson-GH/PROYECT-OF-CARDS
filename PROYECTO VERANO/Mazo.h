#ifndef MAZO_H
#define MAZO_H
#include "Carta.h"

class Mazo {
private:
	Carta* carta;
public:
	Mazo();
	~Mazo();
	void inicializar();
	void barajar();
	Carta* tomarCarta();

};
#endif
