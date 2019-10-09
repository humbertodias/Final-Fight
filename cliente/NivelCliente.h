//
// Created by sebas on 8/10/19.
//

#ifndef FINAL_FIGHT_NIVELCLIENTE_H
#define FINAL_FIGHT_NIVELCLIENTE_H


#include "../modelo/Mapa.h"

class NivelCliente {

public:
    static void generarPantallaDeEspera(Mapa *mapa);
    static void generarMenuSeleccion(Mapa *mapa, Entidad *pantalla);

    static void generarJugador(Mapa *mapa, IdEntidad idEntidad, Entidad *jugador);

    static void generarSelectorDePersonaje(Mapa *mapa, Entidad *entidad);

    static void generarEscenario(Mapa *mapa, Entidad *entidad);
};


#endif //FINAL_FIGHT_NIVELCLIENTE_H
