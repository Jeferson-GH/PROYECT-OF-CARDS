#ifndef MAZO_H
#define MAZO_H
#include "Carta.h"

class Mazo {
private:
	Carta** carta;
	int cant;
public:
	Mazo();
	~Mazo();
	void inicializar();
	void barajar();
	Carta* tomarCarta();
	std::string mostrar();
	Carta** getMazo();
	int getCantidad();
	void setCantidad(int);
	std::string guardarMazo();
	void cambiarCarta(Carta*, int);
};
#endif
