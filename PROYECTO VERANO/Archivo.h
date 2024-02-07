#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <fstream>
#include "Juego.h"

class Archivo {

public:
	Archivo(std::string);
	~Archivo();
	void guardarPartida(Lista*, Mazo*, Nodo*);
	bool cargarPartida(std::string, Lista*&, Mazo*&, Dealer*&, Nodo*&);

private:
	std::string nombreArchivo;

};
#endif
