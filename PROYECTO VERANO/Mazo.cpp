#include "Mazo.h"
#include <random>
#include <sstream>

//Constructor y destructor
Mazo::Mazo() : cant{ 52 } //Se inicializa siempre con 52 cartas en total
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
    delete[] carta; //Elimina el array 
}

//Getters
Carta** Mazo::getMazo() { return carta; }
int Mazo::getCantidad(){ return cant; }

//Setters
void Mazo::setCantidad(int x) { cant = x; }

Carta* Mazo::tomarCarta() { return carta[--cant]; } //Se resta la cantidad y se extrae una carta del mazo

void Mazo::inicializar() //Asigna los atributos correspondientes a cada carta
{
    for (int i = 0; i < 4; i++) { // 4 palos: corazones, diamantes, tréboles, espadas
        for (int j = 0; j < 13; j++) { // Asigna valores del 1 al 13
            carta[i * 13 + j]->setValor(j + 1);
            carta[i * 13 + j]->setPalo(i + 3); //Se asigna un valor int a un char para utilizar su valor ASCII 
            carta[i * 13 + j]->setTipo('N'); // Tipo 'N' representa una carta normal
            carta[i * 13 + j]->setBocaAbajo(false); //Se crean todas boca arriba

            // Asigna el tipo de carta y ajusta valor correspondiente
            switch (carta[i * 13 + j]->getValor()) {
            case 1: carta[i * 13 + j]->setTipo('A'); break; //Si es un AS, se cambia el tipo
            case 11: carta[i * 13 + j]->setTipo('J'); carta[i * 13 + j]->setValor(10); break; //Si son cartas especiales
            case 12: carta[i * 13 + j]->setTipo('Q'); carta[i * 13 + j]->setValor(10); break; //se ajusta el valor a 10 y
            case 13: carta[i * 13 + j]->setTipo('K'); carta[i * 13 + j]->setValor(10); break; //se cambia el tipo
            }
        }
    }
}

void Mazo::barajar()
{
	std::random_device dev; //Definicion de variable para numeros aleatorios
	std::mt19937 rng(dev()); 
	std::uniform_int_distribution<std::mt19937::result_type> aleatorio(0, 51);

	for (int i = 0;i < cant;i++) { //Intercambia las cartas de una posicion aleatoria
		int aux = aleatorio(rng);
		Carta* tmp = carta[i];
		carta[i] = carta[aux];
		carta[aux] = tmp;
	}
}

std::string Mazo::mostrar() //Muestra todas las cartas del mazo 
{
    std::stringstream s;
	for (int i = 0;i < cant;i++) {
        s << carta[i]->mostrar() << std::endl;
	}
    return s.str();
}

void Mazo::cambiarCarta(Carta* c, int pos) //Se sobreescriben los atributos de la carta[pos]
{                                          //con los valores de la nueva carta que se ingresa
    carta[pos]->setValor(c->getValor());
    carta[pos]->setPalo(c->getPalo());
    carta[pos]->setTipo(c->getTipo());
    carta[pos]->setBocaAbajo(c->getBocaAbajo());
}

std::string Mazo::guardarMazo() //Guarda los atributos de cada carta del mazo en una hilera
{
    std::stringstream s;
    int ascii;
    for (int i = 0;i < cant;i++) {
        s << carta[i]->getValor() << " ";
        ascii = carta[i]->getPalo(); //Se guarda el valor ascii del char de Palo
        s << ascii << " ";
        s << carta[i]->getTipo() << " ";
        s << carta[i]->getBocaAbajo() << '\n';
    }
    return s.str();
}
