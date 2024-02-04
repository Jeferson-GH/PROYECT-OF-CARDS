#include "Archivo.h"
#include <string>
#include "Jugador.h"

Archivo::Archivo(std::string nombre) : nombreArchivo{ nombre } {}

Archivo::~Archivo() {}

void Archivo::guardarPartida(Lista* lista, Mazo* baraja, Nodo* jugadorActual)
{
	std::ofstream archivo;
	archivo.open(nombreArchivo, std::ios::app);

	if (!archivo.is_open())
		return;

	std::string nicknameJugadorActual = jugadorActual->dato->getNickname();
	jugadorActual = lista->getInicio();
	archivo << lista->getCantidad() << '\n';
	archivo << lista->guardarNicknames();
	while (jugadorActual->next != nullptr) {
		archivo << jugadorActual->dato->getMano()->getCantidad() << '\n';
		archivo << jugadorActual->dato->guardarMano();
		jugadorActual = jugadorActual->next;
	}
	archivo << jugadorActual->dato->getMano()->getCantidad() << '\n';
	archivo << jugadorActual->dato->guardarMano();
	archivo << nicknameJugadorActual << '\n';

	archivo << baraja->guardarMazo() << '\n';
	archivo.close();
}

bool Archivo::cargarPartida(std::string nombreArchivo, Lista* &lista, Mazo* &baraja, Dealer* &dealer, Nodo* &jugadorActual)
{
	std::ifstream archivo;
	archivo.open(nombreArchivo);
	if (!archivo.is_open())
		return false;
	
	std::string nombres;
	char tipo;
	int cantidadJugadores, valores, x;
	archivo >> cantidadJugadores;
	for (int i = 1; i < cantidadJugadores; i++) {
		archivo >> nombres;
		lista->insertar(new Jugador(nombres));
	}
	delete dealer;
	dealer = new Dealer;
	lista->insertar(dealer);
	jugadorActual = lista->getInicio();
	for (int i = 0; i < cantidadJugadores; i++) {
		archivo >> x;
		for (int i = 0; i < x; i++) {
			Carta* carta = new Carta;
			archivo >> valores;
			carta->setValor(valores);
			archivo >> valores;
			carta->setPalo(valores);
			archivo >> tipo;
			carta->setTipo(tipo);
			archivo >> valores;
			carta->setBocaAbajo(valores);

			jugadorActual->dato->getMano()->agregarCarta(carta);
		}
		jugadorActual = jugadorActual->next;
	}
	archivo >> nombres;
	jugadorActual = lista->getJugador(nombres);

	int cantidad = 0;
	while (archivo >> valores) {
		Carta* carta = new Carta;
		carta->setValor(valores);
		archivo >> valores;
		carta->setPalo(valores);
		archivo >> tipo;
		carta->setTipo(tipo);
		archivo >> valores;
		carta->setBocaAbajo(valores);
		baraja->cambiarCarta(carta, cantidad);
		cantidad++;
		delete carta;
	}
	baraja->setCantidad(cantidad);
	archivo.close();
	return true;
}



