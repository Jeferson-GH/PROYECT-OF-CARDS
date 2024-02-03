#ifndef CARTA_H
#define CARTA_H
#include <iostream>

class Carta
{
private:
    int valor;
    char palo;
    char tipo;
    bool bocaAbajo;

public:
    Carta();
    ~Carta();

    int getValor();
    char getPalo();
    char getTipo();
    bool getBocaAbajo();

    void setValor(int);
    void setPalo(int);
    void setBocaAbajo(bool);
    void setTipo(char);

    void voltear();
    std::string mostrar() const;
    
};


#endif
