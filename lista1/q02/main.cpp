#include <iostream>
#include <string>

using namespace std;

struct Node
{
    char value;
    Node *next = nullptr;
    Node *previous = nullptr;
};

Node *head = nullptr;
Node *tail = nullptr;

void insertNormalNode(char value, Node *&insertPos)
{
    Node *newValue = new Node;
    newValue->value = value;

    if (head == nullptr) // Lista vazia, cria o primeiro nó
    {
        head = newValue;
        tail = newValue;
        insertPos = nullptr; // Depois da primeira inserção, inserir no final por padrão
    }
    else if (insertPos == nullptr) // Inserção no final
    {
        newValue->previous = tail;
        tail->next = newValue;
        tail = newValue;
    }
    else // Inserção no início ou no meio
    {
        newValue->next = insertPos;
        newValue->previous = insertPos->previous;

        if (insertPos->previous != nullptr)
        {
            insertPos->previous->next = newValue;
        }
        else
        {
            head = newValue; // Atualiza `head` corretamente
        }

        insertPos->previous = newValue;
    }
}

void liberarMemoria()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
}

int main()
{
    string entry;

    while (cin >> entry)
    {
        head = nullptr;
        tail = nullptr;
        Node *insertPos = nullptr; // Posição onde os caracteres serão inseridos

        for (char ch : entry)
        {
            if (ch == '[')
            {
                insertPos = head; // Sempre insere no início quando `[`
            }
            else if (ch == ']')
            {
                insertPos = nullptr; // Muda a inserção para o final
            }
            else
            {
                insertNormalNode(ch, insertPos);
            }
        }

        // Impressão correta mantendo a ordem original dos caracteres
        Node *tempPrint = head;
        while (tempPrint != nullptr)
        {
            cout << tempPrint->value;
            tempPrint = tempPrint->next;
        }
        cout << endl;

    }

    return 0;
}
