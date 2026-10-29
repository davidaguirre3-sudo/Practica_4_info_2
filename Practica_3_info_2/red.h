#ifndef RED_H
#define RED_H

#include <iostream>
#include <list>
#include <map>
#include <string>

#include "enrutador.h"

using namespace std;

class Red {
public:
    bool agregarEnrutador(const string& nombre);
    bool eliminarEnrutador(const string& nombre);
    bool agregarEnlace(const string& a, const string& b, int costo);
    bool eliminarEnlace(const string& a, const string& b);

    bool cargarDesdeArchivo(const string& ruta, string& error);

    bool existeEnrutador(const string& nombre) const;
    const Enrutador* obtenerEnrutador(const string& nombre) const;

    list<string> calcularCamino(const string& origen, const string& destino, int& costo) const;

    void imprimirTablas(ostream& os = cout) const;

private:
    void rutasMinimas(const string& origen, map<string, int>& dist, map<string, string>& prev) const;
    void actualizarTablas();

    map<string, Enrutador> enrutadores_;
};

#endif