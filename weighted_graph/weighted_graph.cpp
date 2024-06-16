/*Un grafo pesato viene rappresentato come un grafo non orientato in cui per ogni nodo si ha una lista di archi (o di puntatori ad archi).
Gli archi pesati possono essere rappresentati memorizzando i nodi che incidono sull’arco (numeri interi) ed il peso (numero reale).
Creare una classe WeightedGraph che implementi un grafo pesato, che dovrà contenere i metodi:
- addEdge, che aggiunge un arco (u,v) di peso w al grafo;
- Adj(v), che restituisce tutti i vertici adiacenti a v;
- un costruttore WeightedGraph(V) che crea un grafo pesato vuoto con V vertici;
- un costruttore  che costruisce un grafo a partire da un file in input.*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class WeightedGraph {
private:
    int V;
    vector<vector<pair<int, double>>> adj;

public:
    // Costruttore per creare un grafo pesato vuoto con V vertici
    WeightedGraph(int V) : V(V), adj(V) {}

    // Costruttore per creare un grafo pesato da un file di input
    WeightedGraph(ifstream& in) {
        in >> V;
        adj.resize(V);
        int E;
        in >> E;
        for (int i = 0; i < E; i++) {
            int u, v;
            double w;
            in >> u >> v >> w;
            addEdge(u, v, w);
        }
    }

    // Metodo per aggiungere un arco (u, v) di peso w al grafo
    void addEdge(int u, int v, double w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Perché il grafo è non orientato
    }

    // Metodo per restituire tutti i vertici adiacenti a v
    vector<pair<int, double>>& Adj(int v) {
        return adj[v];
    }

    void printGraph() {
        cout << "Grafo Pesato:" << endl;
        for (int v = 0; v < V; v++) {
            cout << v << ": ";
            for (auto& neighbor : adj[v]) {
                cout << neighbor.first << " (peso: " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    ifstream input("C:\\Users\\fedea\\Documents\\Unipa Materie\\Laboratorio di Algoritmi\\C++\\weighted_graph\\grafo.txt");
    if (!input.is_open()) {
        cout << "Errore durante l'apertura del file." << endl;
    } else {
        WeightedGraph G(input);
        G.printGraph();
    }
    return 0;
}
