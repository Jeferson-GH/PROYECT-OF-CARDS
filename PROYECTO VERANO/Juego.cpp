#include <sstream>
#include <vector> 
#include <algorithm> //Para utilizar la funcion std::find()
#include "Juego.h"
#include "Jugador.h"
#include "Mano.h"
#include "Archivo.h"
#include <io.h>
#include <fcntl.h>
#include <windows.h>
//Constructor y destructor
Juego::Juego() : baraja{ new Mazo }, dealer{ new Dealer }, listaJugadores { new Lista }, jugadorActual { nullptr } {}
Juego::~Juego() { delete baraja; delete dealer;	delete listaJugadores; }

bool Juego::pierde() { return jugadorActual->dato->sePaso(); } //Determina si el jugador se pasa de 21

void Juego::agregarJugador(JugadorGenerico* n) { listaJugadores->insertar(n); } //Se agrega un jugador a la lista

void Juego::jugar(){
	mostrar();
	int opcion;
	do { //Menu principal
		std::cout << "\t Juego Blackjack \n" << '\n';
		std::cout << "1) Nuevo Juego" << '\n';
		std::cout << "2) Cargar Partida" << '\n';
		std::cout << "3) Salir" << '\n';
		std::cin >> opcion;

		if (opcion == 1) { //Si se elige '1' se inicia un nuevo juego

			agregarJugadores(); //Se agregan jugadores a la lista de juego

			while (opcion == 1) {

				baraja->inicializar(); //Se inicializa el mazo 

				baraja->barajar(); //Se barajan las cartas 

				repartirCartas(); //Se reparten las cartas automaticamente a cada jugador

				if (partida()) //Se muestra el flujo de la partida
				{ //Si partida retorna true, quiere decir que se quiso salir de la ejecucion del juego
					opcion = 0; 
					system("cls");
					break; //Break para salir del while
				}

				turnoDealer(); //El dealer escoge su jugada 

				resultados(); //Se muestran los ganadores y perdedores

				restablecerPartida(); //Se limpian todos los datos de la partida, exceptuando la lista de jugadores

				std::cout << "\n1) Jugar de nuevo con los mismos jugadores\n" << "2) Salir\n";
				std::cin >> opcion;
				if (opcion == 2) //	Si se quiere salir, la opcion se vuelve 0 para asi no repetir el ciclo y regresar al menu principal 
					opcion = 0;
				system("cls");
			} 
			limpiarPartida(); //Se limpian todos los datos de la partida al momento de salir 
		}
		if (opcion == 2) { //Si se elige '2' se carga una partida guardada
			opcion = 1; //Opcion se vuelve 1 para poder entrar al juego correctamente
			bool repetirPartida = false; 
			std::string nombreArchivo;

			system("cls");
			std::cout << "Ingrese el nombre del archivo a cargar: ";
			std::cin >> nombreArchivo;

			Archivo archivo(nombreArchivo); //Se crea el archivo con el nombre deseado
			if (!archivo.cargarPartida(nombreArchivo, listaJugadores, baraja, dealer, jugadorActual)) { //En el caso que no haya un archivo con ese nombre:
				system("cls");
				std::cout << "Error al cargar partida...\n\n";
				system("pause");
				system("cls");
				opcion = 0; //Opcion se vuelve 0 para volver al menu principal

			}
			else { //Si el archivo se cargo correctamente:
				system("cls");
				while (opcion == 1) {
					if (repetirPartida) { //repetirPartida se mantiene false en la primera iteracion, asi evitamos repartir las cartas

						baraja->inicializar(); //Si se quiso repetir la partida, se reparten las cartas como se haria normalmente
						baraja->barajar();
						repartirCartas(); 
					}

					if (partida()) //Se muestra el flujo de la partida
					{ //Si partida retorna true, quiere decir que se quiso salir de la ejecucion del juego
						opcion = 0; //Opcion se vuelve 0 para salir al menu principal
						system("cls");
						break;
					}

					turnoDealer(); //El dealer escoge su jugada 

					resultados(); //Se muestran los ganadores y perdedores

					restablecerPartida(); //Se limpian todos los datos de la partida, exceptuando la lista de jugadores

					std::cout << "\n1) Jugar de nuevo con los mismos jugadores\n" << "2) Salir\n";
					std::cin >> opcion;
					if (opcion == 2) //Si se quiere salir, opcion se vuelve 0 para ir al menu principal
						opcion = 0;
					system("cls");
					repetirPartida = true; //Si se quiere repetir la partida, se vuelve true
				}
				limpiarPartida(); //Se limpian todos los datos del juego al salir
			}
		}
	} while (opcion == 0); //Ciclo para volver al menu principal

	if (opcion == 3) { //Si se quiere salir en su totalidad, se limpia la consola y terminamos funcion
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
					std::cout << ".....Ingresar Nickname sin espacios.....\n";
					std::cout << "Nickname Jugador [" << i + 1 << "]: ";
					std::cin >> nickname;

					//Confirma si el nickname esta repetido en la lista
					nicknameRepetido = std::find(listaNicknames.begin(), listaNicknames.end(), nickname) != listaNicknames.end();

					if (nicknameRepetido) {
						std::cout << "El nickname ya esta en uso. Por favor, elija otro.\n";
					}

				} while (nicknameRepetido);
				//Posteriormente se agrega el nickname a la listaNickname y se inserta el jugador a la lista de jugadores
				Jugador* jugador = new Jugador(nickname);
				listaNicknames.push_back(nickname);
				listaJugadores->insertar(jugador);
			}
			repetir = false; //Sale del ciclo una vez que los jugadores sean ingresados correctamente
			agregarJugador(dealer); //Se agrega al dealer como ultimo jugador
		}
		else { //En caso que se ingrese una cantidad invalida:
			std::cout << "\nCantidad de jugadores invalida. Intente nuevamente.\n\n";
		}
		system("CLS");

	} while (repetir);

}

