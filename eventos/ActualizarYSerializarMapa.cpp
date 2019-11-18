//
// Created by sebas on 7/10/19.
//

#include <iostream>
#include "ActualizarYSerializarMapa.h"
#include "../servicios/Locator.h"

ActualizarYSerializarMapa::ActualizarYSerializarMapa(Mapa *mapa) :
        mapa(mapa) {}

void ActualizarYSerializarMapa::resolver() {
    if (Locator::clientes()->getEtapaActual() != "game over") {
        actualizar();
        serializar();
    }
}

void ActualizarYSerializarMapa::actualizar() {
    for (auto entidad : mapa->devolverEntidades()) {
        auto comportamientos = entidad->getComportamientos();
        for (auto *comportamiento : comportamientos) {
            comportamiento->actualizar();
        }
    }
    auto *colisionables = Locator::colisionables();
    colisionables->calcularInteracciones();
    if (!Locator::mapa()->getJugadores()->vivos()) Locator::clientes()->cambiarTodosA("game over");
}

void ActualizarYSerializarMapa::serializar() {
    stringstream s;
    for (auto tupla : mapa->devolverEntidadesConId()) {
        Entidad::putIdInStream(s, tupla.first);
        tupla.second->serializar(s);
    }
    mapa->guardarSerializado(s);
}