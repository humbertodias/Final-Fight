//
// Created by poncio on 23/9/19.
//

#ifndef FINAL_FIGHT_REPRODUCTOREFECTOSDENIVEL_H
#define FINAL_FIGHT_REPRODUCTOREFECTOSDENIVEL_H

#include "../modelo/Entidad.h"

class ReproductorEfectosDeNivel : public Comportamiento{

public:
    void actualizar(Entidad *) override ;
};

#endif //FINAL_FIGHT_REPRODUCTOREFECTOSDENIVEL_H
