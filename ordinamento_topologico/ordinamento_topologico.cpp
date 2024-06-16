//Implementare l’ordinamento topologico di un grafo orientato,
//utilizzando a scelta il Reverse postorder oppure l’algoritmo alternativo.

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

class DiGraph {
private:
    int NumV;
    vector<vector<int>> adj;

public:
    DiGraph(int V) : NumV(V), adj(V) {}

    DiGraph(ifstream& in) {
        in >> NumV;
        adj.resize(NumV);
        int NumE;
        in >> NumE;
        for (int i = 0; i < NumE; i++) {
            int u, v;
            in >> u >> v;
            addEdge(u, v);
        }
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void reversePostOrder(int v, vector<bool>& visited, stack<int>& order) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u]) {
                reversePostOrder(u, visited, order);
            }
        }
        order.push(v);
    }

    stack<int> topologicalSort() {
        vector<bool> visited(NumV, false);
        stack<int> order;
        for (int v = 0; v < NumV; v++) {
            if (!visited[v]) {
                reversePostOrder(v, visited, order);
            }
        }
        return order;
    }

    void printGraph() {
        cout << NumV << " vertici" << endl;
        for (int v = 0; v < NumV; v++) {
            cout << v << ": ";
            for (int u : adj[v]) {
                cout << u << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    ifstream input("C:\\Users\\fedea\\Documents\\Unipa Materie\\Laboratorio di Algoritmi\\C++\\ordinamento_topologico\\grafo.txt");
    if (!input.is_open()) {
        cout << "Errore durante l'apertura del file." << endl;
    } else {
        DiGraph G(input);
        G.printGraph();

        stack<int> order = G.topologicalSort();
        cout << "Ordinamento topologico:" << endl;
        while (!order.empty()) {
            cout << order.top() << " ";
            order.pop();
        }
        cout << endl;
    }
    return 0;
}
