/*Definire una classe per implementare la Union Find attraverso la struttura Weighted Quick-Union by Size, che abbia:
- Array parent
- Array sz
- Costruttore che preso in input un intero n inizializza la struttura con n elementi
- Metodi Find, Union e Connected*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class UnionFind {
private:
    vector<int> parent; // Array per memorizzare il padre di ogni elemento
    vector<int> sz; // Array per memorizzare le dimensioni degli alberi

public:
    // Costruttore che inizializza la struttura con n elementi
    UnionFind(int n) {
        parent.resize(n);
        sz.resize(n, 1); // Inizializza ogni dimensione a 1
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Ogni elemento è il proprio padre
        }
    }

    // Metodo che trova la radice dell'elemento i
    int Find(int i) {
        while (i != parent[i]) {
            parent[i] = parent[parent[i]]; // Path compression
            i = parent[i];
        }
        return i;
    }

    // Metodo che unisce due insiemi
    void Union(int i, int j) {
        int rootI = Find(i);
        int rootJ = Find(j);

        if (rootI != rootJ) {
            // Collega l'albero più piccolo alla radice dell'albero più grande
            if (sz[rootI] < sz[rootJ]) {
                parent[rootI] = rootJ;
                sz[rootJ] += sz[rootI];
            } else {
                parent[rootJ] = rootI;
                sz[rootI] += sz[rootJ];
            }
        }
    }

    // Metodo che verifica se due elementi sono nello stesso insieme
    bool Connected(int i, int j) {
        return Find(i) == Find(j);
    }

    // Metodo per stampare la struttura parent
    void printParent() {
        for (size_t i = 0; i < parent.size(); i++) {
            cout << "Elemento " << i << " -> Padre " << parent[i] << endl;
        }
    }

    // Metodo per stampare la struttura sz
    void printSize() {
        for (size_t i = 0; i < sz.size(); i++) {
            cout << "Elemento " << i << " -> Dimensione " << sz[i] << endl;
        }
    }
};

int main() {
    ifstream input("C:\\Users\\fedea\\Documents\\Unipa Materie\\Laboratorio di Algoritmi\\C++\\union_find\\grafo.txt");
    if (!input.is_open()) {
        cout << "Errore durante l'apertura del file." << endl;
    } else {
        int n, numEdges;
        input >> n >> numEdges;

        UnionFind uf(n);

        for (int i = 0; i < numEdges; i++) {
            int u, v;
            input >> u >> v;
            uf.Union(u, v);
        }

        cout << "Struttura parent:" << endl;
        uf.printParent();
        cout << endl;

        cout << "Struttura sz:" << endl;
        uf.printSize();
        cout << endl;

        cout << "0 e 4 sono connessi? " << (uf.Connected(0, 4) ? "Si" : "No") << endl;
        cout << "4 e 7 sono connessi? " << (uf.Connected(4, 7) ? "Si" : "No") << endl;
        cout << "6 e 5 sono connessi? " << (uf.Connected(6, 5) ? "Si" : "No") << endl;
        cout << "2 e 8 sono connessi? " << (uf.Connected(2, 8) ? "Si" : "No") << endl;
    }
    return 0;
}
