//
// Created by sebas on 30/8/19.
//

#include "gtest/gtest.h"
#include "../model/Mapa.h"
#include "../graphics/BoxGraphics.h"

TEST(Mapa, CrearUnMapaVacioNoPierdeMemoria) {
    Mapa mapa(100, 1000, 300);
}

TEST(Mapa, AgregarMapeablesAUnMapaNoPierdeMemoria) {
    Mapa mapa(2, 3, 4);
    BoxGraphics graphics;
    Mapeable mapeable = Mapeable(6, 9, 5, &graphics);

    mapa.agregar(&mapeable);
}

TEST(Mapa, DevolverMapeablesDevuelveLosMismosObjetos) {
    Mapa mapa(100, 1000, 300);
    BoxGraphics graphics;
    Mapeable mapeable1 = Mapeable(2, 3, 4, &graphics);
    Mapeable mapeable2 = Mapeable(6, 9, 5, &graphics);

    mapa.agregar(&mapeable1);
    mapa.agregar(&mapeable2);

    bool encontrado1 = false;
    bool encontrado2 = false;

    for(auto i : mapa.devolverMapeables()){
        if (i == (&mapeable1)) {
            encontrado1 = true;
        } else if(i == (&mapeable2)) {
            encontrado2 = true;
        }
    }

    EXPECT_TRUE(encontrado1);
    EXPECT_TRUE(encontrado2);
}