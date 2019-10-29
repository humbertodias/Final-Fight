//
// Created by sebas on 6/10/19.
//

#include <random>
#include "NivelServidor.h"
#include "../modelo/Nivel.h"
#include "../estados/Reposando.h"
#include "../fisica/FisicaDePersonaje.h"
#include "../fisica/FisicaDeEscenario.h"
#include "../modelo/Opacidad.h"
#include "../modelo/EstadoDePersonaje.h"
#include "../fisica/FisicaDeTransicion.h"
#include "../graficos/animaciones/FabricaDeAnimacionesDePoison.h"
#include "../estados/ia/Patrullar.h"
#include "../estados/Caminando.h"
#include "../modelo/TipoElemento.h"
#include "../modelo/Actividad.h"
#include "../modelo/NumeroJugador.h"
#include "FabricaDeAnimacionesServidor.h"
#include "../modelo/IndiceSprite.h"
#include "../modelo/Energia.h"

void NivelServidor::generarMenuSeleccion(Mapa *mapa) {
    Locator::logger()->log(INFO, "Se genera el menu de seleccion.");

    Entidad *pantalla = mapa->crearEntidad();
    auto *posicion = new Posicion(0, 10, 0);
    auto *tipo = new Tipo(PANTALLA_SELECCION);
    pantalla->agregarEstado("posicion", posicion);
    pantalla->agregarEstado("mapa", mapa);
    pantalla->agregarEstado("tipo", tipo);
}


Entidad *NivelServidor::generarJugador(Mapa *mapa, enum PERSONAJE personajeSeleccionado, int contadorJugador) {
    Locator::logger()->log(INFO, "Se genera jugador.");

    auto *estado = new Reposando();
    auto *velocidad = new Velocidad();
    auto *orientacion = new Orientacion;
    auto *tipo = new Tipo(JUGADOR);
    auto *jugador = mapa->crearJugador();
    auto *indiceSprite = new IndiceSprite;
    auto *fisica = new FisicaDePersonaje();
    auto *actividad = new Actividad(true);
    auto *posicion = new Posicion(200, 100, 0);
    auto *numeroJugador = new NumeroJugador(contadorJugador);
    auto *estadoDePersonaje = new EstadoDePersonaje(REPOSANDO);
    auto *animacionServidor = FabricaDeAnimacionesServidor::getAnimacion(personajeSeleccionado, "reposando");
    auto *energia = new Energia(100,3);

    jugador->agregarEstado("tipo", tipo);
    jugador->agregarEstado("posicion", posicion);
    jugador->agregarEstado("velocidad", velocidad);
    jugador->agregarEstado("actividad", actividad);
    jugador->agregarEstado("orientacion", orientacion);
    jugador->agregarEstado("indice sprite", indiceSprite);
    jugador->agregarEstado("numeroJugador", numeroJugador);
    jugador->agregarEstado("estado de personaje", estadoDePersonaje);
    jugador->agregarEstado("personaje", new Personaje(personajeSeleccionado));
    jugador->agregarEstado("energia", energia);
    jugador->agregarComportamiento("estado", estado);
    jugador->agregarComportamiento("fisica", fisica);
    jugador->agregarComportamiento("animacion servidor", animacionServidor);
    return jugador;
}

void NivelServidor::generarNivel(const string &nivel, Mapa *mapa) {
    mapa->vaciarMapa();
    Locator::logger()->log(DEBUG, "Se genera " + nivel);

    Entidad *escenario = generarEscenario(nivel, mapa);

    /**
     * Dependencias.
     */
    Jugadores *jugadores = mapa->getJugadores();
    jugadores->reiniciarPosiciones(200, 100);

    auto *posicionDeEscenario = escenario->getEstado<Posicion>("posicion");

    generarElementos(nivel, mapa, posicionDeEscenario, CAJA);
    generarElementos(nivel, mapa, posicionDeEscenario, CUCHILLO);
    generarElementos(nivel, mapa, posicionDeEscenario, TUBO);
    generarElementos(nivel, mapa, posicionDeEscenario, NEUMATICO);
    generarEnemigo(nivel, mapa, posicionDeEscenario);
    generarTransicion(nivel, mapa, jugadores);
}

Entidad *NivelServidor::generarEscenario(const string &nivel, Mapa *mapa) {
    Locator::logger()->log(DEBUG, "Se genera escenario para " + nivel);

    Configuracion *config = Locator::configuracion();
    int profundidad = config->getIntValue("/niveles/" + nivel + "/escenario/profundidad");
    int anchoNivel = config->getIntValue("/niveles/" + nivel + "/escenario/ancho");

    Locator::logger()->log(DEBUG, "Se cargo profundidad para escenario: " + to_string(profundidad));
    Locator::logger()->log(DEBUG, "Se cargo ancho para escenario: " + to_string(anchoNivel));

    Entidad *escenario = mapa->crearEntidad();
    auto *posicion = new Posicion(0, profundidad, 0);
    auto *tipo = new Tipo(ESCENARIO);
    auto *nivelEstado = new Nivel(nivel);
    auto *fisica = new FisicaDeEscenario(anchoNivel);


    escenario->agregarComportamiento("fisica", fisica);
    escenario->agregarEstado("posicion", posicion);
    escenario->agregarEstado("mapa", mapa);
    escenario->agregarEstado("tipo", tipo);
    escenario->agregarEstado("nivel", nivelEstado);

    return escenario;

}

