#include "JugadorGenerico.h"

JugadorGenerico::JugadorGenerico() : mano{ nullptr } {}


bool JugadorGenerico::sePaso()
{
	return mano->getPuntos() > 21;
}



