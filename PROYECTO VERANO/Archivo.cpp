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
	archivo << nicknameJugadorActual << '\n';
	archivo.close();
}

bool Archivo::cargarPartida(std::string nombreArchivo, Lista* &lista, Mazo* &baraja, Nodo* &jugadorActual)
{
	std::ifstream archivo;
	archivo.open(nombreArchivo);
	if (!archivo.is_open())
		return false;
	
	std::string aux;
	archivo >> aux;
	int x = std::stoi(aux);
	for (int i = 0; i < x; i++) {
		archivo >> aux;
		lista->insertar(new Jugador(aux));
	}
	archivo >> aux;
	x = std::stoi(aux);
	for (int i = 0; i < x; i++) {
		archivo >> aux;
		Carta* carta = new Carta;
		int y = std::stoi(aux);
		carta->setValor(y);
		y = std::stoi(aux);
		carta->setPalo(y);
		archivo >> aux; //Comvertir char cambiando la variable AUX a char en lugar de string
		//carta->setTipo(aux)
		//carta->setPalo()
		archivo >> aux;
		archivo >> aux;

		//jugadorActual->dato->getMano()->agregarCarta();
		jugadorActual = lista->getInicio();

	}
	return true;
}



