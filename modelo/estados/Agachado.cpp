//
// Created by franco on 8/9/19.
//

#include <SDL_scancode.h>
#include "Agachado.h"
#include "Parado.h"
#include "../../servicios/Logger.h"

EstadoDePersonaje *Agachado::manejarEntrada(FisicaDePersonaje *fisica, const Uint8 *entrada) {
    if ( entrada[SDL_SCANCODE_D] ){
        Velocidad &velocidad = fisica->velocidad();
        velocidad.x = 0;
        velocidad.y = 0;
        velocidad.z = 0;

        return nullptr;
    }else if ( entrada[SDL_SCANCODE_S] ){
        Saltando* saltando = new Saltando();
        saltando->manejarEntrada(fisica, entrada);
        return saltando;
    }else{
        return new Parado();
    }
}

Agachado::Agachado() {
    Logger logger(DEBUG);
    logger.log(DEBUG, "Se instancio un objeto de clase Agachado");
}

Agachado::~Agachado() {
    Logger logger(DEBUG);
    logger.log(DEBUG, "Se elimino un objeto de clase Agachado");
}

