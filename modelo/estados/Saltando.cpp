//
// Created by franco on 8/9/19.
//

#include "Saltando.h"
#include "Parado.h"
#include "../../servicios/Logger.h"

EstadoDePersonaje* Saltando::manejarEntrada(FisicaDePersonaje *fisica, const Uint8* entrada){

    Velocidad &velocidad = fisica->velocidad();
    if ( subiendo_ ) {
        if (alturaMaxima_ > 0) {
            velocidad.z -= 7;
            alturaMaxima_--;
        } else {
            subiendo_ = false;
            alturaMaxima_ = LIMITE;
        }
    } else if ( ! subiendo_ && alturaMaxima_ > 0){
        velocidad.z += 7;
        alturaMaxima_--;
    }else{
        return new Parado();
    }
    return nullptr;

}

Saltando::Saltando() {
    Logger logger(DEBUG);
    logger.log(DEBUG, "Se instancio un objeto de clase Saltando");
}

Saltando::~Saltando() {
    Logger logger(DEBUG);
    logger.log(DEBUG, "Se elimino un objeto de clase Saltando");
}