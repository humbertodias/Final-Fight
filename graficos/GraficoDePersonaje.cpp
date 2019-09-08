//
// Created by sebas on 2/9/19.
//

#include "GraficoDePersonaje.h"
#include "../modelo/mapeables/Personaje.h"

GraficosDePersonaje::GraficosDePersonaje(SDL_Renderer* renderer, string rutaSprite) :
        rutaSprite(rutaSprite),
        renderer(renderer) {
            SDL_Surface *sprite = IMG_Load(rutaSprite.c_str());
            SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 0X58, 0xB8, 0xF8));
            texture = SDL_CreateTextureFromSurface(renderer, sprite);
            SDL_FreeSurface( sprite );
}


void GraficosDePersonaje::actualizar(Mapeable &mapeable) {
    auto &personaje = dynamic_cast<Personaje &>(mapeable);

    Posicion &posicion = personaje.posicion(); // Se obtiene la posicion del jugador y en base a eso se construye el hitbox del jugador.
    SDL_Rect posicionJugador = {posicion.getX(), posicion.getY(), 200, 400};

    //Se setea la posicion de la plantilla de sprites (La posicion y dimension que se va a renderizar LA PLANTILLA DE SPRITES, no el hitbox)
    SDL_Rect posicionSprite = {5, 0, 40, 100};

    //Se renderiza en la ventana la imagen, la posicion del sprite, y la posicion del jugador
    SDL_RenderCopy(renderer, texture, &posicionSprite, &posicionJugador);
    SDL_RenderPresent(renderer);
}