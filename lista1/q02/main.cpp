#include <iostream>
#include <string>

using namespace std;

struct Node
{
    char value;
    Node *next = nullptr;
    Node *previous = nullptr;
};
// lista duplamente ligada
Node *head = nullptr; // cabeca da lista
Node *tail = nullptr; // ultimo item da lsita

int caracteresCount(const string &entry)
{
    int count = 0;
    while (entry[count] != '\0') // Percorre até encontrar o caractere nulo
    {
        count++;
    }
    return count;
}
void insertNormalNode(char value, Node *&current) // funcao para inserir um novo node na lista, com o valor e o ponteiro para o proximo item da string
{
    Node *newValue = new Node; // noovo node a ser inserido
    newValue->value = value;

    if (head == nullptr) // primeiro node, caso a lista esteja vazia
    {
        head = newValue;
        tail = newValue;
        current = nullptr; // current eh null pois nao ha nenhum outro elemento na lsita paraa ser o proximo, em ambas as direcoes
    }
    else if (current == nullptr) // insercao apos o final, pois currrent == nullptr significa que o proximo item da string aponta para o final
    {
        newValue->previous = tail; // novo node sera adicionado apos o tail
        tail->next = newValue;
        tail = newValue;
    }
    else // insercao no meio
    {
        newValue->next = current;       // o novo node aponta para o proximo item , que eh o current
        Node *last = current->previous; // ponteiro temporario para guardaar o node anterior ao current
        newValue->previous = last;      // o novo node aponta para o node anterior ao current

        if (last != nullptr)
        {
            last->next = newValue;
        }
        else
        {
            head = newValue;
        }

        last = newValue;
    }
}

void printCharList(Node *node)
{
    if (node == nullptr)
    {
        cout << endl;
        return;
    }

    cout << node->value;
    printCharList(node->next); // chamada recursiva para continuar imprimindo os proximos elementos
}

int main()
{
    string entry;

    while (cin >> entry)
    {
        head = nullptr;
        tail = nullptr;
        Node *current = nullptr; // ponteiro para onde o proximo item da string aponta

        int size = caracteresCount(entry);

        for (int i = 0; i < size; i++)
        {
            char letter = entry[i]; // a letra analisada sempre sera a da iteracao atual

            if (letter == '[')
            {
                current = head; // se o caracter for '[', o current aponta para o inicio da lista, entao a insercao sera feita no inicio`
            }
            else if (letter != '[' && letter != ']') // insercao no meio
            {
                insertNormalNode(letter, current);
            }
            else if (letter == ']')
            {
                current = nullptr; // ja se o caracter for ']', o current aponta para o final da lista, entao a insercao sera feita no final
            }
        }

        printCharList(head);
    }

    return 0;
}
