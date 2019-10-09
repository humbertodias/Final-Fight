//
// Created by sebas on 8/10/19.
//

#ifndef FINAL_FIGHT_ACTUALIZADORCLIENTE_H
#define FINAL_FIGHT_ACTUALIZADORCLIENTE_H


#include "../modelo/Mapa.h"
#include "../eventos/Eventos.h"

using namespace std;

class ActualizadorCliente {

private:
    Mapa *mapa;
    bool borrar = true;

public:
    explicit ActualizadorCliente(Mapa *mapa);
    void actualizarEntidades(stringstream &s);

};


#endif //FINAL_FIGHT_ACTUALIZADORCLIENTE_H
