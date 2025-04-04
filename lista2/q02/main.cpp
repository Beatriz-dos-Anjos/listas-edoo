#include <iostream>

using namespace std;

class Node  //criacao da classe Node para representar os nos da arvore binaria de busca com os atributos dos dois unicos filhos e valor
{
public:
    Node *leftchild = nullptr;
    Node *rightchild = nullptr;
    int value;
};

class BinarySearchTree
{
private:
    Node *firstNode;   // o primeiro node da arvore raiz sendo criado do tipo Node

public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(int value);
    bool isEmpty();
    void printInOrder(Node *currentNode);
    void printPreOrder(Node *currentNode);
    void printPostOrder(Node *currentNode);
    void deleteBst(Node *currentNode);
    Node *getFirstNode();  //metodo getter que acessa o primeiro node da arvore na situacao x em questao
};

BinarySearchTree::BinarySearchTree()
{
    firstNode = nullptr;
}

bool BinarySearchTree::isEmpty()
{
    return (firstNode == nullptr);
}
Node *BinarySearchTree::getFirstNode()
{
    return firstNode;
}
void BinarySearchTree ::insert(int value)
{
    Node *NewNode = new Node(); //criacao de um novo no por alocacao dinamica de memoria
    NewNode->value = value; // esse novo node vai ter o valor passado como parametro
    NewNode->leftchild = nullptr;
    NewNode->rightchild = nullptr;
    if (isEmpty())
    {
        firstNode = NewNode; // caso a arvore esteja vazia o primeiro node vai ser o novo node
        return;
    }
    else
    {
        Node *current = firstNode; // cria um node atual temporario  que vai ser o primeiro node da arvore
        while (current != nullptr)
        {
            if (value < current->value) // se o valor passado for menor que o valor do node atual ele vai para a esquerda
            {
                if (current->leftchild == nullptr)
                {
                    current->leftchild = NewNode;
                    return;
                }
                else
                {
                    current = current->leftchild;
                }
            }
            else 
            { 
                if (current->rightchild == nullptr) // se o valor passado for maior que o valor do node atual ele vai para a direita
                {
                    current->rightchild = NewNode;
                    return;
                }
                else
                {
                    current = current->rightchild;
                }
            }
        }
    }
}

void BinarySearchTree::printPreOrder(Node *currentNode) //metodo que imprime a arvore em pre ordem 
{
    if (currentNode != nullptr)
    {
        cout << currentNode->value;
        printPreOrder(currentNode->leftchild); //chama recursivamente o metodo
        printPreOrder(currentNode->rightchild);
    }
}

void BinarySearchTree::printInOrder(Node *currentNode) //metodo que imprime a arvore em ordem
{
    if (currentNode != nullptr)
    {
        printInOrder(currentNode->leftchild); //chama recursivamente o metodo
        cout << currentNode->value;
        printInOrder(currentNode->rightchild);
    }
}

void BinarySearchTree::printPostOrder(Node *currentNode) //metodo que imprime a arvore em pos ordem
{
    if (currentNode != nullptr)
    {
        printPostOrder(currentNode->leftchild); //chama recursivamente o metodo
        printPostOrder(currentNode->rightchild);
        cout << currentNode->value;
    }
}

void BinarySearchTree::deleteBst(Node *currentNode) //metodo que deleta a arvore
{
    if (currentNode != nullptr)
    {
        deleteBst(currentNode->leftchild); // chama recursivamente o metodo para deletar os nodes da arvore sem erros na posicao dos ponteiros apos alteracao
        deleteBst(currentNode->rightchild);
        delete currentNode;
    }
}
BinarySearchTree::~BinarySearchTree() //destrutor
{
    deleteBst(firstNode); //chama o metodo deleteBst para deletar a arvore
}

int main() // funcao prinicpal para printar 
{
    BinarySearchTree binarySearchTree;
    int qtdNumb;
    cin >> qtdNumb;
    for (int i = 0; i < qtdNumb; i++)
    {
        int value;
        cin >> value;
        binarySearchTree.insert(value);
    }
    cout << "Pre order : ";
    binarySearchTree.printPreOrder(binarySearchTree.getFirstNode());
    cout << endl;
    cout << "In order  : ";

    binarySearchTree.printInOrder(binarySearchTree.getFirstNode());
    cout << endl;

    cout << "Post order:";

    binarySearchTree.printPostOrder(binarySearchTree.getFirstNode());
}