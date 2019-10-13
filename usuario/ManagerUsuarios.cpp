//
// Created by leandro on 7/10/19.
//

#include "ManagerUsuarios.h"
#include "../servicios/Locator.h"
#include <algorithm>

ManagerUsuarios::ManagerUsuarios(int max) :
    maximo(max),
    juegoListo(1 - max){}

void ManagerUsuarios::agregarUsuario(Usuario *nuevoUsuario) {
    Locator::logger()->log(DEBUG, "Se agrega el usuario: " + nuevoUsuario->getUsuario());

    if(usuarios.size() < maximo && !estaPresente(nuevoUsuario)){
        usuarios.push_back(nuevoUsuario);
    }else{
        throw exception();
    }
    
    Locator::logger()->log(DEBUG, "Faltan " + to_string(cantidadJugadoresFaltantes()) + " jugadores.");

    juegoListo.post();
}

bool ManagerUsuarios::estaPresente(Usuario *usuario){
    auto findIter = std::find(usuarios.begin(), usuarios.end(), usuario);
    return findIter != usuarios.end();
}

//int ManagerUsuarios::getCantidadLogueados() {
//    return usuarios.size();
//}
//
//bool ManagerUsuarios::faltanJugadores() {
//    return usuarios.size() < maximo;
//}
//
int ManagerUsuarios::cantidadJugadoresFaltantes() {
    return maximo - usuarios.size();
}

void ManagerUsuarios::esperarUsuarios() {
    juegoListo.wait();
}

//
//vector<Socket> ManagerUsuarios::getSockets(){
//    vector<Socket> conexiones;
//    std::list<Usuario>::iterator it = usuarios.begin();
//
//    do{
//        int socket = it->getSocket()->getIntSocket();
//        conexiones.emplace_back(socket);
//        it.operator++();
//    }
//    while(usuarios.end() != it);
//
//    return conexiones;
//}
//
//void ManagerUsuarios::cambiarSocketParaUsuario(Usuario usuario, Socket* pSocket) {
//    bool encontrado = false;
//
//    std::list<Usuario>::iterator it = usuarios.begin();
//
//    while(usuarios.end() != it && !encontrado){
//        encontrado = it->getUsuario() == usuario.getUsuario();
//    }
//
//    it->setSocket(pSocket);
//
//    Locator::logger()->log(INFO, "Se cambio socket para usuario " + it->getUsuario());
//}
