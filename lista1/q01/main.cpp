#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node // aqui escolhi fazer estrutura de lista liagada para a pilha, com um node que guarda um valor e um ponteiro para o proximo node
{
    int value;
    Node *next; // ponteiro para o proximo node
};

class Stack
{
private:
    Node *top; // ponteiro do tipo node que aponta  o topo da pilha
public:
    Stack();
    ~Stack();
    void push(int value);
    int pop();
    void print();
    bool isEmpty();
};

//implementacao dos metodos

Stack::Stack()
{
    top = nullptr; // a pilha comeca vaiza
}

Stack::~Stack()
{
    Node *current = top; // O node atual torna se o topo
    while (current != nullptr)
    {
        Node *next = current->next; // O node seguinte e o proximo do atual
        delete current;             // deleta o atual
        current = next;             // O node atual vira o proximo
    }
}

void Stack::push(int value)
{
    Node *newNode = new Node; // alocacao dinamica da memoria criando um novo node
    newNode->value = value;
    newNode->next = top;
    top = newNode; // o node criado vira o topo
}

int Stack::pop()
{
    if (isEmpty())
    {
        cout << "Stack vazia" << endl;
        return 0;
    }

    Node *temp = top; //node temporario que guarda o topo
    int value = top->value;
    top = top->next; // o topo vira o proximo
    delete temp;     // deleta o node temporario
    return value;
}

bool Stack::isEmpty()
{
    return top == nullptr;
}

// Funcao principal
int equalStacks(int h1, int h2, int h3) // segundo os parametros
{   
    // aqui embaixo quis criar 3 tamanhos, um para cada pilha
    int size1 = 0;
    int size2 = 0;
    int size3 = 0;
    int value = 0;

    Stack s1;
    // preferi lidar com vetores para a entrada dos dados das alturas de cada pilha, por isso ha um loop  que itera sobre o tamanho de cada pilha
    vector<int> StackRepresentation1;
    // loop dee adicao dos valores de cada pilha, que lida com a entrada
    for (int i = 0; i < h1; i++)
    {
        cin >> value;
        StackRepresentation1.push_back(value);
    }
    // loop que adiciona os valores de cada pilha na pilha, porem com a ordem correta ( o topo da pilha e o primeiro valor)
    for (int i = h1 - 1; i >= 0; i--)
    {
        s1.push(StackRepresentation1[i]);
        size1 += StackRepresentation1[i];
    }

    // as mesmas logicas sao aplicadas para as outras pilhas
    Stack s2;
    vector<int> StackRepresentation2;
    for (int i = 0; i < h2; i++)
    {
        cin >> value;
        StackRepresentation2.push_back(value);
    }
    for (int i = h2 - 1; i >= 0; i--)
    {
        s2.push(StackRepresentation2[i]);
        size2 += StackRepresentation2[i];
    }

    Stack s3;
    vector<int> StackRepresentation3;
    for (int i = 0; i < h3; i++)
    {
        cin >> value;
        StackRepresentation3.push_back(value);
    }
    for (int i = h3 - 1; i >= 0; i--)
    {
        s3.push(StackRepresentation3[i]);
        size3 += StackRepresentation3[i];
    }

    // agora, a logica de comparacao das altura das pilhas
    bool isEqual = false; // Variavel que guarda se as pilhas sao iguais como falso
    while (!isEqual)
    {
        if (size1 == size2 && size2 == size3)
        {
            isEqual = true;
            return size3;
        }
        else if (size1 > size2 && size1 > size3)
        {
            size1 -= s1.pop();
        }
        else if (size2 > size1 && size2 > size3)
        {
            size2 -= s2.pop();
        }
        else if (size3 > size1 && size3 > size2)
        {
            size3 -= s3.pop();
        }
        else if (size1 == size2 && size3 > size1)
        {
            size3 -= s3.pop();
        }
        else if (size1 == size3 && size2 > size1)
        {
            size2 -= s2.pop();
        }
        else if (size2 == size3 && size1 > size2)
        {
            size1 -= s1.pop();
        }
        else if (size1 == size2 && size1 > size3)
        {
            size1 -= s1.pop();
            size2 -= s2.pop();
        }
        else if (size1 == size3 && size1 > size2)
        {
            size1 -= s1.pop();
            size3 -= s3.pop();
        }
        else if (size2 == size3 && size2 > size1)
        {
            size2 -= s2.pop();
            size3 -= s3.pop();
        }

        if (size1 == 0 || size2 == 0 || size3 == 0)
        {
            return 0; // tratmento com pilha vazia
        }
    }
    return 0;
}

int main()
{
    int h1, h2, h3;
    cin >> h1 >> h2 >> h3;
    cout << equalStacks(h1, h2, h3) << endl;
    return 0;
}
