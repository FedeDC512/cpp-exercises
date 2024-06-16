/*Implementare l’algoritmo di Prim per il calcolo del Minimum Spanning Tree che utilizzi una classe Priority Queue
da implementare opportunamente. Fornire in output la lista degli archi ed il peso totale del MST*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Struttura per rappresentare un arco pesato
struct Edge {
    int u; // Vertice di partenza
    int v; // Vertice di destinazione
    double weight; // Peso dell'arco
};

// Classe per implementare una coda prioritaria
class PriorityQueue {
private:
    // Coppia (peso, vertice)
    typedef pair<double, int> PDI;
    priority_queue<PDI, vector<PDI>, greater<PDI>> pq; // Min-heap

public:
    // Metodo per inserire un elemento nella coda prioritaria
    void insert(int v, double weight) {
        pq.push({weight, v});
    }

    // Metodo per estrarre l'elemento con la priorità più bassa
    int extractMin() {
        int v = pq.top().second;
        pq.pop();
        return v;
    }

    // Metodo per verificare se la coda prioritaria è vuota
    bool isEmpty() {
        return pq.empty();
    }

    // Metodo per diminuire la priorità di un elemento nella coda prioritaria
    void decreaseKey(int v, double weight) {
        // Non è possibile implementare questa funzione con la STL priority_queue
    }
};

class WeightedGraph {
private:
    int V, E;
    vector<Edge> edges;
    vector<vector<Edge>> adj; // Lista delle adiacenze

public:
    // Costruttore che crea un grafo pesato vuoto con V vertici
    WeightedGraph(int V) : V(V), E(0) {
        adj.resize(V); // Inizializza la lista delle adiacenze con V elementi vuoti
    }

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
    
    // Metodo per ottenere gli archi adiacenti al vertice v
    const vector<Edge>& adjacent(int v) const {
        return adj[v];
    }

    // Metodo per stampare il grafo
    void printGraph() const {
        cout << "Grafo Pesato:" << endl;
        for (const auto& edge : edges) {
            cout << edge.u << " - " << edge.v << " (peso: " << edge.weight << ")" << endl;
        }
    }
};

void PrimMST(const WeightedGraph& G) {
    int V = G.numVertices();
    vector<Edge> mst; // Lista degli archi del MST
    double totalWeight = 0.0; // Peso totale del MST

    PriorityQueue pq; // Coda prioritaria per i vertici

    vector<bool> inMST(V, false); // Indica se un vertice è presente nel MST
    vector<double> distTo(V, numeric_limits<double>::infinity()); // Distanza minima da un vertice al MST
    vector<int> edgeTo(V, -1); // Indica il vertice adiacente che collega il vertice al MST

    // Inizia dalla radice 0
    int root = 0;
    distTo[root] = 0.0;
    pq.insert(root, 0.0);

    while (!pq.isEmpty()) {
        int v = pq.extractMin();
        inMST[v] = true;

        cout << "Vertice v: " << v << endl;

        // Aggiungi l'arco al MST
        if (edgeTo[v] != -1) {
            mst.push_back({edgeTo[v], v, distTo[v]});
            totalWeight += distTo[v];
        }

        // Aggiorna la distanza per i vertici adiacenti
        for (const Edge& e : G.adjacent(v)) {
            int w = e.v;
            double weight = e.weight;
            if (!inMST[w] && weight < distTo[w]) {
                distTo[w] = weight;
                edgeTo[w] = v;
                pq.insert(w, weight);
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
    // Apri il file contenente il grafo
    ifstream input("C:\\Users\\fedea\\Documents\\Unipa Materie\\Laboratorio di Algoritmi\\C++\\algoritmo_prim\\grafo.txt");
    if (!input.is_open()) {
        cout << "Errore durante l'apertura del file." << endl;
    } else {
        WeightedGraph G(input);

        G.printGraph();
        cout << endl;

        PrimMST(G);
    }

    return 0;
}