void NivelServidor::generarTransicion(const string &nivel, Mapa *mapa, Jugadores *posicionDeJugadores) {

    Entidad *transicion = mapa->crearEntidad();
    auto *tipo = new Tipo(TRANSICION);
    int anchoDeNivel = Locator::configuracion()->getIntValue("/niveles/" + nivel + "/escenario/ancho");
    auto *posicion = new Posicion(0, 1, 0);
    auto *opacidad = new Opacidad();
    auto *fisicaDeTransicion = new FisicaDeTransicion(anchoDeNivel);

    transicion->agregarEstado("posicion", posicion);
    transicion->agregarEstado("tipo", tipo);
    transicion->agregarEstado("opacidad", opacidad);
    transicion->agregarEstado("posicion de jugadoresMax", posicionDeJugadores);
    transicion->agregarComportamiento("fisica de transicion", fisicaDeTransicion);
}

int generarPosicionX(int frontera) {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(400, frontera - 400);
    return dist(mt);
}

int generarPosicionY(int frontera) {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(20, frontera - 20);
    return dist(mt);
}

void NivelServidor::generarEnemigo(const string &nivel, Mapa *mapa, Posicion *posicionDeEscenario) {

    Configuracion *config = Locator::configuracion();
    int cantidad = config->getIntValue("/niveles/" + nivel + "/escenario/enemigos/cantidad");
    int anchoNivel = config->getIntValue("/niveles/" + nivel + "/escenario/ancho");
    int profundidadNivel = config->getIntValue("/niveles/" + nivel + "/escenario/profundidad");
    string spritePath = config->getValue("/niveles/" + nivel + "/escenario/enemigos/sprite/src");
    auto *personaje = new Personaje(POISSON);

    for (int i = 0; i < cantidad; i++) {
        Locator::logger()->log(INFO, "Se genera enemigo");

        Entidad *enemigo = mapa->crearEntidad();

        auto *tipo = new Tipo(ENEMIGO);
        auto *comportamiento = new Patrullar();
        auto *velocidadDeEnemigo = new Velocidad();
        auto *orientacionDeEnemigo = new Orientacion;
        auto *fisicaDeEnemigo = new FisicaDePersonaje();
        EstadoDePersonajeServidor *estado = new Caminando();
        auto *estadoDePersonaje = new EstadoDePersonaje(CAMINANDO);
        auto *posicionEnemigoRandom = new Posicion(generarPosicionX(anchoNivel), generarPosicionY(profundidadNivel), 0);
        auto *indiceSprite = new IndiceSprite;
        auto *animacionServidor = FabricaDeAnimacionesServidor::getAnimacion(POISSON, "caminando");

        enemigo->agregarEstado("tipo", tipo);
        enemigo->agregarEstado("personaje", personaje);
        enemigo->agregarEstado("indice sprite", indiceSprite);
        enemigo->agregarEstado("velocidad", velocidadDeEnemigo);
        enemigo->agregarEstado("posicion", posicionEnemigoRandom);
        enemigo->agregarEstado("orientacion", orientacionDeEnemigo);
        enemigo->agregarEstado("estado de personaje", estadoDePersonaje);
        enemigo->agregarEstado("posicion de escenario", posicionDeEscenario);
        enemigo->agregarComportamiento("estado", estado);
        enemigo->agregarComportamiento("fisica", fisicaDeEnemigo);
        enemigo->agregarComportamiento("comportamiento", comportamiento);
        enemigo->agregarComportamiento("animacion servidor", animacionServidor);
    }
}

void NivelServidor::generarElementos(const string &nivel, Mapa *mapa, Posicion *posicionDeEscenario, elementos ART) {
    Configuracion *config = Locator::configuracion();
    int cantidad;
    switch (ART) {
        case CAJA:
            cantidad = config->getIntValue("/niveles/" + nivel + "/escenario/objetos/caja/cantidad");
            break;
        case CUCHILLO:
            cantidad = config->getIntValue("/niveles/" + nivel + "/escenario/objetos/cuchillo/cantidad");
            break;
        case NEUMATICO:
            cantidad = config->getIntValue("/niveles/" + nivel + "/escenario/objetos/neumatico/cantidad");
            break;
        case TUBO:
            cantidad = config->getIntValue("/niveles/" + nivel + "/escenario/objetos/tubo/cantidad");
            break;
        default:
            cantidad = 0;
    }
    int anchoNivel = config->getIntValue("/niveles/" + nivel + "/escenario/ancho");
    int profundidadNivel = config->getIntValue("/niveles/" + nivel + "/escenario/profundidad");

    auto *tipo = new Tipo(ELEMENTO);
    auto *tipoElemento = new TipoElemento(ART);

    for (int i = 1; i <= cantidad; i++) {
        Locator::logger()->log(INFO, "Se inicia la construccion del elemento random :" + to_string(i));
        auto *indiceSprite = new IndiceSprite;
        auto elementoRandom = mapa->crearEntidad();
        auto *posicionElementoRandom = new Posicion(generarPosicionX(anchoNivel), generarPosicionY(profundidadNivel),
                                                    0);

        elementoRandom->agregarEstado("posicion", posicionElementoRandom);
        elementoRandom->agregarEstado("tipo", tipo);
        elementoRandom->agregarEstado("indice sprite", indiceSprite);
        elementoRandom->agregarEstado("tipo elemento", tipoElemento);
        elementoRandom->agregarEstado("posicion de escenario", posicionDeEscenario);
    }

}
