//
// Created by sebas on 30/8/19.
//

#include <algorithm>
#include "Mapa.h"
#include "../servicios/Locator.h"

using namespace std;

IdEntidad Mapa::ultimoId = 0;

Entidad *Mapa::crearEntidad() {
    auto* e = new Entidad();
    {
        std::lock_guard<std::mutex> lock(m);
        entidades[ultimoId++] = e;
    }
    return e;
}

Entidad *Mapa::crearEntidadConId(IdEntidad idEntidad) {
    auto* e = new Entidad();
    {
        std::lock_guard<std::mutex> lock(m);
        entidades[idEntidad] = e;
    }
    return e;
}

vector<Entidad *> Mapa::devolverEntidades() {
    std::lock_guard<std::mutex> lock(m);
    vector<Entidad *> values(entidades.size());
    auto value_selector = [](auto pair) { return pair.second; };
    transform(entidades.begin(), entidades.end(), values.begin(), value_selector);
    return values;
}

void Mapa::vaciarMapa() {
    std::lock_guard<std::mutex> lock(m);
    entidades.clear();
    Locator::logger()->log(DEBUG, "Se vació el vector de entidades.");
    for(auto tupla : jugadores){
        entidades[tupla.first] = tupla.second;
        Locator::logger()->log(DEBUG, "Se agregó al  jugador " + to_string(tupla.first) + " a las entidades.");
    }
}

Entidad *Mapa::crearJugador() {
    Entidad *jugador = crearEntidad();
    {
        std::lock_guard<std::mutex> lock(m);
        jugadores[ultimoId] = jugador;
    }
    return jugador;
}

void Mapa::agregarJugadorConId(IdEntidad idEntidad, Entidad *jugador) {
    std::lock_guard<std::mutex> lock(m);
    jugadores[idEntidad] = jugador;
//    entidades[idEntidad] = jugador;
}

Entidad *Mapa::getJugador() {
    std::lock_guard<std::mutex> lock(m);
    for(auto tuple : jugadores)
        return tuple.second;
    return nullptr;
}

Entidad *Mapa::getEntidad(IdEntidad idEntidad) {
    std::lock_guard<std::mutex> lock(m);
    return entidades[idEntidad];
}

bool Mapa::contiene(IdEntidad idEntidad) {
    std::lock_guard<std::mutex> lock(m);
    return !(entidades.find(idEntidad) == entidades.end());
}

unordered_map<IdEntidad, Entidad *> Mapa::devolverEntidadesConId() {
    std::lock_guard<std::mutex> lock(m);
    return entidades;
}

