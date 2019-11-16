//
// Created by leo on 15/11/19.
//

#include "NotificadorDeGolpes.h"
#include "serializables/Puntaje.h"
#include "serializables/EstadoDePersonaje.h"
#include "serializables/Arma.h"
#include "serializables/Energia.h"

NotificadorDeGolpes::NotificadorDeGolpes(Entidad *entidad) : Comportamiento(entidad) {}

void NotificadorDeGolpes::notificarGolpeAPersonaje(Entidad* personajeGolpeado){
    auto estadoGolpeador = this->entidad->getEstado<EstadoDePersonaje>("estado de personaje");
    auto puntajeGolpeador = this->entidad->getEstado<Puntaje>("puntaje");
    auto arma = this->entidad->getEstado<Arma>("arma");

    int puntosParaJugador = estadoGolpeador->getEstado() == PATEANDO ? 400 : arma->getPuntosParaPersonaje();
    puntajeGolpeador->agregarPuntos(puntosParaJugador);

    if(!personajeGolpeado->getEstado<Energia>("energia")->personajeVive()){
        puntajeGolpeador->agregarPuntos(500);
    }

    arma->usar();
    if (!arma->tieneUsosRestantes()){
        this->entidad->cambiarEstado("arma", new Arma(ARMA::PUNIOS));
    }
}