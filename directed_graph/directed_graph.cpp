/*Creare una classe DiGraph che implementi un grafo orientato, che, oltre ai metodi di inserimento di un arco,
ai costruttori e al metodo di stampa, crei anche il grafo reverse. Si implementino in particolare:
- il metodo INSERT_EDGE(v,u) che inserisce l’arco (v,u);
- un costruttore che, preso in input un parametro int V, inizializzi un grafo con V vertici e 0 archi;
- un costruttore che, preso in input un parametro ifstream in, crei un grafo a partire dalle informazioni contenute in un file di testo dato in input.*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class DiGraph {
private:
    int NumV;
    int NumE;
    vector<vector<int>> Adj;

public:
    // Costruttore per inizializzare un grafo con V vertici e 0 archi
    DiGraph(int V) : NumV(V), NumE(0), Adj(V) {}

    // Costruttore per creare un grafo da un file di testo
    DiGraph(ifstream& in) {
        in >> NumV;
        Adj.resize(NumV);
        in >> NumE;
        for (int i = 0; i < NumE; i++) {
            int v, u;
            in >> v >> u;
            INSERT_EDGE(v, u);
        }
    }

    // Metodo per inserire un arco (v, u)
    void INSERT_EDGE(int v, int u) {
        Adj[v].push_back(u);
        //Adj[u].push_back(v);
    }

    // Metodo per creare il grafo reverse
    DiGraph reverse() {
        DiGraph R(NumV);
        for (int v = 0; v < NumV; v++) {
            for (int u : Adj[v]) {
                R.INSERT_EDGE(u, v);
            }
        }
        return R;
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

int main() {
    ifstream input("C:\\Users\\fedea\\Documents\\Unipa Materie\\Laboratorio di Algoritmi\\C++\\directed_graph\\grafo.txt");
    if (!input.is_open()) {
        cout << "Errore durante l'apertura del file." << endl;
    } else {
        DiGraph G(input);
        G.printGraph();

        // Creazione del grafo reverse
        DiGraph R = G.reverse();
        cout << "Grafo reverse:" << endl;
        R.printGraph();
    }
    return 0;
}
