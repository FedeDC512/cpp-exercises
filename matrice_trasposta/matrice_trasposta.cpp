//Scrivere un programma in C++ che calcoli la trasposta di una matrice quadrata e visualizzi tale matrice

#include <iostream>

void stampaMatrice(int **matrice, int dimensione){
    if (matrice != nullptr){
        for(int i = 0; i<dimensione; i++){
            for (int j = 0; j<dimensione; j++){
                std::cout << matrice[i][j] << " ";
            }
            std::cout << std::endl;
        }
    } else std::cout << "La matrice è vuota!";
}

int main(){
    int scelta;
    std::cout << "Inserisci"<< std::endl <<"1 se vuoi inserire i valori della matrice manualmente,"<< std::endl <<"2 se vuoi che i valori siano inseriti randomicamente:"<< std::endl;
    std::cin >> scelta;

    int dimensione = 0;
    int **matrice = nullptr;
    if (scelta == 1 || scelta ==2){
        std::cout << "Inserisci la dimensione della matrice quadrata: ";
        std::cin >> dimensione;

        matrice = new int*[dimensione]; // Alloco le righe
        for (int i = 0; i < dimensione; i++) {
            matrice[i] = new int[dimensione]; // Alloco le colonne per ogni riga
        }
    }

    switch(scelta) {
        case 1:
            std::cout << "Inserisci " << dimensione*dimensione << " valori (separati da spazi): ";
            for (int i = 0; i < dimensione; i++) {
                for (int j = 0; j<dimensione; j++){
                    std::cin >> matrice[i][j];
                }
            }

            break;
        case 2:
            for (int i = 0; i < dimensione; i++) {
                for (int j = 0; j<dimensione; j++){
                    matrice[i][j] = rand() % 9; //Crea numeri casuali tra 0 e 9
                }
            }
            break;
        default:
            std::cout << "Scelta non valida" << std::endl;
    }

    if (matrice != nullptr){
        std::cout << "La matrice è: " << std::endl;
        stampaMatrice(matrice, dimensione);

        for (int i = 0; i < dimensione; i++) {
            for (int j = 0; j < i; j++){ //Scambio solo gli elementi sopra la diagonale principale
                int temp = matrice[i][j];
                matrice[i][j] = matrice[j][i];
                matrice[j][i] = temp;
            }
        }

        std::cout << "La sua trasposta è: " << std::endl;
        stampaMatrice(matrice, dimensione);
    }

    for (int i = 0; i < dimensione; i++) {
        delete[] matrice[i]; // Dealloco le colonne per ogni riga della matrice
    }
    delete[] matrice; // Dealloco le righe della matrice
    return 0;
}