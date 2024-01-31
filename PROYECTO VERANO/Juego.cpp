#include <sstream>
#include <vector> 
#include <algorithm> //Para utilizar la funcion std::find()
#include <random>
#include "Juego.h"
#include "Jugador.h"
#include "Mano.h"

Juego::Juego() : baraja{ new Mazo }, dealer{ new Dealer }, jugadorActual{ nullptr }, listaJugadores { new Lista } {}
Juego::~Juego()
{
	delete baraja;
	delete dealer;
	delete listaJugadores;
	
}
void Juego::agregarJugador(JugadorGenerico* n) { listaJugadores->insertar(n); }
void Juego::eliminarJugador(std::string n) { listaJugadores->borrar(n); }

void Juego::jugar()
{
	agregarJugadores(); //Se agregan los jugadores al juego


	baraja->inicializar(); 
	baraja->barajar(); //Se inicializa el mazo y se baraja 
	repartirCartas(); //Se reparten las cartas automaticamente 

	partida();

	turnoDealer();
	resultados();

}
void Juego::agregarJugadores() //Agrega jugadores a la lista de juego.
{ 

	int cantidadJugadores;
	std::string nickname;
	bool repetir = true;

	do {
		system("CLS");
		std::cout << "Cantidad de jugadores: ";
		std::cin >> cantidadJugadores; 

		if (cantidadJugadores > 0 and cantidadJugadores <= 7) { //Validacion de entrada de jugadores
			std::cout << "\n";
			std::vector<std::string> listaNicknames; //Se crea una lista de los nombres a ingresar
			for (int i = 0; i < cantidadJugadores; i++) {
				std::string nickname;
				bool nicknameRepetido;
				do {
					std::cout << "Nickname Jugador [" << i + 1 << "]: ";
					std::cin >> nickname;

					//Confirma si el nickname esta repetido en la lista
					nicknameRepetido = std::find(listaNicknames.begin(), listaNicknames.end(), nickname) != listaNicknames.end();

					if (nicknameRepetido) {
						std::cout << "El nickname ya esta en uso. Por favor, elija otro.\n";
					}

				} while (nicknameRepetido);
				//Posteriormente se agrega el nickname a la listaNickname y se agrega el jugador a la lista de jugadores
				Jugador* jugador = new Jugador(nickname);
				listaNicknames.push_back(nickname);
				listaJugadores->insertar(jugador);
			}
			repetir = false; //Sale del ciclo una vez que los jugadores sean ingresados correctamente
			agregarJugador(dealer); //Se agrega al dealer como ultimo jugador
		}
		else {
			std::cout << "\nCantidad de jugadores invalida. Intente nuevamente.\n\n";
		}
		system("CLS");

	} while (repetir);

}

void Juego::repartirCartas() //Reparte las cartas iniciales a todos los jugadores
{
	for (int i = 0; i < 2; i++) {
		jugadorActual = listaJugadores->getInicio(); //Se establece el primer jugador
		while (jugadorActual->next != nullptr) {
			jugadorActual->dato->pedirCarta(baraja);
			jugadorActual = jugadorActual->next;
		}
		jugadorActual->dato->pedirCarta(baraja); //Se asigna dos cartas a la mano de los jugadores
	}
	dealer->volteaSegunda(); //Al terminar de repartir, se le da vuelta a la segunda carta del Dealer
	jugadorActual = listaJugadores->getInicio();
}

bool Juego::pasarTurno() //Se pasa el turno hasta llegar al Dealer
{
	if (jugadorActual->dato == dealer) { 
		return 0; 
	}
	jugadorActual = jugadorActual->next;
	return 1; //Indica si se hizo el cambio
}

int Juego::jugada(char n) //Retorna un numero dependiendo de la jugada 
{
	if ((n == 'D') or (n == 'd')) { //Le da una carta al jugador
		jugadorActual->dato->pedirCarta(baraja);
		return 1;
	}
	if ((n == 'P') or (n == 'p')) { //Se pasa el turno
		if (pasarTurno()) {
			return 2;
		}
		return 3; //Retorna 3 si no se paso
	}
	if ((n == 'G') or (n == 'g')) { //Se guarda la partida
		return 4;
	}

	if ((n == 'S') || (n == 's')) { //Salir del juego
		return 5;
	}
	return 0; //Retorna valor default
}

bool Juego::pierde() //Determina si el jugador se pasa de 21
{ 
	return jugadorActual->dato->sePaso();
}

std::string Juego::mostrarJuego()
{
	std::stringstream s;
	s << dealer->mostrar() << '\n';
	s << jugadorActual->dato->mostrar();
	s << "(D)eme Carta  -  (P)asar  -  (G)uardar Partida  -  (S)alir";
	return s.str();
}

void Juego::turnoDealer() //Evalua la jugada que tomara el dealer dependiendo de los puntos que tenga
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> aleatorio(0, 1);

	if (dealer->getPuntos() < 16) {
		dealer->pedirCarta(baraja);
	} 
	if (dealer->getPuntos() >= 16 and dealer->getPuntos() < 18) {
		if (aleatorio(rng)) {
			dealer->pedirCarta(baraja);
		}
		else {
			return;
		}
	}
	if (dealer->getPuntos() >= 18) {
		return;
	}
}

void Juego::partida()
{
	char opcion;
	bool repetir = true;
	while (jugadorActual->dato != dealer) { //Termina el ciclo cuando se llega al dealer
		std::cout << mostrarJuego();
		std::cin >> opcion;

		switch (jugada(opcion)) { //Se evalua la jugada
		case 1: //Agrega una carta a la mano y vuelve a desplegar en pantalla
			std::cout << mostrarJuego();
			if (pierde()) { //En el caso que pierda el jugador actual:
				std::string nom = jugadorActual->dato->getNickname();
				if (pasarTurno()) { //Se elimina al jugador y se pasa de turno
					eliminarJugador(nom);
					system("cls");
					std::cout << '\n' << nom << " perdio, pasando al siguiente turno\n\n";
					system("pause");
				}
			}
			break;
		case 2:
			break; //Pasa el turno
		case 3:
			break; //No se cambio el turno
		case 4:
			break; //Guardar partida
		case 5:
			break; //Salir del juego (ir al menu principal o terminar programa)
		}
		system("cls");
	}
}

void Juego::resultados()
{
	jugadorActual = listaJugadores->getInicio();
	std::cout << "Lista de resultados: \n\n";

	if (dealer->sePaso()) {
		std::cout << "Dealer perdio con " << dealer->getPuntos() << " puntos en mano\n\n";
		std::cout << "Todos los jugadores restantes ganan";
	}
	else {
		std::cout << "Dealer termina el juego con " << dealer->getPuntos() << " puntos en mano\n";
		do {
			if (jugadorActual->dato->getPuntos() > dealer->getPuntos()) {
				std::cout << " '" << jugadorActual->dato->getNickname() << "' gano con " << jugadorActual->dato->getPuntos() << " en mano\n";
			}
			if (jugadorActual->dato->getPuntos() < dealer->getPuntos()) {
				std::cout << " '" << jugadorActual->dato->getNickname() << "' perdio con " << jugadorActual->dato->getPuntos() << " en mano\n";
			}
			if (jugadorActual->dato->getPuntos() == dealer->getPuntos()) {
				std::cout << " '" << jugadorActual->dato->getNickname() << "' empato con " << jugadorActual->dato->getPuntos() << " en mano\n";

			}
		} while (pasarTurno() and jugadorActual->dato!=dealer);
	}
}