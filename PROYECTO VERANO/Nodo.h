#ifndef NODO_H
#define NODO_H
#include "JugadorGenerico.h"


struct Nodo {
	Nodo* next;
	JugadorGenerico* dato;
};

#endif
