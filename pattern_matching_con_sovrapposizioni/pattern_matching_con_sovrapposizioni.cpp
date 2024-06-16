//Utilizzando la STD::vector class, implementare la variante dell’algoritmo KMP che, dato un pattern ed un testo,
//trovi tutte le occorrenze del pattern nel testo (anche quelle con sovrapposizioni)
//e mandi in output l’elenco delle posizioni iniziali di tali occorrenze.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Costruisco il DFA per il pattern
vector<vector<int>> buildDFA(const string& pattern) {
    int m = pattern.length();
    int R = 256; // Usando l'alfabeto ASCII

    vector<vector<int>> dfa(R, vector<int>(m, 0));
    dfa[pattern[0]][0] = 1;
    for (int X = 0, j = 1; j < m; j++) {
        for (int c = 0; c < R; c++)
            dfa[c][j] = dfa[c][X];
        dfa[pattern[j]][j] = j + 1;
        X = dfa[pattern[j]][X];
    }
    return dfa;
}

// Trovo tutte le occorrenze del pattern nel testo
vector<int> findOccurrences(const string& pattern, const string& text) {
    vector<int> occurrences;
    int m = pattern.length();
    int n = text.length();
    vector<vector<int>> dfa = buildDFA(pattern);
    
    for (int i = 0, j = 0; i < n; i++) {
        //cout << dfa[text[i]][j] << text[i] << " ";
        j = dfa[text[i]][j];
        if (j == m) {
            occurrences.push_back(i - m + 1);
            // Continuo a cercare dalla prossima posizione nel testo
            j = 1;
        }
    }
    return occurrences;
}

int main() {
    string pattern = "aba";
    string text = "ababababa";
    vector<int> result = findOccurrences(pattern, text);
    cout << "Occorrenze del pattern nelle seguenti posizioni: ";
    for (int pos : result) {
        cout << pos << " ";
    }
    cout << endl;
    return 0;
}
