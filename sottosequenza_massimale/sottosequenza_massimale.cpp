//Implementare in C++ gli algoritmi per calcolare la sottosequenza massimale di un vettore, allocato dinamicamente

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

int sottosequenza_massimale(int *vettore, int lunghezza){
    int maxSoFar = 0;
    int maxEndingHere = 0;
    std::cout << std::endl << std::endl << "maxEndingHere | maxSoFar" << std::endl;
    for(int i = 0; i< lunghezza; i++){
        maxEndingHere = max(0, maxEndingHere + vettore[i]); //se somma negativa, resetta a zero
        maxSoFar = max(maxSoFar, maxEndingHere); 
        std::cout << maxEndingHere << " | " << maxSoFar << std::endl;
    }
    return maxSoFar;
}

int main(){
    int scelta;
    std::cout << "Inserisci"<< std::endl <<"1 se vuoi inserire i valori del vettore manualmente,"<< std::endl <<"2 se vuoi usare i valori di esempio delle slide,"<< std::endl <<"3 se vuoi che i valori siano inseriti randomicamente:"<< std::endl;
    std::cin >> scelta;

    int lunghezza = 0;
    int *vettore = nullptr;
    int slide[] = {1, 3, 4, -9, 2, 3, -1, 3, 4, -3, 10, -3, 2};

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
            lunghezza = 13;
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
        int sottosequenzaMax = sottosequenza_massimale(vettore, lunghezza);
        std::cout << std::endl << "La sottosequenza massimale del vettore è " << sottosequenzaMax;
    }
    
    delete[] vettore; //Dealloco il vettore
    return 0;
}