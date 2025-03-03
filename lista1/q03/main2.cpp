#include <iostream>

using namespace std;

const int maxStudents = 1000; // baseado no número de test cases

class Queue // implementação da fila (circular por conta da memória)
{
private:
    int front, rear, count;
    int *queue; // estrutura

public:
    Queue();
    ~Queue();
    bool isEmpty();
    void enqueue(int value);
    int dequeue();
};

Queue::Queue()
{
    front = 0;
    rear = 0;
    count = 0;                    //  contador de elementos
    queue = new int[maxStudents]; // alocação dinâmica do array
}

Queue::~Queue()
{
    delete[] queue;
}

bool Queue::isEmpty()
{
    return count == 0; // Fila vazia
}

void Queue::enqueue(int value) // insercao de estudante na fila
{
    if (count == maxStudents)
    {
        cout << "Queue está cheia" << endl;
    }
    else
    {
        queue[rear] = value;             // estudante eh adicionado no final da fila
        rear = (rear + 1) % maxStudents; // rear eh atualizado e eh feito o modulo para que a fila seja circular
        count++;                         // Atualiza o número de elementos na fila
    }
}

int Queue::dequeue() // remocao de estudante na fila
{
    if (isEmpty())
    {
        return 0; 
    }
    else
    {
        int value = queue[front];
        front = (front + 1) % maxStudents; // ao pegar o primeiro estudante da fila, o front eh atualizado
        count--; 
        return value;
    }
}

void processQueue(int li[], int n, int &timer, int ri[])
{
    Queue queue;      // fila para armazenar os estudantes
    int finalTime[n]; // tempo final de atendimento

    for (int j = 0; j < n; j++)
    {
        finalTime[j] = 0; // nao conseguiu chá
        queue.enqueue(j); // analisando os indices
    }

    for (int j = 0; j < n; j++)  // processando a fila
    {
        int index = queue.dequeue();// retirando o primeiro estudante da fila pelo index
        if (index == -1)
            break;  

        int studentArrival = li[index];
        int studentLeft = ri[index];

        if (studentArrival > timer)
        {
            timer = studentArrival;
        }

        if (timer > studentLeft)
        {
            finalTime[index] = 0; // sai sem bebida
        }
        else
        {
            finalTime[index] = timer;
            timer++; // atualizacao do tempo
        }
    }

    for (int j = 0; j < n; j++)
    {
        cout << finalTime[j] << " "; // para output correto
    }
    cout << endl;
}

int main()
{
    int t;
    cin >> t; // número de test cases

    int timer;
    int li[maxStudents]; // li = tempo de chegada, array que armazena o tempo de chegada de cada estudante
    int ri[maxStudents]; // ri = tempo limite, array que armazena o tempo limite de cada estudante

    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n; // numero de estudantes

        for (int j = 0; j < n; j++)
        {
            cin >> li[j] >> ri[j];
        }

        timer = 1; 

        processQueue(li, n, timer, ri);
    }

    return 0;
}
