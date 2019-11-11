//
// Created by sebas on 21/10/19.
//

#include "GraficoJugador.h"
#include "Grafico.h"
#include "AnimacionCliente.h"
#include "Sprite.h"
#include "../modelo/serializables/Posicion.h"
#include "../servicios/Locator.h"

GraficoJugador::GraficoJugador(Entidad *entidad) : Grafico(entidad) {}

void GraficoJugador::actualizar() {
    Grafico::actualizar();
    SDL_Renderer *renderer = Locator::renderer();
    int posicionDeEscenarioX = Locator::posicionEscenario()->x;
    auto *posicion = entidad->getEstado<Posicion>("posicion");
    auto *spriteIndicador = entidad->getEstado<Sprite>("spriteIndicador");

    auto *animacion = entidad->getEstado<AnimacionCliente>("animacion");

    Posicion nuevaPosicion(posicion->getX() - posicionDeEscenarioX, posicion->getY(), posicion->getZ());
    SDL_Rect posicionEnSprite = animacion->devolverPosicion(entidad);
    SDL_Rect posicionEnPantalla = calcularPosicionEnPantalla(nuevaPosicion, posicionEnSprite, animacion->escala());

    SDL_Rect posicionEnSpriteIndicador = {0, 0, 45, 45};
    Posicion nuevaPosicionIndicador(posicion->getX() - posicionDeEscenarioX, posicion->getY(), posicion->getZ() + posicionEnPantalla.h);
    SDL_Rect posicionEnPantallaIndicador = calcularPosicionEnPantalla(nuevaPosicionIndicador, posicionEnSpriteIndicador,
                                                                      1.5);

    SDL_RenderCopy(renderer, spriteIndicador->getTexture(), &posicionEnSpriteIndicador, &posicionEnPantallaIndicador);
}
