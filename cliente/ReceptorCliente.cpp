//
// Created by sebas on 5/10/19.
//

#include <sys/socket.h>
#include "ReceptorCliente.h"
#include "../servicios/Locator.h"
#include "../modelo/Entidad.h"
#include "ActualizadorCliente.h"

std::chrono::time_point<std::chrono::system_clock> ReceptorCliente::ultimaRecepcion = std::chrono::high_resolution_clock::now();

ReceptorCliente::ReceptorCliente() :
        disponible(0) {}

void ReceptorCliente::recibir() {
    ultimaRecepcion = std::chrono::high_resolution_clock::now();
    while (conexionActiva) {
        stringstream s;
        if(!Locator::socket()->recibir(s)){
            Locator::logger()->log(ERROR, "Se detecta desconexión del servidor.");
            conexionActiva = false;
            disponible.post();
            break;
        }
        ultimaRecepcion = std::chrono::high_resolution_clock::now();

        {
            std::lock_guard<std::mutex> lock(mutex);
            ultimoStream.str(std::string());
            ultimoStream << s.str();
            if(!nuevo){
                nuevo = true;
                disponible.post();
            }
        }
    }
    Locator::logger()->log(DEBUG, "Se termina el hilo del receptor.");
}

void ReceptorCliente::devolverStreamMasReciente(stringstream &s) {
    disponible.wait();
    std::lock_guard<std::mutex> lock(mutex);
    s << ultimoStream.str();
    nuevo = false;
}

pthread_t ReceptorCliente::recibirEnHilo() {
    pthread_t hilo;
    pthread_create(&hilo, nullptr, [](void *arg) -> void * {
        auto *receptor = (ReceptorCliente *) arg;
        receptor->recibir();
        return nullptr;
    }, (void *) this);

    Locator::logger()->log(DEBUG, "Se creó el hilo de recepción.");
    return hilo;
}

bool ReceptorCliente::conexionEstaActiva(){
    return conexionActiva;
}

void ReceptorCliente::finalizar() {
    conexionActiva = false;
}
