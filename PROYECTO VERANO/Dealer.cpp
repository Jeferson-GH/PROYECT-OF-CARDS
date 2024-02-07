#include "Dealer.h"
#include <sstream>

//Constructor
Dealer::Dealer() : JugadorGenerico() { nickname = "Dealer"; }

void Dealer::volteaSegunda() { mano->getCarta(1)->voltear(); } //Voltea la segunda carta del Dealer

std::string Dealer::mostrar() //Muestra la informacion del dealer en una hilera
{ //El metodo mostrar del Dealer es diferente al de jugador ya que, al mostrarse en pantalla, este va a tener un espaciado distintivo
    std::stringstream s;
    s << "\t\t" << nickname << '\n';
    s << "\t     " << mano->mostrar() << '\n' << '\n' << '\n';
    return s.str();
}
