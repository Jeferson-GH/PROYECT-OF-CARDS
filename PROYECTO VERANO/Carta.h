#ifndef CARTA_H
#define CARTA_H
#include <iostream>

struct Carta {
	int valor;
	char palo;
	char tipo;
	bool bocaAbajo;
	bool color;

	Carta();
	~Carta();
	int getValor();
	int getPalo();
	void voltear();

};

#endif
