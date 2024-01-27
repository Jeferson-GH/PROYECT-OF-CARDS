#include "Juego.h"
#include "Jugador.h"
#include <sstream>
#include <vector>
#include <algorithm> //Para utilizar la funcion std::find()
#include "Mano.h"

Juego::Juego()
{
}

Juego::~Juego()
{
}

void Juego::jugar()
{
	agregarJugadores(); //Se agregan los jugadores al juego

	Mazo mazo;
	mazo.inicializar(); 
	mazo.barajar(); //Se inicializa el mazo y se baraja 


}
void Juego::agregarJugador(JugadorGenerico* n) { listaJugadores->insertar(n); }

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

					//Se confirma si el nickname esta repetido en la lista
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


