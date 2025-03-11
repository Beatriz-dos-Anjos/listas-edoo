#include <iostream>

using namespace std;

class Node
{
public:
    Node *leftchild = nullptr;
    Node *rightchild = nullptr;
    int value;
};

class BinarySearchTree
{
private:
    Node *firstNode;

public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(int value);
    bool isEmpty();
    void printInOrder(Node *currentNode);
    void printPreOrder(Node *currentNode);
    void printPostOrder(Node *currentNode);
    void deleteBst(Node *currentNode);
    Node *getFirstNode();
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
    Node *NewNode = new Node();
    NewNode->value = value;
    NewNode->leftchild = nullptr;
    NewNode->rightchild = nullptr;
    if (isEmpty())
    {
        firstNode = NewNode;
        return;
    }
    else
    {
        Node *current = firstNode;
        while (current != nullptr)
        {
            if (value < current->value)
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
                if (current->rightchild == nullptr)
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

void BinarySearchTree::printPreOrder(Node *currentNode)
{
    if (currentNode != nullptr)
    {
        cout << currentNode->value;
        printPreOrder(currentNode->leftchild);
        printPreOrder(currentNode->rightchild);
    }
}

void BinarySearchTree::printInOrder(Node *currentNode)
{
    if (currentNode != nullptr)
    {
        printInOrder(currentNode->leftchild);
        cout << currentNode->value;
        printInOrder(currentNode->rightchild);
    }
}

void BinarySearchTree::printPostOrder(Node *currentNode)
{
    if (currentNode != nullptr)
    {
        printPostOrder(currentNode->leftchild);
        printPostOrder(currentNode->rightchild);
        cout << currentNode->value;
    }
}

void BinarySearchTree::deleteBst(Node *currentNode)
{
    if (currentNode != nullptr)
    {
        deleteBst(currentNode->leftchild);
        deleteBst(currentNode->rightchild);
        delete currentNode;
    }
}
BinarySearchTree::~BinarySearchTree()
{
    deleteBst(firstNode);
}

int main()
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