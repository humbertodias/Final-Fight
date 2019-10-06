//
// Created by sebas on 5/10/19.
//

#include "Procesamiento.h"
#include "../servicios/Locator.h"

Eventos *Procesamiento::devolverCola() {
    return &eventos;
}

void Procesamiento::procesar() {
    while (true) {
        auto *evento = eventos.pop();
        Locator::logger()->log(DEBUG, "Se procesa msg: " + evento->msg + ".");
        if(evento->msg == "fin")
            break;
    }
}

pthread_t Procesamiento::procesarEnHilo() {
    pthread_t hilo;
    pthread_create(&hilo, nullptr, [](void *arg) -> void * {
        auto *procesamiento = (Procesamiento *) arg;
        procesamiento->procesar();
        return nullptr;
    }, (void *) this);

    Locator::logger()->log(DEBUG, "Se creó el hilo de procesamiento.");
    return hilo;
}

