#include<iostream>
using namespace std;

class RingQueue {
private:
    int* data;
    int capacity;
    int front;
    int rear;
    int count;

public:
    RingQueue(int capacity) {
        data = new int[capacity];
        this->capacity = capacity;
        front = 0;
        rear = capacity - 1;
        count = 0;
    }

    ~RingQueue() {
        delete[] data;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Error: Queue is full!" << endl;
            return;
        }

        rear = (rear + 1) % capacity;
        data[rear] = value;
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Error: Queue is empty!" << endl;
            return -1;
        }

        int dequeuedValue = data[front];
        front = (front + 1) % capacity;
        count--;
        return dequeuedValue;
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Error: Queue is empty!" << endl;
            return -1;
        }
        return data[front];
    }

    int getRear() {
        if (isEmpty()) {
            cout << "Error: Queue is empty!" << endl;
            return -1;
        }
        return data[rear];
    }
};

int main() {
    RingQueue queue(5);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    cout << "Front element: " << queue.getFront() << endl;

    cout << "Dequeued element: " << queue.dequeue() << endl;
    cout << "Dequeued element: " << queue.dequeue() << endl;

    cout << "Front element after dequeues: " << queue.getFront() << endl;

    queue.enqueue(40);
    queue.enqueue(50);

    cout << "Rear element: " << queue.getRear() << endl;

    return 0;
}
