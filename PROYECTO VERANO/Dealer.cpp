#include "Dealer.h"
#include <sstream>

Dealer::Dealer(): JugadorGenerico()
{
	nickname = "Dealer";
	mano = new Mano;
}

void Dealer::volteaSegunda() //Voltea la segunda carta del Dealer
{
	mano->getCarta(1)->voltear();
}
std::string Dealer::mostrar() //Muestra la mano
{
    std::stringstream s;
    s << "\t\t" << nickname << '\n';
    s << "\t     " << mano->mostrar() << '\n' << '\n' << '\n';
    return s.str();
}