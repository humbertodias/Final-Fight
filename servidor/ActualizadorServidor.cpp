//
// Created by sebas on 8/10/19.
//

#include "ActualizadorServidor.h"
#include "NivelServidor.h"
#include "../modelo/Accion.h"
#include "../eventos/ConfirmarSeleccion.h"
#include "../eventos/EventoPersonaje.h"

ActualizadorServidor::ActualizadorServidor(Mapa *mapa, EventosAProcesar *eventos) :
        mapa(mapa),
        eventos(eventos) {}

void ActualizadorServidor::interpretarComando(stringstream &s) {

    Accion accion;
    Entidad *jugador = mapa->getJugador();
    while (s.rdbuf()->in_avail() != 0) {
        accion.deserializar(s);

        EventoAProcesar *evento;
        switch (accion.accion()) {

            case SELECCIONAR_SIGUIENTE:
                break;
            case SELECCIONAR_ANTERIOR:
                break;
            case GOLPEAR:
                evento = new Golpear(jugador);
                eventos->push(evento);
                break;
            case SALTAR:
                evento = new Saltar(jugador);
                eventos->push(evento);
                break;
            case REPOSAR:
                evento = new Reposar(jugador);
                eventos->push(evento);
                break;
            case AGACHAR:
                evento = new Agachar(jugador);
                eventos->push(evento);
                break;
            case CAM_IZQUIERDA:
                evento = new CaminarIzquierda(jugador);
                eventos->push(evento);
                break;
            case CAM_DERECHA:
                evento = new CaminarDerecha(jugador);
                eventos->push(evento);
                break;
            case CAM_ARRIBA:
                evento = new CaminarArriba(jugador);
                eventos->push(evento);
                break;
            case CAM_ABAJO:
                evento = new CaminarAbajo(jugador);
                eventos->push(evento);
                break;
            case CAM_IZQUIERDA_ARRIBA:
                evento = new CaminarIzquierdaArriba(jugador);
                eventos->push(evento);
                break;
            case CAM_IZQUIERDA_ABAJO:
                evento = new CaminarIzquierdaAbajo(jugador);
                eventos->push(evento);
                break;
            case CAM_DERECHA_ARRIBA:
                evento = new CaminarDerechaArriba(jugador);
                eventos->push(evento);
                break;
            case CAM_DERECHA_ABAJO:
                evento = new CaminarDerechaAbajo(jugador);
                eventos->push(evento);
                break;
            case SELECCIONAR_CODY:
                evento = new ConfirmarSeleccion(mapa, CODY);
                eventos->push(evento);
                break;
            case SELECCIONAR_HAGGAR:
                evento = new ConfirmarSeleccion(mapa, HAGGAR);
                eventos->push(evento);
                break;
            case SELECCIONAR_GUY:
                evento = new ConfirmarSeleccion(mapa, GUY);
                eventos->push(evento);
                break;
            case SELECCIONAR_MAKI:
                evento = new ConfirmarSeleccion(mapa, MAKI);
                eventos->push(evento);
                break;
        }
    }
}
