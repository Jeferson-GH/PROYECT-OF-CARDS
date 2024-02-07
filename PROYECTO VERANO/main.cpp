#include <iostream>
#include "Juego.h"

int main() {
	
	Juego* juego = new Juego;
	juego->jugar();
	delete juego;

	return 0;
}