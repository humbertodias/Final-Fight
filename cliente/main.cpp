//
// Created by sebas on 4/10/19.
//

#include <string>
#include "ConexionCliente.h"
#include "../servicios/Locator.h"
#include "../main/Juego.h"
#include "Escucha.h"
#include "ActualizadorCliente.h"
#include "NivelCliente.h"
#include "EntradaUsuario.h"

using namespace std;

//Client side
int main(int argc, char *argv[]) {
    auto *logger = new Logger();
    Locator::provide(logger);
    auto* config = new Configuracion();
    Locator::provide(config);

    /**
     * Conexion cliente.
     */
    ConexionCliente conexion("localhost", 5000);
    int socket = conexion.socket();
    Locator::provide(socket);

    /**
     * Transmisión de acciones.
     */
     EntradaNula entrada;
     TrasmisionCliente trasmision(socket, &entrada);

    /**
     * Iniciar juego.
     */
    Juego juego;
    SDL_Renderer *renderer = juego.renderer();
    Locator::provide(renderer);
    Mapa &mapa = juego.mapa();
    NivelCliente::generarPantallaDeEspera(&mapa);

    juego.loop();
    juego.terminar();

//    /**
//     * Actualizador.
//     */
//     ActualizadorCliente actualizador(&mapa);
//
//    /**
//     * Escuchar al servidor.
//     */
//    Escucha escucha(socket, &actualizador);
//    escucha.escucharEnHilo();

    return 0;
}