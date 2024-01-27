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
	void insertar(JugadorGenerico*);
	void borrar(std::string);
	bool listaVacia();
	void limpiar();

};
#endif
