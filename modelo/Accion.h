//
// Created by sebas on 8/10/19.
//

#ifndef FINAL_FIGHT_ACCION_H
#define FINAL_FIGHT_ACCION_H

#include "../serializar/Serializable.h"

enum ACCION {
    CONFIRMAR,
    GOLPEAR,
    SALTAR,
    REPOSAR,
    AGACHAR,
    CAM_IZQUIERDA,
    CAM_DERECHA,
    CAM_ARRIBA,
    CAM_ABAJO,
    CAM_IZQUIERDA_ARRIBA,
    CAM_IZQUIERDA_ABAJO,
    CAM_DERECHA_ARRIBA,
    CAM_DERECHA_ABAJO,
    SELECCIONAR_CODY,
    SELECCIONAR_HAGGAR,
    SELECCIONAR_GUY,
    SELECCIONAR_MAKI,
    ENVIAR_USUARIO,
    FIN
};

class Accion : public Serializable {

private:
    ACCION accion_;

public:
    Accion();
    explicit Accion(ACCION accion);
    ACCION accion();
    void serializar(ostream &stream) override;
    void deserializar(istream &stream) override;

};


#endif //FINAL_FIGHT_ACCION_H
