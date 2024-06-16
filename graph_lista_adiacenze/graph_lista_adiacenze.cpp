/*Creare una classe Graph che implementi un grafo rappresentato con una lista di adiacenze.
In particolare, tale classe deve contenere almeno i seguenti attributi e funzioni:
1. NumV e NumE che memorizzano il numero dei vertici e degli archi
2. Adj che rappresenta la lista delle adiacenze
3. Un costruttore Graph(int V) che inizializza un grafo con V vertici e 0 archi.
4. Un costruttore Graph(ifstream in) che crea un grafo a partire dalle informazioni contenute in un file di testo dato in input
5. Un costruttore Graph(Graph& g) che crea una copia di un grafo g
6. Un metodo INSERT_EDGE(v,u) che inserisce l’arco (v,u)
7. Un metodo ADJACENT(v,u) che verifica se due vertici sono adiacenti
8. Un metodo NEIGHBOURS(v) che restituisce la lista dei nodi adiacenti a v
9. Un metodo degree(v) che calcola il grado di un nodo v
10. Un metodo printGraph che stampa il grafo nella seguente forma:
4 vertici, 10 archi
0: 1 3
1: 0 2 3
2: 1 3
3: 0 1 2 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Graph {
private:
    int NumV; // Numero di vertici
    int NumE; // Numero di archi
    vector<vector<int>> Adj; // Lista delle adiacenze

public:
    // Costruttore per inizializzare un grafo con V vertici e 0 archi
    Graph(int V) : NumV(V), NumE(0), Adj(V) {}

    // Costruttore per creare un grafo da un file di testo
    Graph(ifstream& in) {
        in >> NumV;
        cout << "Numero di vertici letti: " << NumV << endl; // Print di debug
        Adj.resize(NumV);
        in >> NumE;
        cout << "Numero di archi letti: " << NumE << endl; // Print di debug
        for (int i = 0; i < NumE; i++) {
            int v, u;
            in >> v >> u;
            cout << "Lettura arco " << i + 1 << ": " << v << " -> " << u << endl; // Print di debug
            INSERT_EDGE(v, u);
        }
        cout << endl;
    }

    // Costruttore per creare una copia di un grafo g
    Graph(const Graph& g) : NumV(g.NumV), NumE(g.NumE), Adj(g.Adj) {}

    // Metodo per inserire un arco (v, u)
    void INSERT_EDGE(int v, int u) {
        Adj[v].push_back(u);
        Adj[u].push_back(v);
    }

    // Metodo per verificare se due vertici sono adiacenti
    bool ADJACENT(int v, int u) {
        for (int neighbor : Adj[v]) {
            if (neighbor == u)
                return true;
        }
        return false;
    }

    // Metodo per ottenere la lista dei nodi adiacenti a v
    vector<int> NEIGHBOURS(int v) {
        return Adj[v];
    }

    // Metodo per calcolare il grado di un nodo v
    int degree(int v) {
        return Adj[v].size();
    }

    // Metodo per stampare il grafo
    void printGraph() {
        cout << NumV << " vertici, " << NumE << " archi" << endl;
        if (NumE == 0) {
            cout << "Il grafo è vuoto." << endl;
            return;
        }
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

    ifstream input("C:\\Users\\fedea\\Documents\\Unipa Materie\\Laboratorio di Algoritmi\\C++\\graph_lista_adiacenze\\grafo.txt");
    if (!input.is_open()) {
        cout << "Errore durante l'apertura del file." << endl;
    } else {
        Graph g(input);
        g.printGraph();
    }
    return 0;
}
