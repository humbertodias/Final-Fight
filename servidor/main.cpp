//
// Created by sebas on 4/10/19.
//

#include "ConexionServidor.h"
#include "../servicios/Locator.h"
#include "ConexionesClientes.h"
#include "ContenedorHilos.h"
#include "Procesamiento.h"
#include "../eventos/Eventos.h"
#include "Transmision.h"
#include "../eventos/MostrarMenuSeleccion.h"
#include "../eventos/ActualizarYTransmitir.h"
#include "GameLoop.h"
#include "ActualizadorServidor.h"
#include "../usuario/ManagerUsuarios.h"

using namespace std;

int main(int argc, char *argv[]) {
    auto *logger = new Logger();
    Locator::provide(logger);

    auto *config = new Configuracion();
    Locator::provide(config);
    
    /**
     * Conexion al servidor.
     */
    ConexionServidor conexion(5000);
    int socketServidor = conexion.socket();

    /**
     * Crear el mapa.
     */
    Mapa mapa;
    int maximoJugadores = Locator::configuracion()->getIntValue("/usuarios/maximo", 4);

    /**
     * Conexiones de clientes.
     */
    ManagerUsuarios* managerUsuarios = new ManagerUsuarios(maximoJugadores);
    ConexionesClientes conexiones(socketServidor, managerUsuarios, &mapa);
    conexiones.esperarConexiones();
    vector<Socket> socketsClientes = managerUsuarios->getSockets();
    pthread_t hiloConexionesEntrantes = conexiones.abrirHiloConexionesEntrantes();

    /**
     * Procesamiento.
     */
    Procesamiento procesamiento;
    auto *eventosAProcesar = procesamiento.devolverCola();
    pthread_t hiloProcesamiento = procesamiento.procesarEnHilo();

    /**
     * Transmision.
     */
    Transmision transmision(socketsClientes);
    auto *eventosATransmitir = transmision.devolverCola();
    pthread_t hiloTransmision = transmision.transmitirEnHilo();

    /**
     * Game loop.
     */
    auto *actualizar = new ActualizarYTransmitir(&mapa, eventosATransmitir);
    GameLoop gameLoop(eventosAProcesar, actualizar);
    pthread_t hiloGameLoop = gameLoop.loopEnHilo();

    auto *comenzar = new MostrarMenuSeleccion(&mapa);
    eventosAProcesar->push(comenzar);

    /**
     * Contenedor de hilos.
     */
    ActualizadorServidor actualizador(&mapa, eventosAProcesar);
    ContenedorHilos contenedor;
    contenedor.crearHilos(socketsClientes, &actualizador);
    contenedor.esperarFinDeHilos();

    /**
     * Termino el procesamiento.
     */
    auto *finProcesar = new EventoAProcesar("fin");
    eventosAProcesar->push(finProcesar);
    auto *finTransmitir = new EventoATransmitir("fin");
    eventosATransmitir->push(finTransmitir);

    pthread_join(hiloProcesamiento, nullptr);
    pthread_join(hiloTransmision, nullptr);

    return 0;
}