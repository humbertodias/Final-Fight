//
// Created by sebas on 8/10/19.
//

#ifndef FINAL_FIGHT_ACTUALIZADORJUEGO_H
#define FINAL_FIGHT_ACTUALIZADORJUEGO_H


#include "../../modelo/Mapa.h"
#include "../../eventos/Eventos.h"
#include "../../usuario/Usuario.h"
#include "../../usuario/ManagerUsuarios.h"

class ActualizadorJuego {

private:
    Mapa *mapa;
    EventosAProcesar *eventos;
    Entidad *jugador;
    ManagerUsuarios* managerUsuarios;
    Usuario* usuario;

public:
    explicit ActualizadorJuego(Mapa *mapa, EventosAProcesar *eventos, Entidad *jugador, ManagerUsuarios* managerUsuarios, Usuario* usuario);
    void interpretarStream(stringstream &s);
    void actualizarJuego(Usuario *pUsuario);

};


class SetActividadJugador : public EventoAProcesar {

private:
    Entidad *jugador;
    bool activo;

public:
    explicit SetActividadJugador(Entidad *jugador, bool activo);
    void resolver() override;

};

#endif //FINAL_FIGHT_ACTUALIZADORJUEGO_H
