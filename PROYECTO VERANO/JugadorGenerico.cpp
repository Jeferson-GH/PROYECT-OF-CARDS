#include "JugadorGenerico.h"
#include <sstream>

JugadorGenerico::JugadorGenerico() : nickname{ "" }, mano{ new Mano } {}
JugadorGenerico::~JugadorGenerico() { delete mano; }
std::string JugadorGenerico::getNickname() { return nickname; } //Retorna el nickname
Mano* JugadorGenerico::getMano() { return mano; } //Retorna la mano
int JugadorGenerico::getPuntos() { return mano->getPuntos(); } //Suma del valor del mazo
void JugadorGenerico::pedirCarta(Mazo* mazo) { mano->agregarCarta(mazo->tomarCarta()); } //Se toma una carta del mazo y se agrega a la mano del jugador
bool JugadorGenerico::sePaso() { return getPuntos() > 21; } //Determina si se paso de 21
void JugadorGenerico::cambiarValorAS() { mano->getAS()->setValor(11); } //Cambia el valor del AS de 1 a 11







