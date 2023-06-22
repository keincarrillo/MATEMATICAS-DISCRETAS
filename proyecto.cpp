// Alumno: Carrillo Rodriguez Kein Isaac
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Función para cargar una matriz de adyacencia desde un archivo de texto
vector<vector<int>> cargarMatrizDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return {};
    }

    vector<vector<int>> matriz;

    string linea;
    while (getline(archivo, linea)) {
        vector<int> fila;
        stringstream ss(linea);
        string valor;
        while (getline(ss, valor, ',')) {
            fila.push_back(stoi(valor));
        }
        matriz.push_back(fila);
    }

    archivo.close();
    return matriz;
}

// Función para encontrar la ruta más corta entre dos vértices en un grafo representado por una matriz de adyacencia
vector<int> encontrarRutaMasCorta(const vector<vector<int>>& matrizAdyacencia, int origen, int destino) {
    int numVertices = matrizAdyacencia.size();

    // Verificar que los valores en la matriz de adyacencia sean válidos
    for (const auto& fila : matrizAdyacencia) {
        for (int valor : fila) {
            if (valor < 0 || valor > numVertices) {
                cout << "Los valores en la matriz de adyacencia no son válidos." << endl;
                return {};
            }
        }
    }

    // Vector de distancias mínimas desde el origen a cada vértice
    vector<int> distancia(numVertices, numeric_limits<int>::max());

    // Vector de padres para reconstruir la ruta más corta
    vector<int> padre(numVertices, -1);

    // Marcar el origen con distancia cero
    distancia[origen] = 0;

    // Cola para el algoritmo de búsqueda en anchura (BFS)
    queue<int> cola;
    cola.push(origen);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        for (int i = 0; i < numVertices; i++) {
            // Si hay una arista entre el vértice actual y el vértice i
            if (matrizAdyacencia[actual][i] != 0) {
                int distanciaNueva = distancia[actual] + matrizAdyacencia[actual][i];
                if (distanciaNueva < distancia[i]) {
                    distancia[i] = distanciaNueva;
                    padre[i] = actual;
                    cola.push(i);
                }
            }
        }
    }

    // Verificar si se encontró una ruta válida desde el origen al destino
    if (padre[destino] == -1) {
        // No hay una ruta válida
        return {};
    }

    // Reconstruir la ruta más corta desde el destino hasta el origen
    vector<int> ruta;
    int vertice = destino;
    while (vertice != -1) {
        ruta.insert(ruta.begin(), vertice);
        vertice = padre[vertice];
    }

    return ruta;
}

int main() {
    vector<vector<int>> matrizAdyacencia = cargarMatrizDesdeArchivo("matriz.txt");

    int origen = 2;
    int destino = 4;

    vector<int> rutaMasCorta = encontrarRutaMasCorta(matrizAdyacencia, origen, destino);

    if (rutaMasCorta.empty()) {
        cout << "No hay conexión entre el origen y el destino." << endl;
    } else {
        cout << "Ruta mas corta: ";
        for (int vertice : rutaMasCorta) {
            cout << vertice << " ";
        }
        cout << endl;
    }

    return 0;
}
