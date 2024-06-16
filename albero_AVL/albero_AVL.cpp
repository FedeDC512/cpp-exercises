//Definire una classe per gli alberi AVL in cui il contenuto informativo di ogni nodo sia un intero. 
//Definire in modo opportuno i metodi per l’inserimento, la ricerca e la cancellazione di un nodo.
//Esplicitare il contenuto di tali metodi.

#include <iostream>
#include <algorithm>

struct avlNode {
    int inf;
    int h;
    struct avlNode* dx;
    struct avlNode* sx;
};

class avlTree {
public:
    void insert(int x) {
        insertNode(root, x);
    }

    void inOrderTraversal() const {
        inOrderTraversal(root);
    }

    int height() const {
        return height(root);
    }

private:
    avlNode* root = nullptr;

    void insertNode(avlNode* &node, int &x) {
        if (node == nullptr) {
            node = new avlNode;
            node->inf = x;
            node->h = 1;
            node->sx = nullptr;
            node->dx = nullptr;
        } else if (x < node->inf) {
            insertNode(node->sx, x);
        } else if (x > node->inf) {
            insertNode(node->dx, x);
        }

        // Aggiornamento dell'altezza
        node->h = std::max(height(node->sx), height(node->dx)) + 1;
        
        // Bilanciamento dell'albero dopo l'inserimento
        balance(node);
    }

    int height(avlNode* node) const {
        return node ? node->h : 0;
    }

    void inOrderTraversal(avlNode* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->sx);
            std::cout << node->inf << " ";
            inOrderTraversal(node->dx);
        }
    }

    void rotateRight(avlNode* &node) {
        avlNode* temp = node->sx;
        node->sx = temp->dx;
        temp->dx = node;
        node->h = std::max(height(node->sx), height(node->dx)) + 1;
        temp->h = std::max(height(temp->sx), node->h) + 1;
        node = temp;
    }

    void rotateLeft(avlNode*& node) {
        avlNode* temp = node->dx;
        node->dx = temp->sx;
        temp->sx = node;
        node->h = std::max(height(node->sx), height(node->dx)) + 1;
        temp->h = std::max(height(temp->dx), node->h) + 1;
        node = temp;
    }

    void balance(avlNode*& node) {
        if (node == nullptr) return;

        int balanceFactor = height(node->dx) - height(node->sx);

        if (balanceFactor > 1) {
            if (height(node->dx->sx) > height(node->dx->dx)) {
                rotateRight(node->dx);
            }
            rotateLeft(node);
        } else if (balanceFactor < -1) {
            if (height(node->sx->dx) > height(node->sx->sx)) {
                rotateLeft(node->sx);
            }
            rotateRight(node);
        }
    }
};

int main() {
    avlTree tree;

    //Inserisco i valori dell'esercizio delle slide
    tree.insert(10);
    tree.insert(5);
    tree.insert(100);
    tree.insert(175);
    tree.insert(180);
    tree.insert(25);

    std::cout << "InOrder Traversal: ";
    tree.inOrderTraversal();
    std::cout << std::endl;

    std::cout << "Tree Height: " << tree.height() << std::endl;

    return 0;
}
