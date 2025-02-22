#include <iostream>

using namespace std;

const int maxStudents = 1000; // baseado no numero de test cases

class Queue // implementacao na fila (circular por conta da memoria)
{
private:
    int front, rear;
    int *queue; // estrutura

public:
    Queue();
    ~Queue();
    bool isFull();
    void enqueue(int value);
    int dequeue();
};

Queue::Queue()
{
    front = 0;
    rear = 0;
    queue = new int[maxStudents]; // alocacao dinamicaa do array
}

Queue::~Queue()
{
    delete[] queue;
}

bool Queue::isFull() // metodo pra ver se a fila ta cheia, sera usado posteriormente
{
    return (rear - front) == maxStudents;
}

void Queue::enqueue(int value) // insercao de estudante na fila
{
    if (isFull())
    {
        cout << "Queue esta cheia" << endl;
    }
    else
    {
        queue[rear] = value;             // estudante eh adicionado no final da fila
        rear = (rear + 1) % maxStudents; // rear eh atualizado e eh feito o modulo para que a fila seja circular
    }
}

int Queue::dequeue() // remocao de estudante na fila
{
    if (front == rear)
    {
        cout << "Queue  ja esta vazia" << endl;
        return 0;
    }
    else
    {
        int value = queue[front];
        front = (front + 1) % maxStudents; // ao pegar o primeiro estudante da fila, o front eh atualizado
        return value;
    }
}

void processQueue(int li[], int n, int &timer, int ri[])
{
    Queue queue;      // fila para armazenar os estudantes
    int finalTime[n]; // tempo final dde atendimento

    for (int j = 0; j < n; j++) // inserir estudantes na fila normalmente
    {
        queue.enqueue(j); // adicionando o tempo de chegada na fila
    }

    for (int j = 0; j < n; j++) // processando a fila

    {
        int index = queue.dequeue(); // retirando o primeiro estudante da fila pelo index
        int studentArrival = li[index];
        int studentDeadline = ri[index];

        if (studentArrival > timer)
        {
            timer = studentArrival; 
        }

        if (timer > studentDeadline)
        {
            finalTime[index] = 0; // sai sem cha
        }
        else
        {
            finalTime[index] = timer;
            timer++;                  // atualiza o tempo
        }
    }
    for (int j = 0; j < n; j++)
    {
        cout << finalTime[j] << " "; // para output ter a mesma formatacao do problema
    }
    cout << endl;
}

int main()
{
    int t;
    cin >> t; // numero de test cases

    int timer = 1;
    int li[maxStudents]; // li = tempo de chegada , array que armazena o tempo de chegada de cada estudante
    int ri[maxStudents]; // ri = tempo limite, array que armazena o tempo limite de cada estudante
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n; // numero de estudantes

        for (int j = 0; j < n; j++)
        {

            cin >> li[j] >> ri[j]; // tempo de chegada e tempo limite, entao esse par daria o intervalo maximo de tempo de permanencia
        }
        timer = 1; // resetando o timer a cada teste

        processQueue(li, n, timer, ri); // metodo de processamento da fila
    }

    return 0;
}