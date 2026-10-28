#ifndef RED_H
#define RED_H

#include <map>
#include <string>

#include "enrutador.h"

using namespace std;

class Red
{
public:
    bool agregarEnrutador(const string& nombre);
    bool agregarEnlace(const string& a, const string& b, int costo);
    const Enrutador* obtenerEnrutador(const string& nombre) const;

private:
    map<string, Enrutador> enrutadores_;
};

#endif // RED_H