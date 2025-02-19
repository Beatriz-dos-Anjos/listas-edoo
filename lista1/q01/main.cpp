#include <iostream>
#include <string>

using namespace std;

struct Node {
    int value;
    Node* next; //ponteiro para o próximo nó (linked list)
};

class Stack{
    private:
        Node* top; //ponteiro para o topo da pilha
    public:
        Stack();
        ~Stack();
        void push(int value);
        int pop();
        void print();
};

//implementação dos métodos

Stack::Stack(){
    top = nullptr; // a pilha começa vazia
}

Stack::~Stack(){ 
    Node* current = top; // o nó atual é o do topo
    while(current != 0){
        Node* next = current->next; // o próximo nó é o próximo do atual
        delete current; // deleta o atual
        current = next; // o nó atual virá o próximo
    }
}

void Stack::push(int value){
    Node* newNode = new Node; // alocacao dinamica
    newNode->value = value; 
    newNode->next = top; 
    top = newNode; // o nó criado é o topo
}

int Stack::pop(){
    if(top == 0){
        cout << "Stack vazisa" << endl;
        return 0;
    }
    Node* temp = top; // nó temporário recebe o topo
    int value = top->value;
    top = top->next;  // o topo vira o nó subsequente
    delete temp; // deleta o nó temporário que estava guardando o então topo
    return value;
}

void Stack::print(){
    Node* current = top; // o nó atual é o do topo
    while(current){
        cout << current->value << " ";
        current = current->next; // o nó atual vira o próximo
    }
    cout << endl;
}

//funcao principal
int equalStacks(int h1, int h2, int h3){
    // valores inteiros que guardarão os tamanhos das pilhas
    int size1=0;
    int size2=0;
    int size3=0;
    int value=0;
    Stack s1;
    for (int i=0; i<h1; i++){
        cin >> value;
        s1.push(value);
        size1+=value;
    }
    Stack s2;
    for (int i=0; i<h2; i++){
        cin >> value;
        s2.push(value);
        size2+=value;
    }
    Stack s3;
    for (int i=0; i<h3; i++){
        cin >> value;
        s3.push(value);
        size3+=value;
    }
    
    bool isEqual = false; // variável que guarda se as pilhas são iguais
    while (!isEqual){
        if (size1==size2 && size2==size3){
            isEqual = true;
            return size3;
        } else if (size1>size2 && size2>size3){
            size1-=s1.pop();
        } else if (size2>size1 && size2>size3){
            size2-=s2.pop();
        } else if (size3>size1 && size3>size2){
            size3-=s3.pop();
        } else if (size1==size2 && size3>size1){
            size3-=s3.pop();
        } else if (size1==size3 && size2>size1){
            size2-=s2.pop();
        } else if (size2==size3 && size1>size2){
            size1-=s1.pop();
        } else if (size1==size2 && size1>size3){
            size1= size1-s1.pop();
            size2= size2-s2.pop();
        } else if (size1==size3 && size1>size2){
            size1= size1-s1.pop();
            size3= size3-s3.pop();
        } else if (size2==size3 && size2>size1){
            size2= size2-s2.pop();
            size3= size3-s3.pop();
        } else if (size1==0||size2==0||size3==0){
            return 0; // pilhas vazias
        }
    }
};

int main(){
    int h1;
    int h2;
    int h3;
    cin >> h1 >> h2 >> h3;
    cout << equalStacks(h1, h2, h3) << endl;
    return 0;
}; 