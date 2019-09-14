//
// Created by franco on 6/9/19.
//
#include <SDL_system.h>
#include "Parado.h"
#include "Agachado.h"
#include "Caminando.h"

EstadoDePersonaje* Parado::manejarEntrada(Personaje &personaje, const Uint8* entrada) {

    Velocidad &velocidad = personaje.velocidad();

    // TODO: Refactorizar
    if (entrada[SDL_SCANCODE_S]) { // Tecla S -> El personaje Salta
        Saltando* saltando = new Saltando();
        saltando->manejarEntrada(personaje, entrada);
        return saltando;
    }else if (entrada[SDL_SCANCODE_D]){
        Agachado* agachado = new Agachado();
        agachado -> manejarEntrada(personaje, entrada);
        return agachado;
    }else if (entrada[SDL_SCANCODE_RIGHT] || entrada[SDL_SCANCODE_LEFT] || entrada[SDL_SCANCODE_DOWN] || entrada[SDL_SCANCODE_UP]){
        Caminando* caminando = new Caminando();
        caminando -> manejarEntrada(personaje, entrada);
        return caminando;
    }else {return nullptr; }
}

void Parado::actualizar(Personaje &personaje) {
}

void Parado::enter(){
}
