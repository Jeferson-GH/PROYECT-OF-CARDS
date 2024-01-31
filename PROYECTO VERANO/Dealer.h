#ifndef DEALER_H
#define DEALER_H
#include "JugadorGenerico.h"

class Dealer : public JugadorGenerico {
public:
	Dealer();
	void volteaSegunda();
	virtual std::string mostrar();
};

#endif 
