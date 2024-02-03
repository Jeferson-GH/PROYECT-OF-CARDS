#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"

class Lista {
private:
	Nodo* inicio;
public:
	Lista();
	~Lista();
	Nodo* getInicio();
	Nodo* getJugador(std::string);
	Nodo* getJugador(int);
	int getCantidad();
	void insertar(JugadorGenerico*);
	void borrar(std::string);
	bool listaVacia();
	void limpiar();
	std::string guardarNicknames();

};
#endif
