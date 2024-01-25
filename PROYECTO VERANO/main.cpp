#include <iostream>
#include "Jugador.h"

int main() {
	int opcion = 0;
	int cantidadJugadores;
	std::string nickname;

	std::cout << "\t Juego Blackjack \n" << '\n';
	std::cout << "1) Nuevo Juego" << '\n';
	std::cout << "2) Cargar Partida" << '\n';
	std::cout << "3) Salir" << '\n';
	std::cin >> opcion;
	
	if (opcion == 1) {
		system("cls");
		std::cout << "Cantidad de jugadores: ";
		std::cin >> cantidadJugadores;
		Jugador aux;
		for (int i = 0;i < cantidadJugadores;i++) {
			std::cout << "Nickname Jugador [" << i + 1 << "]: ";
			std::cin >> nickname;
		}
		Mazo mazo1;
		mazo1.inicializar();
		mazo1.barajar();
		Carta* p = mazo1.tomarCarta();
		std::cout << "\n\nMazo sin " << p->getPalo() << ' ' << p->getValor() << '\n';
		std::cout << mazo1.mostrar() << '\n';

		Mano mano;
		mano.agregarCarta(p);
		Carta* ptr = mazo1.tomarCarta();
		mano.agregarCarta(ptr);
		std::cout << "\n\nMazo sin " << ptr->getPalo() << ' ' << ptr->getValor() << '\n';
		std::cout << mazo1.mostrar() << '\n';
	
		

		std::cout << "\nMano: \n" << mano.mostrar();
		std::cout << "\nPuntos: " << mano.getPuntos();
	}

	return 0;
}