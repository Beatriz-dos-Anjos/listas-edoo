#include <iostream>
#include <string>
using namespace std;
class HashTable
{
private:
    int HashFunction(string key_string);
    int maxSize;
    string *hashTableStructure; // estrutura da tabela hash

public:
    HashTable(int maxSize, string *hashTableStructure);
    ~HashTable();
    void insert(string key_string);
    void remove(string key_String);
    int find(string key_string);
};

HashTable::HashTable(int maxSize, string *hashTableStructure) // construtor que inicializa o tamanho máximo da tabela, sendo esse 101
{
    maxSize = 101;
    hashTableStructure = new string[maxSize](); // criação da estrutura da tabela hash que possui o tamanho inicializado acima
}
HashTable::~HashTable()
{
    delete[] hashTableStructure;
} // destrutor

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
    return ((h * 19) % 101);
}

void HashTable::insert(string key_string)
{
    int position = HashFunction(key_string); // calcula a posição da chave na tabela hash baseada na string recebida
    int j = 1;
    while (hashTableStructure[position] != "" && j < 20) // se a posicao ja tiver ocupada, ou seja, algum dentre o 0 a 100
    {

        position = ((HashFunction(key_string) + j * j + 23 * j) % 101); // se a posicao ja tiver ocupada, ou seja, algum dentre o 0 a 100
        j++;
    }
    if (hashTableStructure[position] == key_string)
    {
        return;
    }
    else
    {
        if (j == 20)
            return;

        hashTableStructure[position] = key_string; // insere a chave na posicao calculada
    }
}

void HashTable::remove(string key_string)
{
    int position = HashFunction(key_string); // posicao inicial da chave string na tabela int
    int j = 1;
    while (hashTableStructure[position] != "" && j < 20)
    {
        if (hashTableStructure[position] == key_string)
        {
            hashTableStructure[position] = "DELETED";
            return;
        }
        position = (position + j * j + 23 * j) % 101;
        j++;
    }
}

int HashTable::find(string key_string)
{
    int position = HashFunction(key_string);
    if (hashTableStructure[position] == key_string)
    {
        return position;
    }
    else
    {
        int j = 1;
        while ((hashTableStructure[position] != "" && hashTableStructure[position] != "DELETED") && j < 20)
        {
            if (hashTableStructure[position] == key_string)
            {
                return position;
            }
            position = (position + j * j + 23 * j) % 101;
            j++;
        }
        return -1;
    }
}