//
// Created by franco on 13/9/19.
//

#include "Parado.h"

void Parado::manejarEntrada(Personaje &personaje){

    //Actualizar posicion de jugador

    //Llamar a graficar.parado()

    //Refrescar

}

Parado::Parado() {
    Logger logger(DEBUG);
    logger.log(DEBUG, "Se instancio un objeto de clase moverAbajo");
}

Parado::~Parado() {
    Logger logger(DEBUG);
    logger.log(DEBUG, "Se elimino un objeto de clase moverAbajo");
}