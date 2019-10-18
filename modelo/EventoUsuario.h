//
// Created by sebas on 18/10/19.
//

#ifndef FINAL_FIGHT_EVENTOUSUARIO_H
#define FINAL_FIGHT_EVENTOUSUARIO_H


#include "../serializar/Serializable.h"

enum EVENTO_USUARIO {
    CONTRASENIA_INCORRECTA,
    USUARIO_YA_CONECTADO,
    PARTIDA_LLENA,
    CONECTADO // exito al conectarse
};

class EventoUsuario : public Serializable {

private:
    EVENTO_USUARIO evento_;

public:
    EventoUsuario();
    explicit EventoUsuario(EVENTO_USUARIO);
    EVENTO_USUARIO evento();
    void serializar(ostream& stream) override;
    void deserializar(istream& stream) override;
};


#endif //FINAL_FIGHT_EVENTOUSUARIO_H
