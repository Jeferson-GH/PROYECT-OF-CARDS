#include "Dealer.h"

Dealer::Dealer(): JugadorGenerico()
{
	nickname = "Dealer";
	mano = nullptr;
}

void Dealer::pedirCarta(Mazo* m) //Se toma una carta del mazo y se agrega a la mano del Dealer
{
	mano->agregarCarta(m->tomarCarta());
}

void Dealer::volteaSegunda() //Voltea la segunda carta del Dealer
{
	mano->getCarta(1)->voltear();
}
