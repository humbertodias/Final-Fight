//
// Created by sebas on 13/9/19.
//

#ifndef FINAL_FIGHT_ANIMACION_H
#define FINAL_FIGHT_ANIMACION_H


#include <SDL_rect.h>
#include <vector>
#include "../modelo/mapeables/Entidad.h"

using namespace std;

class Animacion : public Estado {

private:
    vector<SDL_Rect> posiciones;
    vector<float> duracionesPorSprite;
    int duracionTotal;
    float escala_;

    int framesFaltantes;
    int spriteActual;
    float sumaDeDuracionesRelativas;

    int calcularFramesFaltantes();

public:
    Animacion(vector<SDL_Rect> posiciones, vector<float> duracionesPorSprite, int duracionTotal, float escala = 1);
    SDL_Rect actualizarYDevolverPosicion();
    float escala();

    void setPosicionesInicial( vector<SDL_Rect> posicionesInicial) { posiciones = posicionesInicial; }
    bool compareTo(Animacion *animacionAcomparar);
};


#endif //FINAL_FIGHT_ANIMACION_H
