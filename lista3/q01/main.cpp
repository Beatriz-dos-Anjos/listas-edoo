#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node
{
public:
    int data; // node da pilha implementada como linked list
    Node *next;
};

class StackedItUp // aqui eh feita a classe StackedItUp que implementa a pilha
{
private: // ela tem um ponteiro para o topo da pilha e uma string de instrucoes
    Node *topo;
    string instructions;
    int bottom;

public:
    StackedItUp();
    ~StackedItUp();
    void packedItUp(int valorDesejado, int correcao); // empilha o valor desejado e aplica a correcao, com base na entrada
    void joinOneAndPlus(int target);                  // na pilha, insere 1 e depois soma o restante
    void doubleLast();                                // duplica o ultimo valor da pilha
    void joinAndMinus();                              // remove os dois primeiros valores da pilha e diminui os restantes
    void insertComand(const string &line);            // insere o comando na string de instrucoes
    void push(int v);                                 // add um valor no topo da pilha
    int pop();                                        // remove o valor do topo da pilha
    string getDatas();                                // retorna a string de instrucoes
    string mainLogic(const vector<int> &input);
    int plusTimes(int val);
};

int StackedItUp::plusTimes(int val) //  logica necessaria por conta do index
{
    return val - 1;
}

string StackedItUp::mainLogic(const vector<int> &input) // aqui consta a logica principal
{
    int n = input.size();
    vector<int> accuracy(n, 0); // implementei um vetor para guardar os valores que
    vector<int> plus(n, 0);

    accuracy[0] = input[n - 1];       // vetor que guarda o resultado apos todas as operacoes para ver se eh igual a entrada
    plus[0] = plusTimes(accuracy[0]); // aqui eh feita a contagem de + necessarios

    for (int i = 1; i < n; ++i)
    {
        int index = n - 1 - i; // fazendo a logica da pilha, de acessar os inputs de cima pra baixo
        int soma = 0;
        for (int t = 0; t < i; ++t) // verifca quantos + foram somados ja que impacta na estrutura
            soma += plus[t];
        accuracy[i] = input[index] + soma;
        plus[i] = plusTimes(accuracy[i]); // aqui eh feita a contagem de + necessarios ate ajustar o valor
    }

    StackedItUp packed;

    for (int i = n - 1; i >= 0; --i) // constrcao na pilha
    {
        packed.packedItUp(input[i], accuracy[i] - input[i]); // ao chamar a funcao, faz as operacoes necessarias de duplicar e/ou ajustar
    }

    return packed.getDatas();
}

StackedItUp::StackedItUp() // construtor
{
    topo = nullptr;
    instructions = "";
    bottom = -100000; // valor escolhido pois nao pode ser um valor de entrada e topo
}

string StackedItUp::getDatas()
{
    return instructions;
}
StackedItUp::~StackedItUp() // destruct
{
    while (topo)
    {
        Node *temporaryNode = topo;
        topo = topo->next;
        delete temporaryNode; // libera a memoria
    }
}

void StackedItUp::packedItUp(int temporaryValue, int correcao) // eh a funcao chamada
{
    int finalValue = temporaryValue + correcao;

    if (temporaryValue == bottom) // caso os valores tenham sido iguais, apenas chama a funcao de duplicar
    {
        doubleLast();
        return;
    }

    joinOneAndPlus(finalValue); // caso nao, aplica a funcao de empilhar e subtrairr
    bottom = temporaryValue;
}

void StackedItUp::joinOneAndPlus(int target) // estruturar o numero ja com a estrutura necessaria
{
    if (target <= 0)
        return;
    insertComand("1");
    push(1);

    for (int i = 1; i < target; ++i)
    {
        insertComand("1");
        push(1);
        insertComand("+");
        joinAndMinus();
    }
}

void StackedItUp::doubleLast() // se os valores forem iguais, duplica o topo
{
    if (!topo)
        return;
    int doubled = topo->data;
    insertComand("d"); // acao que eh representada pelo comando d
    Node *newNode = new Node{doubled, topo};
    topo = newNode;
}

void StackedItUp::joinAndMinus()
{
    if (!topo || !topo->next)
        return;
    int a = pop(); // remocao dos dois elementos do topo da pilha
    int b = pop();

    Node *actualNode = topo;
    Node *anterior = nullptr;

    while (actualNode) // diminui todos os valores resto -1
    {
        actualNode->data -= 1;
        if (actualNode->data <= 0)
        {
            Node *apagar = actualNode;
            if (!anterior)
            {
                topo = actualNode->next;
                actualNode = topo;
            }
            else
            {
                anterior->next = actualNode->next;
                actualNode = actualNode->next;
            }
            delete apagar;
        }
        else // se for zero, remove
        {
            anterior = actualNode;
            actualNode = actualNode->next;
        }
    }

    Node *newNode = new Node{a + b, topo};
    topo = newNode;
}

void StackedItUp::insertComand(const string &line)
{
    instructions += line;
}
void StackedItUp::push(int v)
{
    Node *newNode = new Node{v, topo};
    topo = newNode; // empilha o valor no topo da pilha
}

int StackedItUp::pop() // remove o valor do topo da pilha
{
    if (!topo)
        return 0;
    int val = topo->data;
    Node *temporaryNode = topo;
    topo = topo->next;
    delete temporaryNode;
    return val;
}

int main()
{
    int n;
    cin >> n;
    vector<int> data(n);
    for (int i = 0; i < n; ++i)
        cin >> data[i];

    StackedItUp obj;
    string result = obj.mainLogic(data);
    ;
    cout << result << endl;

    return 0;
}
