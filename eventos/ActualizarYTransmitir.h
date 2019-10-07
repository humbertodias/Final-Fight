//
// Created by sebas on 7/10/19.
//

#ifndef FINAL_FIGHT_ACTUALIZARYTRANSMITIR_H
#define FINAL_FIGHT_ACTUALIZARYTRANSMITIR_H


#include "Eventos.h"

class ActualizarYTransmitir : public EventoAProcesar {

private:
    Mapa *mapa;
    EventosATransmitir *eventosATransmitir;
    void transmitir();

public:
    ActualizarYTransmitir(Mapa *mapa, EventosATransmitir *eventosATransmitir);
    void resolver() override;
};


#endif //FINAL_FIGHT_ACTUALIZARYTRANSMITIR_H
