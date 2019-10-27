//
// Created by sebas on 12/10/19.
//

#include "ActualizadorUsuario.h"
#include "../../usuario/Usuario.h"
#include "../../servicios/Locator.h"
#include "../../modelo/EventoUsuario.h"
#include "../../modelo/Accion.h"

ActualizadorUsuario::ActualizadorUsuario(EventosAProcesar *eventos, ManagerUsuarios *manager) :
        usuarioAgregado(0),
        eventos(eventos),
        manager(manager) {
    Locator::logger()->log(DEBUG, "Se crea un actualizador de usuario.");
}


bool ActualizadorUsuario::validarContrasenia(Usuario *usuario, Socket *socket) {

    bool contraseniaCorrecta = Locator::configuracion()->isUserOk(usuario->getUsuario(), usuario->getContrasenia());
    if (contraseniaCorrecta) {
        Locator::logger()->log(INFO, "Se recibió una contraseña correcta del usuario: " + usuario->getUsuario() + ".");
    } else {
        Locator::logger()->log(ERROR,
                               "Se recibió una contraseña incorrecta del usuario: " + usuario->getUsuario() + ".");
        EventoUsuario evento(CONTRASENIA_INCORRECTA);
        stringstream ss;
        evento.serializar(ss);
        socket->enviar(ss);
    }
    return contraseniaCorrecta;
}

Usuario *ActualizadorUsuario::getUsuario(Socket *socket) {
    auto *nuevoUsuario = new Usuario;

    stringstream s;
    bool fin = false;
    while (!fin) {
        if (!socket->recibir(s)) {
            Locator::logger()->log(ERROR, "Se desconectó el cliente de forma inesperada. Se termina el hilo.");
            pthread_exit(nullptr);
        }
        Accion accion;
        accion.deserializar(s);
        switch (accion.accion()) {
            case ENVIAR_USUARIO:
                nuevoUsuario->deserializar(s);
                if(validarContrasenia(nuevoUsuario, socket)) fin = true;
                break;
            case FIN:
                Locator::logger()->log(INFO, "Se desconecta voluntariamente un cliente en el menu de usuario.");
                pthread_exit(nullptr);
            default:
                Locator::logger()->log(ERROR, "Se recibió una acción inválilda en el actualizador de usuario.");
                break;
        }
    };

    nuevoUsuario->setSocket(socket);
    auto *crear = new AgregarUsuario(nuevoUsuario, manager, usuarioAgregado);
    eventos->push(crear);
    usuarioAgregado.wait();

    if (!nuevoUsuario->getValido()) { // Usuario invalido
        Locator::logger()->log(INFO, "Se desconecta el usuario " + nuevoUsuario->getUsuario() + " y se termina su hilo.");
        pthread_exit(nullptr);
    }
    return nuevoUsuario;
}

AgregarUsuario::AgregarUsuario(Usuario *usuario, ManagerUsuarios *manager, semaphore &semaphore) :
        usuarioAgregado(semaphore),
        usuario(usuario),
        manager(manager) {}

void AgregarUsuario::resolver() {
    EventoUsuario *evento;
    if (manager->estaPresente(usuario)) {
        Usuario *usuarioAnterior = manager->getUsuarioAnterior(usuario);

        if (usuarioAnterior->estaConectado()) { // El usuario esta conectado desde otro cliente.
            usuario->setValido(false);
            evento = new EventoUsuario(USUARIO_YA_CONECTADO);
            Locator::logger()->log(ERROR, "El usuario: " + usuarioAnterior->getUsuario() +
                                          " se encuentra conectado desdo otro cliente.");

        } else { // El usuario se había desconectado.
            usuario->setPersonaje(usuarioAnterior->getPersonaje());
            manager->reemplazarUsuarioCon(usuario);
            usuario->setValido(true);
            evento = new EventoUsuario(CONECTADO);
            Locator::logger()->log(INFO,
                                   "El usuario: " + usuarioAnterior->getUsuario() + " se reconectó a la partida.");
        }
    } else {
        if (manager->faltanJugadores()) { // Hay espacio para un jugador más.
            manager->agregarUsuario(usuario);
            usuario->setValido(true);
            evento = new EventoUsuario(CONECTADO);
            Locator::logger()->log(INFO, "El usuario: " + usuario->getUsuario() + " se conectó a la partida.");

        } else { // No queda espacio en la partida
            Locator::logger()->log(ERROR, "El usuario: " + usuario->getUsuario() +
                                          " trató de conectarse cuando la partida ya estaba completa.");
            usuario->setValido(false);
            evento = new EventoUsuario(PARTIDA_LLENA);
        }
    }
    stringstream ss;
    evento->serializar(ss);
    usuario->getSocket()->enviar(ss);
    usuarioAgregado.post();
}

