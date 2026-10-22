#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <map>
#include <string>

using namespace std;

class Enrutador {
public:
    explicit Enrutador(const string& nombre);

    const string& nombre() const;

    void agregarVecino(const string& vecino, int costo);
    const map<string, int>& vecinos() const;

    void inicializarTabla();
    const map<string, int>& tablaCostos() const;

private:
    string nombre_;
    map<string, int> vecinos_;
    map<string, int> tablaCostos_;
};

#endif // ENRUTADOR_H