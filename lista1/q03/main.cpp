#include <iostream>

using namespace std;

const int maxStudents = 1000;

class Queue
{
private:
    int front, rear;
    int *queue;

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
    queue = new int[maxStudents];
}

Queue::~Queue()
{
    delete[] queue;
}

bool Queue::isFull()
{
    return (rear - front) == maxStudents;
}

void Queue::enqueue(int value)
{
    if (isFull())
    {
        cout << "Queue esta cheia" << endl;
    }
    else
    {
        queue[rear % maxStudents] = value;
        rear++;
    }
}

int Queue::dequeue()
{
    if (front == rear)
    {
        cout << "Queue  ja esta vazia" << endl;
        return 0;
    }
    else
    {
        int value = queue[front % maxStudents];
        front++;
        return value;
    }
}

void processQueue(int li[], int n, int &timer, int ri[])
{
    int finalTime[n];
    for (int j = 0; j < n; j++)
    {
        if (li[j] > timer)
        {
            timer = li[j];
        }

        // lidando com o tempo maximo de tolerancia

        if (ri[j] >= timer)
        {
            finalTime[j] = timer;
            timer++;
        }
        else
        {
            finalTime[j] = 0;
        }
    }
    for (int j = 0; j < n; j++)
    {
        cout << finalTime[j] << " ";
    }
    cout << endl;
}

int main()
{
    int t;
    cin >> t; // numero de test cases

    int timer = 1;
    int li[maxStudents];
    int ri[maxStudents];
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n; // numero de estudantes

        for (int j = 0; j < n; j++)
        {

            cin >> li[j] >> ri[j]; // tempo de chegada e tempo limite, entao esse par daria o intervalo maximo de tempo de permanencia
        }
        int timer = 1;
        processQueue(li, n, timer, ri);
    }

    return 0;
}