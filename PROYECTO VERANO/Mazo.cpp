#include "Mazo.h"
#include <random>
#include <sstream>

Mazo::Mazo() : cant{ 52 }
{
    carta = new Carta* [52];
    for (int i = 0; i < 52; i++) {
        carta[i] = new Carta; //Se crea un array de punteros a Carta en el heap
    }
}

Mazo::~Mazo()
{
    for (int i = 0; i < cant; i++) {
        delete carta[i]; // Libera la memoria de cada Carta individual
    }
    delete[] carta; 
}

void Mazo::inicializar()
{
    // 4 palos: corazones, diamantes, tréboles, espadas
    for (int i = 0; i < 4; i++) {
        // Asigna valores del 1 al 13
        for (int j = 0; j < 13; j++) {
            carta[i * 13 + j]->setValor(j + 1);
            carta[i * 13 + j]->setPalo(i + 3);
            carta[i * 13 + j]->setTipo('N'); // Carta normal
            carta[i * 13 + j]->setBocaAbajo(false);

            // Asigna tipo de carta y ajusta valor correspondiente
            switch (carta[i * 13 + j]->getValor()) {
            case 1: carta[i * 13 + j]->setTipo('A'); break;
            case 11: carta[i * 13 + j]->setTipo('J'); carta[i * 13 + j]->setValor(10); break;
            case 12: carta[i * 13 + j]->setTipo('Q'); carta[i * 13 + j]->setValor(10); break;
            case 13: carta[i * 13 + j]->setTipo('K'); carta[i * 13 + j]->setValor(10); break;
            }
        }
    }
}

void Mazo::barajar()
{
    //Definicion de variable para numeros aleatorios
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> aleatorio(0, 51);

	for (int i = 0;i < cant;i++) { //Intercambia posiciones aleatoriamente
		int aux = aleatorio(rng);
		Carta* tmp = carta[i];
		carta[i] = carta[aux];
		carta[aux] = tmp;
	}
}

Carta* Mazo::tomarCarta() //Se extrae una carta del mazo y se resta la cantidad
{
	cant--;
	return carta[cant];
}

std::string Mazo::mostrar() //Muestra todas las cartas del mazo
{
    std::stringstream s;
	for (int i = 0;i < cant;i++) {
        s << carta[i]->mostrar() << std::endl;
	}
    return s.str();
}

Carta** Mazo::getMazo()
{
    return carta;
}

int Mazo::getCantidad()
{
    return cant;
}
void Mazo::setCantidad(int x)
{
    cant=x;
}

std::string Mazo::guardarMazo()
{
    std::stringstream s;
    int x;
    char y;
    for (int i = 0;i < cant;i++) {
        s << carta[i]->getValor() << " ";
        x = carta[i]->getPalo();
        s << x << " ";
        y = carta[i]->getTipo();
        s << y << " ";
        s << carta[i]->getBocaAbajo() << '\n';
    }
    return s.str();
}

void Mazo::cambiarCarta(Carta* c, int pos)
{
    carta[pos]->setValor(c->getValor());
    carta[pos]->setPalo(c->getPalo());
    carta[pos]->setTipo(c->getTipo());
    carta[pos]->setBocaAbajo(c->getBocaAbajo());

}
