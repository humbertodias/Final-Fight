//
// Created by franco on 3/11/19.
//

#ifndef FINAL_FIGHT_RECIBIENDOGOLPE_H
#define FINAL_FIGHT_RECIBIENDOGOLPE_H


#include "EstadoDePersonajeServidor.h"

class RecibiendoGolpe : public EstadoDePersonajeServidor{

private:
    int duracion = 20;
    int faltante = duracion;

public:
    using EstadoDePersonajeServidor::EstadoDePersonajeServidor;

    void actualizar() override;
    void darGolpe() override {};
    void saltar() override {};
    void caminar(bool X_pos, bool X_neg, bool Y_pos, bool Y_neg) override {};
    void reposar() override {};
    void agachar() override {};
    void recibirGolpe() override {};
};


#endif //FINAL_FIGHT_RECIBIENDOGOLPE_H