void Juego::repartirCartas() //Reparte las cartas iniciales a todos los jugadores
{
	for (int i = 0; i < 2; i++) { //Se asignan dos cartas a la mano de los jugadores
		jugadorActual = listaJugadores->getInicio(); //Se establece el primer jugador al inicio de la lista
		while (jugadorActual != nullptr) {
			jugadorActual->dato->pedirCarta(baraja);
			jugadorActual = jugadorActual->next;
		}
	}
	dealer->volteaSegunda(); //Al terminar de repartir, se le da vuelta a la segunda carta del Dealer
	jugadorActual = listaJugadores->getInicio(); //Reeestablece el jugador actual a inicio
}

void Juego::pasarTurno() //Se pasa el turno de los jugadores; no se ejecuta si se llega al Dealer
{
	if (jugadorActual->dato != dealer) { 
		jugadorActual = jugadorActual->next;
	}
}

void Juego::mostrarJuego() //Se muestra el estado actual del juego
{
	std::cout << dealer->mostrar() << '\n';
	std::cout << jugadorActual->dato->mostrar();
	std::cout << "(D)eme Carta  -  (P)asar  -  (G)uardar Partida  -  (S)alir\n";
}

void Juego::mostrar(){
	std::cout << "***************************************" << '\n';
	std::cout << "* BIENVENIDO A ESTE MARAVILLOSO JUEGO *" << '\n';
	std::cout << "***************************************" << '\n';
	system("pause");
	system("cls");
	std::cout << "***************************************" << '\n';
	std::cout << "*  DONDE NECESITAS GANARLE AL DEALER  *" << '\n';
	std::cout << "*   Y OBTENER EL MAZO MAS ALTO SIN    *" << '\n';
	std::cout << "*       PASARSE DE 21 PUNTOS          *" << '\n';
	std::cout << "***************************************" << '\n';
	system("pause");
	system("cls");
	std::cout << "***************************************" << '\n';
	std::cout << "*************** ESTO ES ***************" << '\n';
	std::cout << "***************************************" << '\n';
	system("pause");
	system("cls");
	std::cout << "***********************" << '\n';
	std::cout << "*                     *" << '\n';
	std::cout << "*      BLACK JACK     *" << '\n';
	std::cout << "*   ________________  *" << '\n';
	std::cout << "*  |D      *       C| *" << '\n';
	std::cout << "*  |    *     *     | *" << '\n';
	std::cout << "*  |  *    21   *   | *" << '\n';
	std::cout << "*  |    *     *     | *" << '\n';
	std::cout << "*  |P      *       T| *" << '\n';
	std::cout << "*  |________________| *" << '\n';
	std::cout << "*                     *" << '\n';
	std::cout << "***********************" << '\n';
	system("pause");
	system("cls");
}

