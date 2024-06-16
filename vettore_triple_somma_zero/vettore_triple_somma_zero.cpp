//Scrivere un programma in C++ che, dato un vettore di interi allocato dinamicamente e riempito con valori casuali compresi tra -100 e 100, trovi il numero delle triple di elementi la cui somma è uguale a zero.
//Qual è la complessità di tempo della vostra soluzione? Esempio: 30, -40, -20, -10, 40, 0, 10, 5 Soluzione: 4

#include <iostream>

int max(int a, int b){
    int max = a;
    if (b > max) max = b;
    return max;
}

void stampaVettore(int *vettore, int lunghezza){
    if (vettore != nullptr){
        std::cout << "Il vettore è: ";
        for(int i = 0; i<lunghezza; i++){
            std::cout << vettore[i] << " ";
        }
    } else std::cout << "Il vettore è vuoto!";
}

int main(){
    int scelta;
    std::cout << "Inserisci"<< std::endl <<"1 se vuoi inserire i valori del vettore manualmente,"<< std::endl <<"2 se vuoi usare i valori di esempio dell'esercizio,"<< std::endl <<"3 se vuoi che i valori siano inseriti randomicamente:"<< std::endl;
    std::cin >> scelta;

    int lunghezza = 0;
    int *vettore = nullptr;
    int slide[] = {30, -40, -20, -10, 40, 0, 10, 5};

    switch(scelta) {
        case 1:
            std::cout << "Inserisci la lunghezza del vettore: ";
            std::cin >> lunghezza;
            vettore = new int [lunghezza]; 

            std::cout << "Inserisci " << lunghezza << " valori (separati da spazi): ";
            for (int i = 0; i < lunghezza; i++) {
                std::cin >> vettore[i];
            }

            break;
        case 2:
            lunghezza = 8;
            vettore = new int[lunghezza];

            for (int i = 0; i < lunghezza; i++) { //Copio i valori nell'array dinamico
                vettore[i] = slide[i];
            }

            break;
        case 3:
            std::cout << "Inserisci la lunghezza del vettore: ";
            std::cin >> lunghezza;
            vettore = new int [lunghezza]; 
            for(int i = 0; i<lunghezza; i++){
                vettore[i] = (1 + rand() % 200) -100; //Crea numeri casuali tra 1 e 200, poi sottrae 100 per avere numeri casuali tra -100 e +100
            }
            break;
        default:
            std::cout << "Scelta non valida" << std::endl;
    }

    stampaVettore(vettore, lunghezza);

    if (vettore != nullptr){
        //calcolo le triple
        int conteggioTriple = 0;
        for (int i = 0; i < lunghezza - 2; i++) {
            for (int j = i + 1; j < lunghezza - 1; j++) {
                for (int k = j + 1; k < lunghezza; k++) {
                    if (vettore[i] + vettore[j] + vettore[k] == 0) {
                        conteggioTriple++;
                    }
                }
            }
        }
        std::cout << std::endl << "Il numero di triple con somma zero nel vettore è: " << conteggioTriple << std::endl;
        /*La complessità di tempo di questo approccio è O(n^3), dove n è la lunghezza del vettore.
        Questo perché utilizzo tre cicli annidati per generare tutte le possibili triple di elementi nel vettore.
        Esistono anche altre strategie più efficienti con complessità minore, ad esempio utilizzando una mappa/hashmap
        per memorizzare le somme delle coppie di elementi nel vettore (complessità O(n^2)), oppure ordinando il vettore
        e utilizzando la tecnica dei due puntatori (complessità O(n^2)) per trovare le triple con somma zero.*/
    }
    
    delete[] vettore; //Dealloco il vettore
    return 0;
}