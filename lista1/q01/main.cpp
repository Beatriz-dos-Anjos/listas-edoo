#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* next; // Ponteiro para o próximo nó (linked list)
};

class Stack {
private:
    Node* top; // Ponteiro para o topo da pilha
public:
    Stack();
    ~Stack();
    void push(int value);
    int pop();
    void print();
    bool isEmpty();
};

// Implementação dos métodos

Stack::Stack() {
    top = nullptr; // A pilha começa vazia
}

Stack::~Stack() {
    Node* current = top; // O nó atual é o do topo
    while (current != nullptr) {
        Node* next = current->next; // O próximo nó é o próximo do atual
        delete current; // Deleta o atual
        current = next; // O nó atual vira o próximo
    }
}

void Stack::push(int value) {
    Node* newNode = new Node; // Alocação dinâmica
    newNode->value = value;
    newNode->next = top;
    top = newNode; // O nó criado é o topo
}

int Stack::pop() {
    if (isEmpty()) {
        cout << "Stack vazia" << endl;
        return 0;
    }  
    
    Node* temp = top; // Nó temporário recebe o topo
    int value = top->value;
    top = top->next;  // O topo vira o nó subsequente
    delete temp; // Deleta o nó temporário que estava guardando o então topo
    return value;
}

bool Stack::isEmpty() {
    return top == nullptr;
}

// Função principal
int equalStacks(int h1, int h2, int h3) {
    int size1 = 0, size2 = 0, size3 = 0, value = 0;
    vector<int> tempStack;  // Vetor para armazenar os valores antes de empilhar

    // Criando a Stack 1
    Stack s1;
    for (int i = 0; i < h1; i++) {
        cin >> value;
        tempStack.push_back(value);
    }
    for (int i = h1 - 1; i >= 0; i--) { // Empilha na ordem correta
        s1.push(tempStack[i]);
        size1 += tempStack[i];
    }
    tempStack.clear(); // Limpa o vetor para reutilizar

    // Criando a Stack 2
    Stack s2;
    for (int i = 0; i < h2; i++) {
        cin >> value;
        tempStack.push_back(value);
    }
    for (int i = h2 - 1; i >= 0; i--) { // Empilha na ordem correta
        s2.push(tempStack[i]);
        size2 += tempStack[i];
    }
    tempStack.clear(); // Limpa o vetor para reutilizar

    // Criando a Stack 3
    Stack s3;
    for (int i = 0; i < h3; i++) {
        cin >> value;
        tempStack.push_back(value);
    }
    for (int i = h3 - 1; i >= 0; i--) { // Empilha na ordem correta
        s3.push(tempStack[i]);
        size3 += tempStack[i];
    }
    tempStack.clear(); // Limpa o vetor

    bool isEqual = false; // Variável que guarda se as pilhas são iguais
    while (!isEqual) {
        if (size1 == size2 && size2 == size3) {
            isEqual = true;
            return size3;
        } else if (size1 > size2 && size1 > size3) {
            size1 -= s1.pop();
        } else if (size2 > size1 && size2 > size3) {
            size2 -= s2.pop();
        } else if (size3 > size1 && size3 > size2) {
            size3 -= s3.pop();
        } else if (size1 == size2 && size3 > size1) {
            size3 -= s3.pop();
        } else if (size1 == size3 && size2 > size1) {
            size2 -= s2.pop();
        } else if (size2 == size3 && size1 > size2) {
            size1 -= s1.pop();
        } else if (size1 == size2 && size1 > size3) {
            size1 -= s1.pop();
            size2 -= s2.pop();
        } else if (size1 == size3 && size1 > size2) {
            size1 -= s1.pop();
            size3 -= s3.pop();
        } else if (size2 == size3 && size2 > size1) {
            size2 -= s2.pop();
            size3 -= s3.pop();
        }

        if (size1 == 0 || size2 == 0 || size3 == 0) {
            return 0; // Pilhas vazias
        }
    }
    return 0;
}

int main() {
    int h1, h2, h3;
    cin >> h1 >> h2 >> h3;
    cout << equalStacks(h1, h2, h3) << endl;
    return 0;
}
