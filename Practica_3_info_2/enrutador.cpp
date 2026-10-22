#include "enrutador.h"
#include "iostream"

using namespace std;

Enrutador::Enrutador(const string& nombre) : nombre_(nombre) {
    inicializarTabla();
}

const string& Enrutador::nombre() const {
    return nombre_;
}

void Enrutador::agregarVecino(const string& vecino, int costo) {
    vecinos_[vecino] = costo;
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

const map<string, int>& Enrutador::tablaCostos() const {
    return tablaCostos_;
}