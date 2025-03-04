#include <iostream>
#include <string>

using namespace std;

class HashTable
{
private:
    int maxSize;                         // tamanho maximo de itens que estao a ser colocados na tabela hash
    string *hashTableStructure;          // estrutura da tabela hash
    int HashFunction(string key_string); // funcao de espelhamento

public:
    HashTable(int size);

    ~HashTable();
    // funcoes
    void insert(string key_string);

    void remove(string key_string);

    int find(string key_string);

    string getData(int index); // encapsulamento de dados para permitir o acesso ao atributo privado hashTableStructure
};

int HashTable::HashFunction(string key_string)
{
    int h = 0;
    int i = 0; // percorrendo cada caractere da string , até o fim, para calcular o valor da chave
    while (key_string[i] != '\0')
    {
        int asciiValue = key_string[i];
        int finalValue1 = (asciiValue * (i + 1));
        int finalResult = finalValue1;
        h = h + finalResult; // variavel h que guarda todos o valores ascii
        i++;
    }
    return (h * 19) % maxSize;
}

HashTable::HashTable(int size)
{
    maxSize = size;
    hashTableStructure = new string[maxSize]; // alocacao dinamica de memoria para a tabela hash
    for (int i = 0; i < maxSize; i++)
    {
        hashTableStructure[i] = ""; // inicializando a tabela hash com valores vazios
    }
}

HashTable::~HashTable()
{
    delete[] hashTableStructure; // liberando a memoria alocada
}

void HashTable::insert(string key_string)
{
    if (find(key_string) != -1)
        return; // mais abaixo ha um if que verifica se a chave ja existe, se sim, retorna -1 para nao ter risco de duplicacao

    int position = HashFunction(key_string); // calcula a posição da chave na tabela hash baseada na string recebida
    int j = 1;

    while (hashTableStructure[position] != "" && hashTableStructure[position] != "DELETED" && j < 20) // insercao de uma chave na tabela hash
    {
        position = (position + j * j + 23 * j) % maxSize; // recalcula a posicao da chave na tabela hash
        j++;
    }

    if (j < 20)
    {
        hashTableStructure[position] = key_string;
    }
}

void HashTable::remove(string key_string)
{
    int position = find(key_string);
    if (position == -1) // usa o metodo find para averiguar se a chave existe
        return;

    hashTableStructure[position] = "DELETED"; // se a chave existe, remove ela da tabela hash marcado por deleted
}

int HashTable::find(string key_string)
{
    int position = HashFunction(key_string); // nova posicao na tabela hash
    int j = 1;

    while (j < 20)
    {
        if (hashTableStructure[position] == key_string)
        {
            return position; // se a chave for a mesma que esta sendo procurada, retorna a posicao
        }
        if (hashTableStructure[position] == "")
        {
            return -1; // se nao encontrou, retorna -1
        }
        position = (position + j * j + 23 * j) % maxSize;
        j++;
    }
    return -1;
}

string HashTable::getData(int index)
{
    return hashTableStructure[index];
}
int main()
{
    int t;
    cin >> t;

    while (t > 0)
    {
        HashTable hashTable(101); // criacao de uma tabela hash com 101 posicoes

        int n;
        cin >> n;

        for (int j = 0; j < n; j++)
        {
            string operation;
            cin >> operation;
            string instructor = "";
            string key = "";
            bool foundSignal = false;
            for (char c : operation) // separacao da string recebida em duas partes, a instrucao e a chave
            {
                if (c == ':')
                {
                    foundSignal = true; // flag para indicar que o separador foi encontrado :
                }
                else if (!foundSignal) // caso contrario , adiciona a instrucao
                {
                    instructor += c;
                }
                else 
                {
                    key += c;
                }
            }

            if (instructor == "ADD")
            {
                hashTable.insert(key);
            }
            else if (instructor == "DEL")
            {
                hashTable.remove(key);
            }
        }

        int numCount = 0;
        for (int i = 0; i < 101; i++)
        {
            string value = hashTable.getData(i);
            if (value != "" && value != "DELETED")
            {
                numCount++;
            }
        }
        cout << numCount << endl;

        for (int i = 0; i < 101; i++)
        {
            string value = hashTable.getData(i);
            if (value != "" && value != "DELETED")
            {
                cout << i << ":" << value << endl;
            }
        }
        t--;
    }
    return 0;
}
