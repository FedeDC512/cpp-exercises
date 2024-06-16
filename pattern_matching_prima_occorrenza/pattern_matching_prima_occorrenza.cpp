//Utilizzando la STD::vector class, implementare l’algoritmo KMP  che, dato un pattern ed un testo,
//trovi un’occorrenza del pattern nel testo (se esiste) e mandi in output la posizione iniziale di tale occorrenza.

#include <iostream>
#include <vector>
using namespace std;

// Costruisco il DFA per il pattern
vector<vector<int>> buildDFA(const string& pattern) {
    int m = pattern.length();
    const int ALPH = 256; // Usando l'alfabeto ASCII

    vector<vector<int>> dfa(ALPH, vector<int>(m, 0));
    dfa[pattern[0]][0] = 1;
    for (int x = 0, j = 1; j < m; j++) {
        for (int c = 0; c < ALPH; c++)
            dfa[c][j] = dfa[c][x]; // Copio i casi di mismatch
        dfa[pattern[j]][j] = j + 1; // Imposto il caso di match
        x = dfa[pattern[j]][x]; // Aggiorno lo stato di restart
    }
    return dfa;
}

// Eseguo il pattern matching KMP
vector<int> algKMP(const string& pattern, const string& text) {
    int m = pattern.length();
    int n = text.length();
    vector<vector<int>> dfa = buildDFA(pattern);
    vector<int> matches;
    
    for (int i = 0, j = 0; i < n; i++) {
        //cout << dfa[text[i]][j] << text[i] << " ";
        j = dfa[text[i]][j];
        if (j == m){ // Trovato un match
            matches.push_back(i - m + 1);
            j = 0;
        }
    }
    return matches;
}

int main() {
    string pattern = "abacab";
    string text = "abacaabaccabacabaabb";
    
    vector<int> occurrences = algKMP(pattern, text);
    if (occurrences.empty()) {
        cout << "Pattern non trovato." << endl;
    } else {
        cout << "Pattern trovato nelle seguenti posizioni: ";
        for (int pos : occurrences) {
            cout << pos << " ";
        }
    }
    return 0;
}
