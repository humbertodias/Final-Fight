//
// Created by leo on 4/11/19.
//

#include "Puntaje.h"
#include "../../servicios/Locator.h"

void Puntaje::serializar(ostream &stream) {
    Serializable::serializarEntero(stream, this->puntos);
}

void Puntaje::deserializar(istream &stream) {
    this->puntos = Serializable::deserializarEntero(stream);
}

void Puntaje::agregarPuntos(int puntosRecibidos) {
    Locator::logger()->log(INFO, "Se agregan puntos al jugador: " + puntosRecibidos);
    this->puntos += puntosRecibidos;
}

int Puntaje::obtenerPuntos() {
    return puntos;
}