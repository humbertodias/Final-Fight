//
// Created by franco on 13/9/19.
//

#include "Lanzar.h"

void Lanzar::manejarEntrada(Personaje &personaje){

    //Actualizar posicion de jugador

    //Llamar a graficar.golpear()

    //Refrescar

}

Lanzar::Lanzar() {
    Logger logger(DEBUG);
    logger.log(DEBUG, "Se instancio un objeto de clase Lanzar");
}

Lanzar::~Lanzar() {
    Logger logger(DEBUG);
    logger.log(DEBUG, "Se elimino un objeto de clase Lanzar");
}

