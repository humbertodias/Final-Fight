//
// Created by sebas on 30/8/19.
//

#ifndef FINAL_FIGHT_POSICION_H
#define FINAL_FIGHT_POSICION_H


#include "Velocidad.h"
#include "Entidad.h"

class Posicion : public Estado, public Serializador {

private:

public:
    explicit Posicion(int x = 0, int y = 0, int z = 0);
    Posicion operator-(Posicion otraPosicion);
    void mover(Velocidad& velocidad);
    int x, y, z;
    int getX();
    int getY();
    int getZ();
    void setX(int x);

    void serializar(ostream& stream) override;
    void deserializar(istream& stream) override;
};


#endif //FINAL_FIGHT_POSICION_H
