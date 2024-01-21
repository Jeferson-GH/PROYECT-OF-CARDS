#ifndef CARTA_H
#define CARTA_H
#include <iostream>

class Carta {
private:
	int valor;
	int palo;
	bool bocaAbajo;
public:
	Carta();
	~Carta();
	int getValor() { return valor; }
	int getPalo() { return palo; }
	void voltear();

};

#endif
