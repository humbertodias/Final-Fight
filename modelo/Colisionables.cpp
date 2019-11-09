//
// Created by franco on 31/10/19.
//

#include "Colisionables.h"
#include "Envolvente.h"
#include "../estados/EstadoDePersonajeServidor.h"
#include <utility>


void Colisionables::calcularPosiblesColisiones() {

    for ( auto *entidadCentral : colisionables ){
        auto* envolvente= entidadCentral->getEstado<Envolvente>("envolvente");
        auto* posicion = entidadCentral->getEstado<Posicion>("posicion");
        auto* velocidad = entidadCentral->getEstado<Velocidad>("velocidad");
        for ( auto* entidad_colisionable : colisionables ){

            auto *envolventeContrario = entidad_colisionable->getEstado<Envolvente>("envolvente");
            auto *posicionContrario = entidad_colisionable->getEstado<Posicion>("posicion");
            if ( entidad_colisionable != entidadCentral ) {

                auto *velocidadContrario = entidad_colisionable->getEstado<Velocidad>("velocidad");

                if ( velocidadContrario->y == 0 && velocidad->y != 0){
                    if (envolvente->colisionaAbajoCon(envolventeContrario) ){
                        posicion->y = envolventeContrario->posicion->y + envolventeContrario->profundidad + envolvente->profundidad;
                    }else if (envolvente->colisionaArribaCon(envolventeContrario)){
                        posicion->y = envolventeContrario->posicion->y - envolventeContrario->profundidad - envolvente->profundidad;
                    }
                }else if ( velocidadContrario->y != 0 && velocidad->y != 0 ){
                    if (envolvente->colisionaAbajoCon(envolventeContrario) || envolvente->colisionaArribaCon(envolventeContrario) ){
                        posicion->y -= int(velocidad->y);
                        posicionContrario->y -= int(velocidadContrario->y);
                    }
                }
                if ( velocidadContrario->x == 0 && velocidad->x != 0){
                    if (envolvente->colisionaPorIzquiedaCon(envolventeContrario) ){
                        posicion->x = envolventeContrario->posicion->x - envolventeContrario->ancho - envolvente->ancho;
                    }else if (envolvente->colisionaPorDerechaCon(envolventeContrario) ){
                        posicion->x = envolventeContrario->posicion->x + envolventeContrario->ancho + envolvente->ancho;
                    }
                }else if ( velocidadContrario->x != 0 && velocidad->x != 0 ){
                    if (envolvente->colisionaPorIzquiedaCon(envolventeContrario) || envolvente->colisionaPorDerechaCon(envolventeContrario) ){
                        posicion->x -= int(velocidad->x);
                        posicionContrario->x -= int(velocidadContrario->x);
                    }
                }
            }
        }

        if ( posicion->y >= limiteEnProfundidad ){
            posicion->y = limiteEnProfundidad - 1;
        }else if ( posicion->y <= limiteFrontal ){
            posicion->y = limiteFrontal;
        }
    }
}

void Colisionables::add(Entidad * entidad) {
    colisionables.insert(colisionables.begin(), entidad);

    auto* tipo = entidad->getEstado<Tipo>("tipo");
    if ( tipo->tipo() == ENEMIGO || tipo->tipo() == ELEMENTO ){
        enemigos.insert(enemigos.begin(), entidad);
    }else if ( tipo->tipo() == JUGADOR ){
        jugadores.insert(jugadores.begin(), entidad);
    }
}

void Colisionables::addLimitesDeEscenario(int profundidad, int frente) {
     this -> limiteEnProfundidad = profundidad;
     this -> limiteFrontal = frente;
}

void Colisionables::calcularAtaques() {
    for ( auto *jugador : jugadores ){
        auto* envolvente= jugador->getEstado<Envolvente>("envolvente ataque");
        auto* posicion = jugador->getEstado<Posicion>("posicion");
        auto* velocidad = jugador->getEstado<Velocidad>("velocidad");
        if ( envolvente != nullptr ){

            for ( auto *enemigo : enemigos ){
                auto* envolvente_enemigo= enemigo->getEstado<Envolvente>("envolvente");
                auto* posicion_enemigo = enemigo->getEstado<Posicion>("posicion");
                auto* velocidad_enemigo = enemigo->getEstado<Velocidad>("velocidad");
            }
        }
    }
}

