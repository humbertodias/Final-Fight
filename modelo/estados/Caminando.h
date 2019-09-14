//
// Created by franco on 13/9/19.
//

#ifndef FINAL_FIGHT_CAMINANDO_H
#define FINAL_FIGHT_CAMINANDO_H

#include "EstadoDePersonaje.h"

class Caminando : public EstadoDePersonaje{

public:
    Caminando();
    ~Caminando();
    virtual EstadoDePersonaje *manejarEntrada(FisicaDePersonaje *fisica, const Uint8* entrada);
    void enter() override {};
    void actualizar() override {};
};

#endif //FINAL_FIGHT_CAMINANDO_H
