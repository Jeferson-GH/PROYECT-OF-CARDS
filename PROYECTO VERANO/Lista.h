#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"

class Lista {

public:
	Lista();
	~Lista();

	Nodo* getInicio();
	Nodo* getJugador(std::string);
	Nodo* getJugador(int);
	int getCantidad();

	void insertar(JugadorGenerico*);
	void borrar(std::string);
	void limpiar();

	std::string guardarNicknames();

private:
	Nodo* inicio;

};
#endif
