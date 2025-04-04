#include <iostream>
using namespace std;

struct Key // chave da tabela hash , tendo como caractere uma chave e um valor que soma os epsos ate o ponto atual
{
    char key;
    long long plus; 
};

struct Node // node da tela hash, usado para evitar colisoes por lista ligada
{
    Key key;
    int value;
    Node *next;
};

class HashMap  // classe que implementa a tabela hash, com o tamanho definido como 100003 ,, pois eh primo
{
private:
    static constexpr int size = 100003;
    Node *table[size];

public:
    HashMap();

    ~HashMap();

    int HashFunction(Key key1);

    int WasSeen(Key key1);

    void Insert(Key key1, int value);
};

HashMap::HashMap()
{
    for (int i = 0; i < size; i++)
    {
        table[i] = nullptr;  // inicializa a tabela hash com ponteiros nulos
    }
}

HashMap::~HashMap()
{
    {
        for (int i = 0; i < size; i++)
        {
            Node *current = table[i];
            while (current)
            {
                Node *temp = current;
                current = current->next;
                delete temp; // faz um ponteiro temporario para liberar memoria e percorrer todos os nodes alocados
            }
        }
    }
}

HashMap::HashFunction(Key key1) // funcao de espelhamento, que transforma a chave num indice
{
    long long hash_not_sized = ((key1.key - 'a') * 1000003LL + key1.plus) % size; //a chave vira un indice, usando o numero primo grande para espalhar os dados e aplicar o modulo pra ficar dentro da tabela
    if (hash_not_sized < 0)
        hash_not_sized += size;
    return hash_not_sized;
}

int HashMap::WasSeen(Key key1) // recebe ukma chave e um valor, e verifica se ja foi visto antes
{
    int position = HashFunction(key1);
    Node *currentNode = table[position];
    while (currentNode != nullptr) //percorre tudo
    {
        if (currentNode->key.key == key1.key && currentNode->key.plus == key1.plus)
            return currentNode->value;
        currentNode = currentNode->next;
    }
    return 0;
}

void HashMap::Insert(Key key1, int value) //insercao
{
    int position = HashFunction(key1); // funcao de espelhamento aplicada
    Node *currentNode = table[position];
    while (currentNode != nullptr) //percorre a lista ligada
    {
        if (currentNode->key.key == key1.key && currentNode->key.plus == key1.plus) //e a chave atual eh igual a procurada
        {
            currentNode->value += value; //soma o valor
            return;
        }
        currentNode = currentNode->next;
    }
    Node *newNode = new Node; // se nao, alocacao de um novo node
    newNode->key = key1;
    newNode->value = value;
    newNode->next = table[position];
    table[position] = newNode; // insercao na tabela
}

int main()
{
    int chars[26];
    string s;
    for (int i = 0; i < 26; i++) //leitura dos valores de cada letra do alfabeto
    {
        cin >> chars[i];
    }
    cin >> s;

    HashMap hashMap; //criacao de um objeto da tabela hash
    long long plus = 0; // ter que ser long long por conta da alocacao de memória
    long long total = 0;
    hashMap.Insert({' ', 0}, 1);

    for (char atual : s) // a cada caracter da string, verificar se ja foi visto antes. se sim, was seen. se nao, insere
    {
        total += hashMap.WasSeen({atual, plus});
        plus += chars[atual - 'a'];
        hashMap.Insert({atual, plus}, 1);
    }

    cout << total << endl;
    return 0;
}
