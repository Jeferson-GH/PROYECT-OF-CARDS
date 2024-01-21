#ifndef DEALER_H
#define DEALER_H
#include "JugadorGenerico.h"

class Dealer : public JugadorGenerico {
	Dealer();
	~Dealer();
	Carta* pedirCarta();
	void volteaSegunda();
};

#endif 
