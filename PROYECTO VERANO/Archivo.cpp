#include "Archivo.h"
#include <string>
#include "Jugador.h"

//Constructor y destructor
Archivo::Archivo(std::string nombre) : nombreArchivo{ nombre } {}
Archivo::~Archivo() {}

void Archivo::guardarPartida(Lista* lista, Mazo* baraja, Nodo* jugadorActual) //Guarda la informacion del estado de la partida
{
	std::ofstream archivo;
	archivo.open(nombreArchivo, std::ios::app); //Se abre el archivo para escritura

	if (!archivo.is_open()) //Termina la funcion si no se abrio el archivo
		return;

	std::string nicknameJugadorActual = jugadorActual->dato->getNickname(); //Se guarda el nickname del jugador actual
	jugadorActual = lista->getInicio(); // Se actualiza el jugador actual al inicio de la lista

	archivo << lista->getCantidad() << '\n'; // Se escribe la cantidad de jugadores en la lista
	archivo << lista->guardarNicknames(); // Se guardan los nicknames de los jugadores en la lista

	while (jugadorActual != nullptr) { // Recorre la lista de jugadores
		archivo << jugadorActual->dato->getMano()->getCantidad() << '\n'; // Se escribe la cantidad de cartas en la mano del jugador actual
		archivo << jugadorActual->dato->guardarMano(); // Se guardan las cartas de la mano del jugador actual
		jugadorActual = jugadorActual->next;
	}
	archivo << nicknameJugadorActual << '\n'; // Se guarda el nickname del jugador que conserva el turno
	archivo << baraja->guardarMazo() << '\n'; // Se guardan las cartas restantes en el mazo
	archivo.close(); // Se cierra el archivo
}

bool Archivo::cargarPartida(std::string nombreArchivo, Lista*& lista, Mazo*& baraja, Dealer*& dealer, Nodo*& jugadorActual)
{
	std::ifstream archivo;
	archivo.open(nombreArchivo); // Se abre el archivo para lectura
	if (!archivo.is_open()) // Retorna false si no se pudo abrir el archivo
		return false;

	std::string nombres; //Se declaran distintas variables para diferentes valores de datos
	char tipo;
	int cantidadJugadores, valores, x;
	archivo >> cantidadJugadores; // Se lee la cantidad de jugadores guardados en el archivo
	for (int i = 1; i < cantidadJugadores; i++) { // Se itera para leer los nombres de los jugadores
		archivo >> nombres;
		lista->insertar(new Jugador(nombres)); // Se inserta un nuevo jugador en la lista
	}
	delete dealer; // Se libera la memoria del dealer anterior para crear uno nuevo
	dealer = new Dealer;
	lista->insertar(dealer); // Se inserta el dealer en la lista
	jugadorActual = lista->getInicio(); // Se asigna el jugador actual como el primer jugador de la lista
	for (int i = 0; i < cantidadJugadores; i++) { //Leen las manos de los jugadores
		archivo >> x; // Se lee la cantidad de cartas en la mano del jugador actual
		for (int i = 0; i < x; i++) { // Se itera para leer cada carta en la mano del jugador actual
			Carta* carta = new Carta;
			archivo >> valores;
			carta->setValor(valores);
			archivo >> valores;
			carta->setPalo(valores);
			archivo >> tipo;
			carta->setTipo(tipo);
			archivo >> valores;
			carta->setBocaAbajo(valores);

			jugadorActual->dato->getMano()->agregarCarta(carta); // Se agrega la carta a la mano del jugador actual
		}
		jugadorActual = jugadorActual->next;
	}
	archivo >> nombres;
	jugadorActual = lista->getJugador(nombres); // Se asigna el jugador actual como el jugador que conservo el turno en la partida guardada

	int cantidad = 0; // Variable para almacenar la cantidad de cartas en el mazo
	while (archivo >> valores) { // Se itera para leer las cartas restantes en el mazo
		Carta* carta = new Carta;
		carta->setValor(valores);
		archivo >> valores;
		carta->setPalo(valores);
		archivo >> tipo;
		carta->setTipo(tipo);
		archivo >> valores;
		carta->setBocaAbajo(valores);
		baraja->cambiarCarta(carta, cantidad); // Se cambia la carta en el mazo
		cantidad++;
		delete carta; //Liberamos memoria de la carta creada
	}
	baraja->setCantidad(cantidad); // Se establece la cantidad total de cartas en el mazo
	archivo.close(); // Se cierra el archivo
	return true; // Retorna true si se logro cargar la partida
}
