#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <fstream>
#include "Juego.h"

class Archivo {
private:
	std::string nombreArchivo;
public:
	Archivo(std::string);
	~Archivo();
	void guardarPartida(Lista*, Mazo*, Nodo*);
	bool cargarPartida(std::string, Lista*&, Mazo*&, Dealer*&, Nodo*&);

};
#endif
