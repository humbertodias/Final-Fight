//
// Created by sebas on 10/9/19.
//

#include "FisicaDeEscenario.h"
#include "../servicios/Locator.h"
#include "../modelo/Mapa.h"
#include "../servidor/NivelServidor.h"

FisicaDeEscenario::FisicaDeEscenario(int largo) :
        largo(largo) {
    Configuracion *config = Locator::configuracion();
    scrollIzquierdo = config->getIntValue("/scroll/izquierdo");
    scrollDerecho = config->getIntValue("/scroll/derecho");
}

void FisicaDeEscenario::actualizar(Entidad *entidad) {
    int ancho = Locator::configuracion()->getIntValue("/resolucion/ancho");
    auto *posicionEscenario = entidad->getEstado<Posicion>("posicion");
    int xPersonaje = entidad->getEstado<Posicion>("posicion de jugador")->getX();

    int xEscenario = posicionEscenario->getX();
    if ((xPersonaje - xEscenario < scrollIzquierdo) && (xPersonaje - scrollIzquierdo) > 0)
        posicionEscenario->setX(xPersonaje - scrollIzquierdo);
    if ((xPersonaje - xEscenario > ancho - scrollDerecho) && (largo - xPersonaje) > scrollDerecho)
        posicionEscenario->setX(xPersonaje + scrollDerecho - ancho);

    if (xPersonaje > largo) {
        Locator::logger()->log(INFO, "Se llego al final del nivel.");
        auto *mapa = entidad->getEstado<Mapa>("mapa");
        mapa->vaciarMapa();
        NivelServidor::generarNivel("nivel2", mapa);
    }
}