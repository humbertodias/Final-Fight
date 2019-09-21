//
// Created by sebas on 14/9/19.
//

#ifndef FINAL_FIGHT_FABRICADEANIMACIONESDECODY_H
#define FINAL_FIGHT_FABRICADEANIMACIONESDECODY_H


#include "Animacion.h"

class FabricaDeAnimacionesDeCody {

public:
    static Animacion* caminando();
    static Animacion* saltando();
    static Animacion* parado();
    static Animacion* golpear();
    static Animacion* agachado();

};


#endif //FINAL_FIGHT_FABRICADEANIMACIONESDECODY_H
