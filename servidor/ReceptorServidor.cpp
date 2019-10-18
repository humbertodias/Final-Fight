//
// Created by sebas on 5/10/19.
//

#include "ReceptorServidor.h"
#include "../usuario/Usuario.h"
#include "actualizadores/ActualizadorUsuario.h"
#include "actualizadores/ActualizadorMenuSeleccion.h"
#include "../modelo/Actividad.h"


ReceptorServidor::ReceptorServidor(Mapa *mapa, Socket socket, ListaSockets *listaSockets, ManagerUsuarios *manager, EventosAProcesar *eventos,
                                   SelectorPersonajes *selector, semaphore *confirmacion) :
        mapa(mapa),
        socket(socket),
        manager(manager),
        eventos(eventos),
        selector(selector),
        listaSockets(listaSockets),
        confirmacion(confirmacion) {}

void ReceptorServidor::recibir() {

    ActualizadorUsuario actualizadorUsuario(eventos, manager);
    Locator::logger()->log(DEBUG, "Se crea un actualizador de usuario.");

    Usuario *usuario = actualizadorUsuario.getUsuario(socket);
    listaSockets->agregar(socket);

    if (!usuario->getPersonaje()) {
        ActualizadorMenuSeleccion actualizadorMenu(mapa, eventos, selector, usuario, manager, confirmacion);
        Locator::logger()->log(DEBUG, "Se crea un actualizador de menu de selección.");
        do {
            stringstream ss;
            if (!socket.recibir(ss)) {
                usuario->desconectar();
                Locator::logger()->log(ERROR, "Se termina el hilo.");
                pthread_exit(nullptr);
            }
            actualizadorMenu.interpretarStream(ss);
        } while (!actualizadorMenu.fin());

        confirmacion->wait();
    }
    Entidad *jugador = usuario->getPersonaje();
    eventos->push(new SetActividadJugador(jugador, true));

    ActualizadorJuego actualizadorJuego(mapa, eventos, jugador);
    Locator::logger()->log(DEBUG, "Se crea un actualizador de juego.");
    do {
        stringstream sss;
        if (!socket.recibir(sss)) {
            usuario->desconectar();
            eventos->push(new SetActividadJugador(jugador, false));
            Locator::logger()->log(ERROR, "Se termina el hilo.");
            pthread_exit(nullptr);
        }
        actualizadorJuego.interpretarStream(sss);
    } while (!actualizadorJuego.fin());
}

SetActividadJugador::SetActividadJugador(Entidad *jugador, bool activo) :
        activo(activo),
        jugador(jugador) {}

void SetActividadJugador::resolver() {
    jugador->getEstado<Actividad>("actividad")->activo = activo;
}
