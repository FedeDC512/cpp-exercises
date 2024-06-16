/*Implementare l’algoritmo di Kruskal per il calcolo del Minimum Spanning Tree che utilizzi la classe Union Find
definita in un'altra attività. Fornire in output la lista degli archi ed il peso totale del MST*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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
};

struct Edge {
    int u, v;
    double weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class WeightedGraph {
private:
    int V, E;
    vector<Edge> edges;

public:
    // Costruttore che crea un grafo pesato vuoto con V vertici
    WeightedGraph(int V) : V(V), E(0) {}

    // Costruttore che crea un grafo pesato da un file di input
    WeightedGraph(ifstream& in) {
        in >> V >> E;
        for (int i = 0; i < E; i++) {
            int u, v;
            double weight;
            in >> u >> v >> weight;
            addEdge(u, v, weight);
        }
    }

    // Metodo per aggiungere un arco (u, v) di peso w al grafo
    void addEdge(int u, int v, double weight) {
        edges.push_back({u, v, weight});
    }

    // Metodo per ottenere tutti gli archi del grafo
    const vector<Edge>& getEdges() const {
        return edges;
    }

    int numVertices() const {
        return V;
    }

    int numEdges() const {
        return E;
    }

    // Metodo per stampare il grafo
    void printGraph() const {
        cout << "Grafo Pesato:" << endl;
        for (const auto& edge : edges) {
            cout << edge.u << " - " << edge.v << " (peso: " << edge.weight << ")" << endl;
        }
    }
};

void KruskalMST(const WeightedGraph& G) {
    vector<Edge> mst; // Lista degli archi del MST
    double totalWeight = 0.0; // Peso totale del MST

    // Ottieni gli archi del grafo e ordinali per peso
    vector<Edge> edges = G.getEdges();
    sort(edges.begin(), edges.end());

    // Crea la struttura Union Find con il numero di vertici del grafo
    UnionFind uf(G.numVertices());

    // Scorri gli archi ordinati e costruisci il MST
    for (const auto& edge : edges) {
        if (!uf.Connected(edge.u, edge.v)) {
            uf.Union(edge.u, edge.v);
            mst.push_back(edge);
            totalWeight += edge.weight;
            // Termina se ho trovato V-1 archi (dove V è il numero di vertici)
            if (mst.size() == G.numVertices() - 1) {
                break;
            }
        }
    }

    // Stampa gli archi del MST e il peso totale
    cout << "Minimum Spanning Tree (MST):" << endl;
    for (const auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " (peso: " << edge.weight << ")" << endl;
    }
    cout << "Peso totale del MST: " << totalWeight << endl;
}

int main() {
    ifstream input("C:\\Users\\fedea\\Documents\\Unipa Materie\\Laboratorio di Algoritmi\\C++\\algoritmo_kruskal\\grafo.txt");
    if (!input.is_open()) {
        cout << "Errore durante l'apertura del file." << endl;
    } else {
        WeightedGraph G(input);

        G.printGraph();
        cout << endl;

        KruskalMST(G);
    }

    return 0;
}
