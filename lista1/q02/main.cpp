#include "iostream"
#include "string"
using namespace std;

struct Node
{
    char value;           // o input do usuario sera um char
    Node *next = nullptr; // ponteiros para o proximo node e o anterior sao nulos, pois o primeiro nó criado nao tem antecessor e o ultimo nao tem sucessor
    Node *previous = nullptr;
};

Node *head = nullptr; // ponteiro para o primeiro node da lista
Node *tail = nullptr; // ponteiro para o ultimo node da lista

// funcao ao encontrar [, inserindo elemento no início da lista
void insertNodeInit(char value)
{
    Node *newValue = new Node; // alocacao dinamica de memoria para um novo node
    newValue->value = value;
    if (head == nullptr)
    {
        head = newValue;
        tail = newValue;
    }
    else
    {
        newValue->next = head; // o proximo node do novo node eh o antigo primeiro node
        head->previous = newValue;
        head = newValue;
    }
}

// funcao ao encontrar ], inserir no final da lista
void insertNodeEnd(char value)
{
    Node *newValue = new Node;
    newValue->value = value;
    if (head == nullptr)
    {
        head = newValue;
        tail = newValue; // ja que so tem um elemento, ele eh o primeiro e o ultimo
    }
    else
    {
        newValue->previous = tail;
        tail->next = newValue;
        tail = newValue;
    }
}


//funcao para saber a quantidade de caracteres dentro da entrada string
int getLength(string entry){
    int length = 0;
    for ( int length; entry[length] != '\0'; length++){
        length++;
    }
    return length;
}

int main()
{
    std::string entry;
    cin >> entry;
    int lengthEntry = getLength(entry);
    for (int i = 0; i < lengthEntry; i++)
    {
        if (entry[i] == '[')
        {
            insertNodeInit(entry[i]);
        }
        else if (entry[i] == ']')
        {
            insertNodeEnd(entry[i]);
        }
    }


    return 0;
}