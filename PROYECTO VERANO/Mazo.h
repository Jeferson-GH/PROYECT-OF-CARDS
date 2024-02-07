#ifndef MAZO_H
#define MAZO_H
#include "Carta.h"

class Mazo {

public:

	Mazo();
	~Mazo();

	Carta** getMazo();
	int getCantidad();

	void setCantidad(int);

	void inicializar();
	void barajar();
	Carta* tomarCarta();
	void cambiarCarta(Carta*, int);
	std::string mostrar();
	std::string guardarMazo();


private:

	Carta** carta;
	int cant;

};
#endif
