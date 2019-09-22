//
// Created by sebas on 14/9/19.
//

#include "FabricaDeAnimacionesDeAxl.h"

Animacion* FabricaDeAnimacionesDeAxl::caminado() {
    vector<SDL_Rect> posiciones = {
            //{5, 5, 60, 95},
            {60, 0, 60, 105},
            {120, 0, 60, 105},
    };

    vector<float> duraciones = {1, 1, 1, 1, 1, 1};

    return new Animacion(posiciones, duraciones, 60, 4.5);
}

Animacion* FabricaDeAnimacionesDeAxl::saltando() {
    vector<SDL_Rect> posiciones = {{5, 5, 60, 95}};

    vector<float> duraciones = {1, 1, 1, 1};

    return new Animacion(posiciones, duraciones, 60, 4.5);
}

Animacion* FabricaDeAnimacionesDeAxl::parado() {
    vector<SDL_Rect> posiciones = {{5, 5, 60, 95}};
    vector<float> duraciones = {1};

    return new Animacion(posiciones, duraciones, 60, 4.5);
}

Animacion *FabricaDeAnimacionesDeAxl::agachado() {
    vector<SDL_Rect> posiciones = {{5, 5, 60, 95}};

    vector<float> duraciones = {1};

    return new Animacion(posiciones, duraciones, 60, 4.5);
}

Animacion* FabricaDeAnimacionesDeAxl::golpear() {
    vector<SDL_Rect> posiciones = {
            {45, 105, 60, 104},
            {105, 105, 75, 104},
            {180, 105, 40, 104},
            {220, 105, 75, 104},
    };

    vector<float> duraciones = {1, 1, 1, 1, 1, 1};

    return new Animacion(posiciones, duraciones, 60, 4.5);
}