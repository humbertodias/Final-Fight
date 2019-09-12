//
// Created by sebas on 12/9/19.
//

#include "GraficoDePersonajeCaminando.h"
#include "../modelo/mapeables/Personaje.h"
#include "../servicios/Locator.h"
#include <cmath>

GraficoDePersonajeCaminando::GraficoDePersonajeCaminando(SDL_Renderer *renderer, SDL_Texture *texturaSprite) :
        renderer(renderer),
        texture(texturaSprite),
        spriteActual(0),
        cantidadDeSprites(6),
        coordenadasSprites{
                {12, 100, 30, 90},
        } {}

void GraficoDePersonajeCaminando::actualizar(Mapeable &mapeable) {
    auto &personaje = dynamic_cast<Personaje &>(mapeable);

    Configuracion *config = Locator::configuracion();
    Posicion &posicion = personaje.posicion(); // Se obtiene la posicion del jugador y en base a eso se construye el hitbox del jugador.

    const int screenX = posicion.getX() + posicion.getY() * cos(config->inclinacionDeEscenario);
    const int screenY = config->alturaDePantalla
                        + posicion.getZ()
                        - posicion.getY() * cos(M_PI / 2 - config->inclinacionDeEscenario)
                        - coordenadasSprites[spriteActual].h * config->escalaDeGraficos;

    SDL_Rect posicionJugador = {screenX,
                                screenY,
                                int(coordenadasSprites[spriteActual].w * config->escalaDeGraficos),
                                int(coordenadasSprites[spriteActual].h * config->escalaDeGraficos)};

    //Se renderiza en la ventana la imagen, la posicion del sprite, y la posicion del jugador
    SDL_RenderCopy(renderer, texture, &coordenadasSprites[spriteActual], &posicionJugador);
}
