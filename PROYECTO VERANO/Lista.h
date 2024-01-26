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
	void insertar(JugadorGenerico*);
	void borrar(Nodo*);
	bool listaVacia();
	void limpiar();
};
#endif
