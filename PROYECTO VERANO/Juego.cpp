#include "Juego.h"
#include "Jugador.h"
#include <sstream>
#include <vector>
#include <algorithm> //Para utilizar la funcion std::find()
#include "Mano.h"

Juego::Juego() : baraja{ nullptr }, dealer{ nullptr }, jugadorActual{ nullptr }, listaJugadores{ nullptr } {}
Juego::~Juego()
{
	delete baraja;
	delete dealer;
	delete jugadorActual;
}
void Juego::agregarJugador(JugadorGenerico* n) { listaJugadores->insertar(n); }
void Juego::eliminarJugador(std::string n) { listaJugadores->borrar(n); }
void Juego::jugar(){
	agregarJugadores(); //Se agregan los jugadores al juego

	Mazo mazo;
	mazo.inicializar(); 
	mazo.barajar(); //Se inicializa el mazo y se baraja 

	jugadorActual = listaJugadores->getInicio(); //Se establece el primer jugador


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
		}
		else {
			std::cout << "\nCantidad de jugadores invalida. Intente nuevamente.\n\n";
			system("PAUSE");
		}
		system("CLS");

	} while (repetir);

}

bool Juego::pasarTurno() //Se pasa el turno en caso que la lista no se haya acabado
{
	if (jugadorActual->next == nullptr) { 
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
	if (jugadorActual->dato->sePaso())
		return true; 
	return false;
}