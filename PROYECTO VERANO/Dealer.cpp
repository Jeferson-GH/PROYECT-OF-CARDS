#include "Dealer.h"

Dealer::Dealer(): JugadorGenerico()
{
	nickname = "Dealer";
	mano = nullptr;
}
Dealer::~Dealer() {}

void Dealer::volteaSegunda() //Voltea la segunda carta del Dealer
{
	mano->getCarta(1)->voltear();
}
