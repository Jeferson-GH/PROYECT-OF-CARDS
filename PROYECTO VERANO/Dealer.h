#ifndef DEALER_H
#define DEALER_H
#include "JugadorGenerico.h"

class Dealer : public JugadorGenerico {
public:
	Dealer();
	
	virtual Carta* pedirCarta();
	void volteaSegunda();
};

#endif 
