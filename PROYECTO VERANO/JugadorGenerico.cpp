#include "JugadorGenerico.h"
#include <sstream>

//Constructor y destructor
JugadorGenerico::JugadorGenerico() : nickname{ "" }, mano{ new Mano } {}
JugadorGenerico::~JugadorGenerico() { delete mano; }

//Getters
std::string JugadorGenerico::getNickname() { return nickname; }
Mano* JugadorGenerico::getMano() { return mano; }
int JugadorGenerico::getPuntos() { return mano->getPuntos(); }

void JugadorGenerico::pedirCarta(Mazo* mazo) { mano->agregarCarta(mazo->tomarCarta()); } //Se toma una carta del mazo y se agrega a la mano del jugador

bool JugadorGenerico::sePaso() { return getPuntos() > 21; } //Determina si se paso de 21

void JugadorGenerico::cambiarValorAS() { mano->getAS()->setValor(11); } //Cambia el valor del AS de 1 a 11

std::string JugadorGenerico::guardarMano() { return mano->guardarCartas(); } //Guarda las cartas de la mano en una hilera








