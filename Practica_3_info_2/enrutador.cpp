#include "enrutador.h"

Enrutador::Enrutador(const string& nombre) : nombre_(nombre) {
    inicializarTabla();
}

const string& Enrutador::nombre() const {
    return nombre_;
}

void Enrutador::agregarVecino(const string& vecino, int costo) {
    vecinos_[vecino] = costo;
}

bool Enrutador::eliminarVecino(const string& vecino) {
    return vecinos_.erase(vecino) > 0;
}

const map<string, int>& Enrutador::vecinos() const {
    return vecinos_;
}

void Enrutador::inicializarTabla() {
    tablaCostos_.clear();
    tablaCostos_[nombre_] = 0;
    for (const auto& v : vecinos_)
        tablaCostos_[v.first] = v.second;
}

void Enrutador::actualizarTabla(const map<string, int>& costos) {
    tablaCostos_ = costos;
}

const map<string, int>& Enrutador::tablaCostos() const {
    return tablaCostos_;
}