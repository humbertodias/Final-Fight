//
// Created by sebas on 2/9/19.
//

#ifndef FINAL_FIGHT_COMPORTAMIENTODEJUGADOR_H
#define FINAL_FIGHT_COMPORTAMIENTODEJUGADOR_H


#include "Comportamiento.h"
#include "../modelo/estados/EstadoDePersonaje.h"
#include "../fisica/FisicaDePersonaje.h"

class ComportamientoDeJugador : public Comportamiento {

private:
    EstadoDePersonaje* estado_;
    FisicaDePersonaje *fisica;

public:
    explicit ComportamientoDeJugador(FisicaDePersonaje *fisica);
    void actualizar() override;
    ~ComportamientoDeJugador();
};


#endif //FINAL_FIGHT_COMPORTAMIENTODEJUGADOR_H