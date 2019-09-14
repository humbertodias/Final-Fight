//
// Created by franco on 6/9/19.
//

#ifndef FINAL_FIGHT_PARADO_H
#define FINAL_FIGHT_PARADO_H

#include "EstadoDePersonaje.h"
#include "Saltando.h"

class Parado : public EstadoDePersonaje{

private:

public:
    Parado();
    ~Parado();
    virtual EstadoDePersonaje *manejarEntrada(FisicaDePersonaje *fisica, const Uint8* entrada);
    void actualizar() override {};
    void enter() override {};
};

#endif //FINAL_FIGHT_PARADO_H
