#include "Juego.h"
#include "../servicios/Locator.h"
#include "../graficos/Sprite.h"
#include "../modelo/Posicion.h"
#include "../graficos/animaciones/FabricaDeAnimacionesDeCody.h"
#include "../niveles/Nivel.h"
#include "../tipos/tipos.h"

void configApplication(int argc, const char*args[]){
    bool defaultLogger = argc == 1;
    bool defaultConfiguration = argc == 1;
    bool paramIsLoggerLevel = false;

    if (argc == 2){
        string param = args[1];
        size_t found = param.find(".xml");

        defaultConfiguration = found==std::string::npos;
        defaultLogger = found!=std::string::npos;
        paramIsLoggerLevel = !defaultLogger;
    }

    Configuracion *config =
            defaultConfiguration ?
            new Configuracion() :
            (argc == 2 ?
             new Configuracion(args[1]) :
             new Configuracion(args[2]));

    Locator::provide(config);

    string loggerLevel = config->getValue("/debug/level");
    defaultLogger = defaultLogger && loggerLevel.empty();

    Logger* logger =
            defaultLogger ?
            new Logger() :
            (argc > 2 || paramIsLoggerLevel ?
             new Logger(args[1]) :
             new Logger(loggerLevel));
    Locator::provide(logger);

    Locator::logger()->log(DEBUG, "Se inicio logger modo DEBUG");

    string configPath = config->getActualPath();

    Locator::logger()->log(DEBUG, "Archivo de configuracion abierto: " + configPath);

    logger = nullptr;
    config = nullptr;

    delete logger;
    delete config;
}

int main(int argc, const char **args) {
    /**
     * Iniciar.
     */

    if (argc == 1){
        const char *args2[] = {"", "DEBUG", "Configuracion.xml"};
        configApplication(3, args2);
    }else{
        configApplication(argc, args);
    }

    Juego juego;
    SDL_Renderer *renderer = juego.renderer();
    Locator::provide(renderer);

    Mapa &mapa = juego.mapa();

    nombreJugador nombreJugador = juego.menuPrincipal();

    Entidad *jugador = Nivel::generarJugador(&mapa, nombreJugador); //Es propio de nivel?

    Nivel::generarNivel("nivel1", &mapa, jugador);

    juego.loop();

    Locator::clean();
}