#include "red.h"

bool Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty() || enrutadores_.count(nombre) > 0) return false;
    enrutadores_.emplace(nombre, Enrutador(nombre));
    return true;
}

bool Red::agregarEnlace(const string& a, const string& b, int costo) {

    if (a == b || costo <= 0) return false;
    if (enrutadores_.count(a) == 0 || enrutadores_.count(b) == 0) return false;

    Enrutador& ra = enrutadores_.at(a);
    Enrutador& rb = enrutadores_.at(b);
    ra.agregarVecino(b, costo);
    rb.agregarVecino(a, costo);
    ra.inicializarTabla();
    rb.inicializarTabla();
    return true;
}

const Enrutador* Red::obtenerEnrutador(const string& nombre) const {
    auto it = enrutadores_.find(nombre);
    return it != enrutadores_.end() ? &it->second : nullptr;
}