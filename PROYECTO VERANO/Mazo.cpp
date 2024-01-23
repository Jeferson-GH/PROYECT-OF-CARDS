#include "Mazo.h"
#include <random>
#include "color.h"

Mazo::Mazo(): cant{52}
{
	carta = new Carta[52];
}

Mazo::~Mazo()
{
	delete[] carta;
}

void Mazo::inicializar()
{
	//3 corazones, 4 diamante, 5 trebol, 6 espada
	for (int i = 0;i < 4;i++) {
		//Asigna valores del 1 al 13
		for (int j = 0;j < 13;j++) {
			carta[i * 13 + j].valor = j + 1; 
			carta[i * 13 + j].palo = i+3;
			carta[i * 13 + j].tipo = 'N'; //Carta normal
			if (carta[i * 13 + j].palo == 3 or carta[i * 13 + j].palo == 4) //Asigna color dependiendo del palo
				carta[i * 13 + j].color = true; 

			//Asigna tipo de carta y ajusta valor correspondiente
			switch (carta[i * 13 + j].valor) {
			case 1:
				carta[i * 13 + j].tipo = 'A'; 
				break;

			case 11:
				carta[i * 13 + j].tipo = 'J'; 
				carta[i * 13 + j].valor -= 1;
				break;
				
			case 12:
				carta[i * 13 + j].tipo = 'Q'; 
				carta[i * 13 + j].valor -= 2; 
				break;
			case 13:
				carta[i * 13 + j].tipo = 'K'; 
				carta[i * 13 + j].valor -= 3;
				break;
			}
		}
	}
}

void Mazo::barajar()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> aleatorio(0, 52);

	for (int i = 0;i < 52;i++) {
		int aux = aleatorio(rng);
		Carta tmp = carta[i];
		carta[i] = carta[aux];
		carta[aux] = tmp;
	}
}

Carta* Mazo::tomarCarta()
{
	cant--;
	return &carta[cant];
}

void Mazo::mostrar() {
	for (int i = 0;i < 52;i++) {

		std::cout << "[";
		if (carta[i].color)
			std::cout << red << carta[i].palo << white;
		else
			std::cout << carta[i].palo;
		std::cout << "] | ";
		switch (carta[i].tipo) {
		case 'A':
			std::cout << "AS " << carta[i].valor << std::endl; break;

		case 'J':
			std::cout << "J " << carta[i].valor << std::endl; break;
		case 'Q':
			std::cout << "Q " << carta[i].valor << std::endl; break;
		case 'K':
			std::cout << "K " << carta[i].valor << std::endl; break;
		}
		if (carta[i].tipo=='N')
			std::cout << carta[i].valor << std::endl;
	}
}
