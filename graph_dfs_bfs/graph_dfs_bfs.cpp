//Implementare DepthFirstSearch e BreadthFirstSearch in un grafo non orientato rappresentato con lista di adiacenze.
//Suggerimento: definirle come classi che usano la classe Graph

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int NumV;
    int NumE;
    vector<vector<int>> Adj; // Lista delle adiacenze

public:
    Graph(int V) : NumV(V), NumE(0), Adj(V) {}

    Graph(ifstream& in) {
        in >> NumV;
        Adj.resize(NumV);
        in >> NumE;
        for (int i = 0; i < NumE; i++) {
            int v, u;
            in >> v >> u;
            INSERT_EDGE(v, u);
        }
    }

    void INSERT_EDGE(int v, int u) {
        Adj[v].push_back(u);
        Adj[u].push_back(v);
    }

    vector<int> NEIGHBOURS(int v) {
        return Adj[v];
    }

    // Metodo per ottenere il numero di vertici
    int V() {
        return NumV;
    }

    void printGraph() {
        cout << NumV << " vertici, " << NumE << " archi" << endl;
        for (int v = 0; v < NumV; v++) {
            cout << v << ": ";
            for (int u : Adj[v]) {
                cout << u << " ";
            }
            cout << endl;
        }
    }
};

// Classe per eseguire Depth First Search
class DepthFirstSearch {
private:
    vector<bool> marked; // Array per marcare i nodi visitati
    vector<int> edgeTo; // Array per tenere traccia degli archi usati per raggiungere i nodi

    void dfs(Graph& G, int v) {
        marked[v] = true;
        for (int w : G.NEIGHBOURS(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, w);
            }
        }
    }

public:
    DepthFirstSearch(Graph& G, int s) : marked(G.V(), false), edgeTo(G.V()) {
        dfs(G, s);
    }

    bool isMarked(int v) {
        return marked[v];
    }

    int edgeToVertex(int v) {
        return edgeTo[v];
    }
};

// Classe per eseguire Breadth First Search
class BreadthFirstSearch {
private:
    vector<bool> marked; // Array per marcare i nodi visitati
    vector<int> edgeTo; // Array per tenere traccia degli archi usati per raggiungere i nodi
    vector<int> distTo; // Array per tenere traccia delle distanze dai nodi

public:
    BreadthFirstSearch(Graph& G, int s) : marked(G.V(), false), edgeTo(G.V()), distTo(G.V(), INT_MAX) {
        queue<int> q;
        distTo[s] = 0;
        marked[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : G.NEIGHBOURS(v)) {
                if (!marked[w]) {
                    edgeTo[w] = v;
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    q.push(w);
                }
            }
        }
    }

    bool isMarked(int v) {
        return marked[v];
    }

    int distanceTo(int v) {
        return distTo[v];
    }

    int edgeToVertex(int v) {
        return edgeTo[v];
    }
};

int main() {
    ifstream input("C:\\Users\\fedea\\Documents\\Unipa Materie\\Laboratorio di Algoritmi\\C++\\graph_dfs_bfs\\grafo.txt");
    if (!input.is_open()) {
        cout << "Errore durante l'apertura del file." << endl;
    } else {
        Graph g(input);
        g.printGraph();

        int startVertex = 0; // Vertice di partenza per la ricerca

        // Depth First Search
        DepthFirstSearch dfs(g, startVertex);
        cout << "DFS:" << endl;
        for (int v = 0; v < g.V(); v++) {
            if (dfs.isMarked(v)) {
                cout << startVertex << " to " << v << " via " << dfs.edgeToVertex(v) << endl;
                //Es: vado dal vertice 0 al vertice 1 attraverso il vertice 0
            }
        }

        // Breadth First Search
        BreadthFirstSearch bfs(g, startVertex);
        cout << "BFS:" << endl;
        for (int v = 0; v < g.V(); v++) {
            if (bfs.isMarked(v)) {
                cout << startVertex << " to " << v << " via " << bfs.edgeToVertex(v) << " at distance " << bfs.distanceTo(v) << endl;
                //Es: vado dal vertice 0 al vertice 2 attraverso il vertice 1 e la distanza tra il vertice 0 e il vertice 2 è 2
            }
        }
    }
    return 0;
}
