//
// Created by sebas on 10/9/19.
//

#include "FisicaDeEscenario.h"
#include "../modelo/mapeables/Escenario.h"

void FisicaDeEscenario::actualizar(Mapa &mapa, Mapeable &mapeable) {
    auto &escenario = dynamic_cast<Escenario &>(mapeable);
    // TODO: actuaizar la posicion del escenario cuando avance el personaje (puede que no sea necesario).
}
