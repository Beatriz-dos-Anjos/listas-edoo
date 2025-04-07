#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct ComandoInfo // estrutura que vai guardar os comandos e qtd de pasos
{
    string comando;
    int steps;
};

class Stacked
{
public:
    vector<int> itens; // a pilha possui um vetor dos numeros
    string commands;   // string que vai guardar os comandos
    int finalSum;      // soma total dos passos feitos

    Stacked();
    void push(int valor);
    ComandoInfo minusAndDivide(int numero); // o numero eh transformando em comandos
    string finalString();
};

Stacked::Stacked()
{
    finalSum = 0;  // inicialmente, sao 0 passos acumulados
    commands = ""; // e nao ha comandos
}

void Stacked::push(int valor) // push adicionando o valor no final do vetor
{
    itens.push_back(valor);
}

ComandoInfo Stacked::minusAndDivide(int numero) // transforma o número em comandos
{
    string binario = "";          // string para guardar o número convertido para binário
    string comandosGerados = "1"; // o primeiro comando sempre e  1
    int totalPassos = 0;

    for (; numero > 0; numero = numero / 2) //conversap do número para binário
    {
        char digito = (numero % 2 == 0) ? '0' : '1';
        binario = digito + binario; //montar o binario
    }

    for (size_t pos = 1; pos < binario.length(); pos++)
    {
        comandosGerados += "d+"; //caso haja duplicacao
        totalPassos++;

        if (binario[pos] == '1')
        {
            comandosGerados += "1+"; // se nao tiver duplicacao, adiciona 1
            totalPassos++;
        }
    }

    return ComandoInfo{comandosGerados, totalPassos}; //retorna numa especie de tupla
}

string Stacked::finalString()
{
    string resultado; //  comando final ainda naao setado
    int indice = itens.size();
    while (indice > 0) // enquanto tiver elementos na pilha
    {
        indice--;                                      // parte de diminuir
        int valorAtual = itens[indice] + finalSum;     // soma todos os passos
        ComandoInfo info = minusAndDivide(valorAtual); // chama a funcao de conversao
        resultado.insert(0, info.comando);             // insercao do resultado no inicio da string
        finalSum += info.steps;                        // soma os passos
    }

    return resultado;
}

int main()
{
    int numEntry;
    cin >> numEntry;
    vector<int> dados(numEntry);

    for (int i = 0; i < numEntry; ++i)
    {
        cin >> dados[i];
    }

    Stacked pilha;

    for (int i = 0; i < numEntry; ++i) // empilhamento de objeto
    {
        pilha.push(dados[i]);
    }

    string firstComand = pilha.finalString(); // comandos
    cout << firstComand << endl;

    return 0;
}
