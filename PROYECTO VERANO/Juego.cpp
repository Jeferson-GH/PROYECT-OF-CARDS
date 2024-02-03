#include <sstream>
#include <vector> 
#include <algorithm> //Para utilizar la funcion std::find()
#include "Juego.h"
#include "Jugador.h"
#include "Mano.h"
#include "Archivo.h"

Juego::Juego() : baraja{ new Mazo }, dealer{ new Dealer }, jugadorActual{ nullptr }, listaJugadores { new Lista } {}

Juego::~Juego() { delete baraja; delete dealer;	delete listaJugadores; }

void Juego::setJugadorActual(std::string nickname) { jugadorActual = listaJugadores->getJugador(nickname); }

void Juego::agregarJugador(JugadorGenerico* n) { listaJugadores->insertar(n); }

void Juego::eliminarJugador(std::string n) { listaJugadores->borrar(n); }

void Juego::jugar()
{
	int opcion;
	do {
		std::cout << "\t Juego Blackjack \n" << '\n';
		std::cout << "1) Nuevo Juego" << '\n';
		std::cout << "2) Cargar Partida" << '\n';
		std::cout << "3) Salir" << '\n';
		std::cin >> opcion;

		if (opcion == 1) {
			agregarJugadores(); //Se agregan los jugadores al juego

			while (opcion == 1) {

				baraja->inicializar(); //Se inicializa el mazo 

				baraja->barajar(); //Se barajan las cartas 

				repartirCartas(); //Se reparten las cartas automaticamente a cada jugador

				if (partida()) //Se muestra el flujo de la partida
				{
					opcion = 0; 
					system("cls");
					break;
				}

				turnoDealer(); //El dealer escoge su jugada 

				resultados(); //Se muestran los ganadores y perdedores

				restablecerPartida(); //Se limpian todos los datos de la partida, exceptuando la lista de jugadores

				std::cout << "\n1) Jugar de nuevo con los mismos jugadores\n" << "2) Salir\n";
				std::cin >> opcion;
				if (opcion == 2)
					opcion = 0;
				system("cls");
			} 
			limpiarPartida();
		}
		if (opcion == 2) {
			opcion = 1;
			bool repetirPartida = false;
			std::string nombreArchivo;
			std::cout << "Ingrese el nombre del archivo a cargar: ";
			std::cin >> nombreArchivo;
			Archivo archivo(nombreArchivo);
			archivo.cargarPartida(nombreArchivo, listaJugadores, dealer, jugadorActual);
			system("cls");

			while (opcion == 1) {

				baraja->inicializar(); //Se inicializa el mazo 

				baraja->barajar(); //Se barajan las cartas 

				if (repetirPartida)
					repartirCartas();

				if (partida()) //Se muestra el flujo de la partida
				{
					opcion = 0;
					system("cls");
					break;
				}

				turnoDealer(); //El dealer escoge su jugada 

				resultados(); //Se muestran los ganadores y perdedores

				restablecerPartida(); //Se limpian todos los datos de la partida, exceptuando la lista de jugadores

				std::cout << "\n1) Jugar de nuevo con los mismos jugadores\n" << "2) Salir\n";
				std::cin >> opcion;
				if (opcion == 2)
					opcion = 0;
				system("cls");
				repetirPartida = true;
			}
			limpiarPartida();
		}
	} while (opcion == 0);

	if (opcion == 3) {
		system("cls");
		return;
	}
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

void Juego::pasarTurno() //Se pasa el turno hasta llegar al Dealer
{
	if (jugadorActual->dato != dealer) { 
		jugadorActual = jugadorActual->next;
	}
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
	bool repetir = true;
	system("cls");
	std::cout << "\t Turno del dealer: \n\n" << dealer->mostrar();
	std::cout << "Presione cualquier tecla para saber su carta oculta \n\n";
	system("pause");
	system("cls");
	dealer->volteaSegunda();
	while (repetir) {
		std::cout << dealer->mostrar();
		system("pause");
		system("cls");
		if (dealer->getPuntos() < 16) {
			std::cout << "El dealer toma una carta\n\n";
			dealer->pedirCarta(baraja);
		}
		else {
			std::cout << "El dealer decide plantarse\n";
			repetir = false;
		}
	}
	std::cout << "Culmina el turno del dealer, presione cualquier tecla para ver los resultados\n\n";
	system("pause");
	system("cls");
}

bool Juego::partida()
{
	char opcion;
	int opcionAS;
	bool repetir = true;
	while (jugadorActual->dato != dealer) { //Termina el ciclo cuando se llega al dealer
		std::cout << mostrarJuego() << '\n';
		if (jugadorActual->dato->getMano()->hayAS() and repetir) {
			repetir = false;
			std::cout << "\nCambiar AS?\n" << "1) Si\n" << "2) No\n";
			std::cin >> opcionAS;
			if (opcionAS == 1) {
				jugadorActual->dato->cambiarValorAS();
			}
			system("cls");
			std::cout << mostrarJuego() << '\n';
		}
		std::cin >> opcion;
		switch (opcion) { //Se evalua la jugada
		case 'd': //Agrega una carta a la mano y vuelve a desplegar en pantalla
			jugadorActual->dato->pedirCarta(baraja);
			std::cout << mostrarJuego();
			if (pierde()) { //En el caso que pierda el jugador actual:
				system("cls");
				std::cout << '\n' << jugadorActual->dato->getNickname() << " perdio, pasando al siguiente turno\n";
				std::cout << "Mano del jugador: " << jugadorActual->dato->mostrar() << "\n\n";
				pasarTurno(); //Se pasa de turno
				system("pause");
			}
			break;
		case 'p':
			pasarTurno(); //Pasa el turno
			break;
		case 'g': //Guardar partida
		{		
			std::string nombreArchivo;
			system("cls");
			std::cout << "Ingrese el nombre con el que quiere guardar la partida: ";
			std::cin >> nombreArchivo;
			Archivo archivo(nombreArchivo);
		//	nombreArchivo += ".txt";
			archivo.guardarPartida(listaJugadores, baraja, jugadorActual);
			return true;
		}
		case 's':
			return true; //Salir del juego 
		}
		system("cls");
		repetir = true;
	}
	return false;
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
			if (!jugadorActual->dato->sePaso()) {
				if (jugadorActual->dato->getPuntos() > dealer->getPuntos()) {
					std::cout << " '" << jugadorActual->dato->getNickname() << "' gano con " << jugadorActual->dato->getPuntos() << " en mano\n";
				}
				if (jugadorActual->dato->getPuntos() == dealer->getPuntos()) {
					std::cout << " '" << jugadorActual->dato->getNickname() << "' empato con " << jugadorActual->dato->getPuntos() << " en mano\n";

				}
				if (jugadorActual->dato->getPuntos() < dealer->getPuntos()) {
					std::cout << " '" << jugadorActual->dato->getNickname() << "' perdio con " << jugadorActual->dato->getPuntos() << " en mano\n";
				}
			}
			else {
				std::cout << " '" << jugadorActual->dato->getNickname() << "' se paso con " << jugadorActual->dato->getPuntos() << " en mano\n";
			}
			pasarTurno();
		} while (jugadorActual->dato!=dealer);
	}
}

void Juego::restablecerPartida()
{
	jugadorActual = listaJugadores->getInicio();
	while (jugadorActual->next != nullptr) {
		jugadorActual->dato->getMano()->limpiar();
		jugadorActual = jugadorActual->next;
	}
	delete dealer;
	dealer = new Dealer;
	delete baraja;
	baraja = new Mazo;
	jugadorActual = listaJugadores->getInicio();
}

void Juego::limpiarPartida()
{
	jugadorActual = listaJugadores->getInicio();
	while (jugadorActual->next != nullptr) {
		jugadorActual->dato->getMano()->limpiar();
		jugadorActual = jugadorActual->next;
	}
	delete dealer;
	dealer = new Dealer;
	delete baraja;
	baraja = new Mazo;
	delete listaJugadores;
	listaJugadores = new Lista;
}
