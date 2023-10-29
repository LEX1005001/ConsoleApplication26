template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& item) {
        Node* newNode = new Node;
        newNode->data = item;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = rear = newNode;
            newNode->prev = nullptr;
        }
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }

        size++;
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }
        else {
            front->prev = nullptr;
        }

        delete temp;
        size--;
    }

    T& peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }

        return front->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }
};
