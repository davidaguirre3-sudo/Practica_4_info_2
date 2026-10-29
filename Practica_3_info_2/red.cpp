#include "red.h"

#include <fstream>
#include <iomanip>
#include <limits>
#include <set>
#include <sstream>
#include <utility>

namespace {
const int INF = numeric_limits<int>::max() / 2;
}

bool Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty() || existeEnrutador(nombre)) return false;
    enrutadores_.emplace(nombre, Enrutador(nombre));
    actualizarTablas();
    return true;
}

bool Red::eliminarEnrutador(const string& nombre) {
    if (!existeEnrutador(nombre)) return false;
    for (auto& par : enrutadores_) par.second.eliminarVecino(nombre);
    enrutadores_.erase(nombre);
    actualizarTablas();
    return true;
}

bool Red::agregarEnlace(const string& a, const string& b, int costo) {
    if (a == b || costo <= 0) return false;
    if (!existeEnrutador(a) || !existeEnrutador(b)) return false;

    enrutadores_.at(a).agregarVecino(b, costo);
    enrutadores_.at(b).agregarVecino(a, costo);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnlace(const string& a, const string& b) {
    if (!existeEnrutador(a) || !existeEnrutador(b)) return false;

    bool existia = enrutadores_.at(a).eliminarVecino(b);
    enrutadores_.at(b).eliminarVecino(a);
    if (existia) actualizarTablas();
    return existia;
}

bool Red::cargarDesdeArchivo(const string& ruta, string& error) {
    ifstream archivo(ruta);
    if (!archivo) {
        error = "no se pudo abrir '" + ruta + "'";
        return false;
    }

    Red nueva;
    string linea;
    int numero = 0;
    while (getline(archivo, linea)) {
        ++numero;
        size_t pos = linea.find('#');
        if (pos != string::npos) linea.erase(pos);

        istringstream ss(linea);
        string tipo;
        if (!(ss >> tipo)) continue;

        bool ok = false;
        if (tipo == "R") {
            string nombre;
            ok = (ss >> nombre) && nueva.agregarEnrutador(nombre);
        } else if (tipo == "E") {
            string a, b;
            int costo = 0;
            ok = (ss >> a >> b >> costo) && nueva.agregarEnlace(a, b, costo);
        }
        if (!ok) {
            error = "linea " + to_string(numero) + " invalida: " + linea;
            return false;
        }
    }
    enrutadores_ = move(nueva.enrutadores_);
    return true;
}

bool Red::existeEnrutador(const string& nombre) const {
    return enrutadores_.count(nombre) > 0;
}

const Enrutador* Red::obtenerEnrutador(const string& nombre) const {
    auto it = enrutadores_.find(nombre);
    return it != enrutadores_.end() ? &it->second : nullptr;
}

list<string> Red::calcularCamino(const string& origen, const string& destino, int& costo) const {
    list<string> camino;
    costo = -1;
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) return camino;

    map<string, int> dist;
    map<string, string> prev;
    rutasMinimas(origen, dist, prev);
    if (dist.at(destino) >= INF) return camino;
    costo = dist.at(destino);

    for (string actual = destino; ; actual = prev.at(actual)) {
        camino.push_front(actual);
        if (actual == origen) break;
    }
    return camino;
}

void Red::imprimirTablas(ostream& os) const {
    os << setw(4) << "";
    for (const auto& col : enrutadores_) os << setw(5) << col.first;
    os << '\n';
    for (const auto& fila : enrutadores_) {
        const map<string, int>& tabla = fila.second.tablaCostos();
        os << setw(4) << fila.first;
        for (const auto& col : enrutadores_) {
            auto it = tabla.find(col.first);
            if (it != tabla.end()) os << setw(5) << it->second;
            else                   os << setw(5) << "INF";
        }
        os << '\n';
    }
}

void Red::rutasMinimas(const string& origen, map<string, int>& dist, map<string, string>& prev) const {
    dist.clear();
    prev.clear();
    for (const auto& par : enrutadores_) dist[par.first] = INF;
    dist[origen] = 0;

    set<pair<int, string>> pendientes;
    pendientes.insert(make_pair(0, origen));

    while (!pendientes.empty()) {
        int distActual = pendientes.begin()->first;
        string actual = pendientes.begin()->second;
        pendientes.erase(pendientes.begin());

        for (const auto& vec : enrutadores_.at(actual).vecinos()) {
            const string& destino = vec.first;
            int nueva = distActual + vec.second;
            if (nueva < dist[destino]) {
                pendientes.erase(make_pair(dist[destino], destino));
                dist[destino] = nueva;
                prev[destino] = actual;
                pendientes.insert(make_pair(nueva, destino));
            }
        }
    }
}

void Red::actualizarTablas() {
    for (auto& par : enrutadores_) {
        map<string, int> dist;
        map<string, string> prev;
        rutasMinimas(par.first, dist, prev);

        map<string, int> alcanzables;
        for (const auto& d : dist)
            if (d.second < INF) alcanzables[d.first] = d.second;
        par.second.actualizarTabla(alcanzables);
    }
}