//
// Created by franco on 8/9/19.
//

#ifndef FINAL_FIGHT_SALTANDO_H
#define FINAL_FIGHT_SALTANDO_H

#include "EstadosDePersonaje.h"

#define LIMITE 30 // Limite del salto en altura

class Saltando : public EstadosDePersonaje{

private:
    int alturaMaxima_ = LIMITE; // Numero de prueba SUPER HARDCODE
    bool subiendo_ = true;

public:
    EstadosDePersonaje *manejarEntrada(Personaje& personaje, const Uint8* entrada) override;
    void actualizar(Personaje& personaje) override;

};

#endif //FINAL_FIGHT_SALTANDO_H
