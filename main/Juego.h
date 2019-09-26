//
// Created by sebas on 1/9/19.
//

#ifndef FINAL_FIGHT_JUEGO_H
#define FINAL_FIGHT_JUEGO_H

#include "../modelo/Mapa.h"
#include <SDL2/SDL.h>

class Juego {

private:

    void inicializarGraficos();
    void inicializarElementos();

    void processInput();
    void actualizar();
    void graficar();
    void clearScene();

    SDL_Renderer *renderer_ = nullptr;
    SDL_Window *window = nullptr;
    bool exit = false;
    Mapa mapa_;

public:
    Juego();

    void loop();
    Mapa &mapa();
    SDL_Renderer* renderer();
    void terminar();

};


#endif //FINAL_FIGHT_JUEGO_H
