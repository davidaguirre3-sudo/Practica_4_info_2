#ifndef MENU_H
#define MENU_H

#include "red.h"

class Menu {
public:
    void ejecutar();

private:
    void mostrarOpciones() const;
    void cargarArchivo();
    void agregarEnrutador();
    void eliminarEnrutador();
    void agregarEnlace();
    void eliminarEnlace();
    void consultarCamino() const;
    void mostrarTablas() const;

    Red red_;
};

#endif