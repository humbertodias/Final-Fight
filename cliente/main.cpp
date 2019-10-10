//
// Created by sebas on 4/10/19.
//

#include <string>
#include "ConexionCliente.h"
#include "../servicios/Locator.h"
#include "../main/Juego.h"
#include "ReceptorCliente.h"
#include "ActualizadorCliente.h"
#include "NivelCliente.h"
#include "EntradaUsuario.h"

using namespace std;

//Client side
int main(int argc, char *argv[]) {
    auto *logger = new Logger();
    Locator::provide(logger);
    auto *config = new Configuracion();
    Locator::provide(config);

    string ipAddress;
    int port;
    bool paramsOk = false;
    string configPath;
    string nivelDebug;

    if (argc < 3) {
        logger->log(ERROR, "No se recibio ip y/o puerto. Se termina la ejecucion");
    } else {
        ipAddress = argv[1];

        try {
            port = stoi(argv[2]);
            paramsOk = true;
        } catch (...) {
            logger->log(ERROR, "Error en puerto recibido. Se termina la ejecucion.");
        }

        if(argc > 3){
            if(argc == 4){
                string param = argv[3];
                size_t found = param.find(".xml");


                if(found==std::string::npos){ //no encontro .xml
                    nivelDebug = param;
                }else{
                    configPath = param;
                }
            }else{
                nivelDebug = argv[3];
                configPath = argv[4];
            }
        }
    }

    if (paramsOk) {
        string user;
        string pass;


        /*cout << "Ingrese nombre de usuario" << endl;
        cin >> user;
        cout << "Ingrese contraseña" << endl;
        cin >> pass;*/

        /**
         * Conexion cliente.
         */
        ConexionCliente conexion(ipAddress, port);
        Socket socket = conexion.socket();
        Locator::provide(socket);

        /**
         * Transmisión de acciones.
         */
        EntradaNula entrada;
        TrasmisionCliente trasmision(socket, &entrada);
        trasmision.transmitirEnHilo();


        /**
         * Iniciar juego.
         */
        Juego juego;
        SDL_Renderer *renderer = juego.renderer();
        Locator::provide(renderer);
        Mapa &mapa = juego.mapa();
        NivelCliente::generarPantallaDeEspera(&mapa);

        juego.loop(&trasmision);
        juego.terminar();

    }


    return 0;

}