#ifndef CARTA_H
#define CARTA_H
#include <iostream>

class Carta
{
private:
    int valor;
    char palo;
    bool color;
    char tipo;
    bool bocaAbajo;

public:
    Carta();
    ~Carta();

    int getValor() const;
    int getPalo() const;
    bool getBocaAbajo() const;

    void setValor(int);
    void setPalo(int);
    void setColor(bool);
    void setBocaAbajo(bool);
    void setTipo(char);

    void voltear();
    void mostrar() const;
    
};


#endif
