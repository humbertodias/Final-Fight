#include "Juego.h"
#include "../servicios/Locator.h"
#include "../graficos/Sprite.h"
#include "../modelo/Posicion.h"
#include "../graficos/FabricaDeAnimacionesDeCody.h"
#include "../graficos/Grafico.h"
#include "../fisica/FisicaDeEscenario.h"
#include "../graficos/GraficoDeEscenario.h"
#include "../estados/Parado.h"
#include "../fisica/FisicaDePersonaje.h"
#include "../modelo/Orientacion.h"
#include "../niveles/Nivel.h"

//DECLARACION CONSTANTES
static const char *const PATH_SPRITE_CAJA = "assets/escenarios/caja.png";
static const char *const PATH_SPRITE_CUCHILLO = "assets/objetos/cuchillo.png";

static const char *const PATH_XML_CANTIDAD_CAJA = "/escenario/objetos/caja/cantidad";
static const char *const PATH_XML_CANTIDAD_CUCHILLO = "/escenario/objetos/cuchillo/cantidad";

void configApplication(int argc, char*args[]){
    bool defaultLogger = argc == 1;
    bool defaultConfiguration = argc == 1;

    if (argc == 2){
        string param = args[1];
        size_t found = param.find(".xml");

        defaultConfiguration = found==std::string::npos;
        defaultLogger = found!=std::string::npos;
    }

    Configuracion *config =
            defaultConfiguration ?
            new Configuracion() :
            (argc == 2 ?
             new Configuracion(args[1]) :
             new Configuracion(args[2]));

    Locator::provide(config);

    string loggerLevel = config->getValue("/debug/level");
    defaultLogger = defaultLogger && loggerLevel.compare("") == 0;

    Logger* logger =
            defaultLogger ?
            new Logger() :
            (argc == 2 ?
             new Logger(args[1]) :
             new Logger(loggerLevel));
    Locator::provide(logger);

    logger = NULL;
    config = NULL;

    delete logger;
    delete config;
}

int main(int argc, char *args[]) {
    /**
     * Iniciar.
     */
    configApplication(argc, args);

    Juego juego;
    SDL_Renderer *renderer = juego.renderer();
    Locator::provide(renderer);

    Mapa &mapa = juego.mapa();

    Entidad *jugador = Nivel::generarJugador(&mapa);

    Nivel::generarNivel("nivel2", &mapa, jugador);

    juego.loop();

    Locator::clean();
}