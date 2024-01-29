#include "JugadorGenerico.h"
#include <sstream>

JugadorGenerico::JugadorGenerico() : nickname(""), mano(nullptr) {}
JugadorGenerico::~JugadorGenerico() { delete mano; }

std::string JugadorGenerico::getNickname() { return nickname; } //Retorna el nickname
Mano* JugadorGenerico::getMano() { return mano; } //Retorna la mano
int JugadorGenerico::getPuntos() { return mano->getPuntos(); } //Suma del valor del mazo
void JugadorGenerico::pedirCarta(Mazo* mazo) { mano->agregarCarta(mazo->tomarCarta()); } //Se toma una carta del mazo y se agrega a la mano del jugador
bool JugadorGenerico::sePaso() { return getPuntos() >= 21; } //Determina si se paso de 21

std::string JugadorGenerico::mostrarMano() //Muestra la mano
{
    std::stringstream s;
    s << "\t" << mano->mostrar();
    return s.str();
}