void Juego::turnoDealer() //Evalua la jugada que tomara el dealer dependiendo de los puntos que tenga
{	
	bool repetir = true;

	system("cls");
	std::cout << "\t Turno del dealer: \n\n" << dealer->mostrar();
	std::cout << "Presione cualquier tecla para saber su carta oculta \n\n";
	system("pause");
	system("cls");

	dealer->volteaSegunda(); //Se deja ver la carta oculta del Dealer
	while (repetir) { //Repite las instrucciones si el dealer no se planta
		std::cout << dealer->mostrar();
		system("pause");
		system("cls");
		if (dealer->getPuntos() < 16) { //Se le agrega una carta a la mano
			std::cout << "El dealer toma una carta\n\n";
			dealer->pedirCarta(baraja);
		}
		else {
			std::cout << "El dealer decide plantarse\n";
			repetir = false; //Sale del ciclo
		}
	}

	std::cout << "Culmina el turno del dealer, presione cualquier tecla para ver los resultados\n\n";
	system("pause");
	system("cls");
}

bool Juego::partida() //Opera las elecciones del jugador actual
{
	char opcion;
	int opcionAS;
	bool repetir = true;

	while (jugadorActual->dato != dealer) { //Termina el ciclo cuando se llega al Dealer
		mostrarJuego();
		if (jugadorActual->dato->getMano()->hayAS() and repetir) { //Evalua si hay un AS en la mano
			repetir = false;
			std::cout << "\n\nCambiar AS?\n" << "1) Si\n" << "2) No\n"; //Se permite la opcion de cambiar el valor del AS de 1 a 11
			std::cin >> opcionAS;
			if (opcionAS == 1) { //Se cambia el valor
				jugadorActual->dato->cambiarValorAS();
			}
			system("cls");
			mostrarJuego(); //Vuelve a mostrar la pantalla de juego
		}
		std::cin >> opcion; //Se habilita la opcion de escoger la jugada
		switch (opcion) { //Se evalua la jugada
		case 'd':
		case 'D':
		//Agrega una carta a la mano y vuelve a desplegar en pantalla
			jugadorActual->dato->pedirCarta(baraja);
			mostrarJuego();
			if (pierde()) { //En el caso que pierda el jugador actual:
				system("cls");
				std::cout << '\n' << jugadorActual->dato->getNickname() << " perdio, pasando al siguiente turno\n\n";
				std::cout << "Mano del jugador: " << jugadorActual->dato->mostrar() << "\n\n";
				pasarTurno(); //Se pasa de turno
				system("pause");
			}
			break;
		case 'p' :
		case 'P':
			pasarTurno(); //Pasa el turno
			break;
		case 'g':
		case 'G'://Guardar partida
		{		
			std::string nombreArchivo;
			system("cls");
			std::cout << "Ingrese el nombre con el que quiere guardar la partida: ";
			std::cin >> nombreArchivo;
			Archivo archivo(nombreArchivo);
			archivo.guardarPartida(listaJugadores, baraja, jugadorActual); //Se guardan los datos de la partida en un archivo
			return true; //Devuelve true para salir 
		}
		case 's':
		case 'S':
			return true; //Salir del juego 
		}
		system("cls");
		repetir = true; //Sigue el juego ya que no se quiso salir 
	}
	return false; //Retorna false si en ningun momento se salio de la partida
}

void Juego::resultados() //Se despliegan los resultados del juego actual
{
	jugadorActual = listaJugadores->getInicio();
	std::cout << "Lista de resultados: \n\n";

	if (dealer->sePaso()) { //Si el dealer se pasa, todos los jugadores ganan
		std::cout << "Dealer perdio con " << dealer->getPuntos() << " puntos en mano\n\n";
		std::cout << "Todos los jugadores restantes ganan\n";
	}
	else {
		std::cout << "Dealer termina el juego con " << dealer->getPuntos() << " puntos en mano\n";
		do { //Se muestra que jugador gano, perdio o empato con el dealer
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
		} while (jugadorActual->dato!=dealer); //Deja de iterar cuando se llega al Dealer
	}
}

void Juego::restablecerPartida() //Se reestablece el estado del juego para poder jugar de nuevo
{
	jugadorActual = listaJugadores->getInicio();
	while (jugadorActual->next != nullptr) {
		jugadorActual->dato->getMano()->limpiar(); //Se limpian las manos de todos los jugadores
		jugadorActual = jugadorActual->next;
	}
	delete dealer; //Se crean nuevas instancias de mazo y dealer
	dealer = new Dealer;
	delete baraja;
	baraja = new Mazo; 
	jugadorActual = listaJugadores->getInicio(); //Se reestablece el jugadorActual al inicio de la lista
}

void Juego::limpiarPartida() //Se limpia la partida en su totalidad
{
	restablecerPartida();
	delete listaJugadores;
	listaJugadores = new Lista;
}
