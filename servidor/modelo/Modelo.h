//
// Created by sebas on 5/11/19.
//

#ifndef FINAL_FIGHT_MODELO_H
#define FINAL_FIGHT_MODELO_H


#include "../../modelo/serializables/Serializable.h"

typedef string IdEtapa;

class Modelo : public Serializable {

private:
    IdEtapa id;

public:
    void setId(IdEtapa id);
    void serializar(ostream& stream) override;
    void deserializar(istream& stream) override;

};


#endif //FINAL_FIGHT_MODELO_H
