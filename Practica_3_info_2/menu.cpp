#include "menu.h"

#include <iostream>
#include <list>
#include <sstream>
#include <string>

namespace {
string leerPalabra(const string& mensaje) {
    cout << mensaje;
    string linea, palabra;
    getline(cin, linea);
    istringstream ss(linea);
    ss >> palabra;
    return palabra;
}

int leerEntero(const string& mensaje) {
    cout << mensaje;
    string linea;
    getline(cin, linea);
    istringstream ss(linea);
    int valor;
    if (!(ss >> valor)) return -1;
    return valor;
}
}

void Menu::ejecutar() {
    cargarArchivo();

    string opcion;
    while (true) {
        mostrarOpciones();
        cout << "Opcion: ";
        if (!getline(cin, opcion)) break;

        if (opcion == "0")      break;
        else if (opcion == "1") agregarEnrutador();
        else if (opcion == "2") eliminarEnrutador();
        else if (opcion == "3") agregarEnlace();
        else if (opcion == "4") eliminarEnlace();
        else if (opcion == "5") consultarCamino();
        else if (opcion == "6") mostrarTablas();
        else cout << "Opcion invalida.\n";
    }
}

void Menu::mostrarOpciones() const {
    cout << "\n=== Simulador de red de enrutadores ===\n"
         << "1. Agregar enrutador\n"
         << "2. Eliminar enrutador\n"
         << "3. Agregar enlace (o cambiar su costo)\n"
         << "4. Eliminar enlace\n"
         << "5. Consultar camino entre dos enrutadores\n"
         << "6. Mostrar tablas de costos\n"
         << "0. Salir\n";
}

void Menu::cargarArchivo() {
    const string ruta = "topologia.txt";
    string error;
    if (red_.cargarDesdeArchivo(ruta, error)) cout << "Red cargada desde " << ruta << ".\n";
    else cout << "No se pudo cargar " << ruta << ": " << error << "\n";
}

void Menu::agregarEnrutador() {
    string nombre = leerPalabra("Nombre del enrutador: ");
    if (red_.agregarEnrutador(nombre)) cout << "Enrutador agregado.\n";
    else cout << "No se pudo agregar (nombre vacio o ya existe).\n";
}

void Menu::eliminarEnrutador() {
    string nombre = leerPalabra("Nombre del enrutador: ");
    if (red_.eliminarEnrutador(nombre)) cout << "Enrutador eliminado.\n";
    else cout << "El enrutador no existe.\n";
}

void Menu::agregarEnlace() {
    string a = leerPalabra("Enrutador 1: ");
    string b = leerPalabra("Enrutador 2: ");
    int costo = leerEntero("Costo (entero > 0): ");
    if (red_.agregarEnlace(a, b, costo)) cout << "Enlace agregado.\n";
    else cout << "No se pudo agregar (deben existir, ser distintos y costo > 0).\n";
}

void Menu::eliminarEnlace() {
    string a = leerPalabra("Enrutador 1: ");
    string b = leerPalabra("Enrutador 2: ");
    if (red_.eliminarEnlace(a, b)) cout << "Enlace eliminado.\n";
    else cout << "Ese enlace no existe.\n";
}

void Menu::consultarCamino() const {
    string origen = leerPalabra("Origen: ");
    string destino = leerPalabra("Destino: ");
    if (!red_.existeEnrutador(origen) || !red_.existeEnrutador(destino)) {
        cout << "Alguno de los enrutadores no existe.\n";
        return;
    }

    int costo;
    list<string> camino = red_.calcularCamino(origen, destino, costo);
    if (camino.empty()) {
        cout << "No hay camino entre " << origen << " y " << destino << ".\n";
        return;
    }

    cout << "Camino: ";
    for (auto it = camino.begin(); it != camino.end(); ++it) {
        if (it != camino.begin()) cout << " -> ";
        cout << *it;
    }
    cout << "\nCosto total: " << costo << "\n";
}

void Menu::mostrarTablas() const {
    red_.imprimirTablas();
}