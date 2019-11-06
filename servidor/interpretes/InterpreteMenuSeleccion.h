//
// Created by sebas on 5/11/19.
//

#ifndef FINAL_FIGHT_INTERPRETEMENUSELECCION_H
#define FINAL_FIGHT_INTERPRETEMENUSELECCION_H


#include "InterpreteServidor.h"

class InterpreteMenuSeleccion : public InterpreteServidor {

private:

public:
    using InterpreteServidor::InterpreteServidor;
    bool interpretarAccion(ACCION accion, stringstream &s) override;
    void finalizar() override;

};

class ConfirmarSeleccion : public EventoAProcesar {

private:
    Usuario *usuario;
    enum PERSONAJE personajeSeleccionado;

public:
    explicit ConfirmarSeleccion(Usuario *usuario, enum PERSONAJE personaje);
    void resolver() override;
};

#endif //FINAL_FIGHT_INTERPRETEMENUSELECCION_H
