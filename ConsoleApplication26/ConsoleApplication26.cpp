#include <iostream>
//односвязанный список
template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;  // указатель на голову списка
    Node* tail;  // указатель на конец списка
    int size;    // размер списка

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        // Деструктор, освобождающий память, выделенную для каждого узла списка
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void addToHead(const T& value) {
        // Добавление нового элемента в начало списка
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;

        if (tail == nullptr) {
            tail = head;
        }

        size++;
    }

    void addToTail(const T& value) {
        // Добавление нового элемента в конец списка
        Node* newNode = new Node(value);

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    void insertAtIndex(const T& value, int index) {
        // Вставка нового элемента по заданному индексу
        if (index < 0 || index > size) {
            std::cout << "Invalid index" << std::endl;
            return;
        }

        if (index == 0) {
            addToHead(value);
        }
        else if (index == size) {
            addToTail(value);
        }
        else {
            Node* newNode = new Node(value);
            Node* current = head;

            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;

            size++;
        }
    }

    void removeFromHead() {
        // Удаление элемента из начала списка
        if (isEmpty()) {
            std::cout << "List is empty" << std::endl;
            return;
        }

        Node* nodeToRemove = head;
        head = head->next;
        delete nodeToRemove;

        if (head == nullptr) {
            tail = nullptr;
        }

        size--;
    }

    void removeFromTail() {
        // Удаление элемента из конца списка
        if (isEmpty()) {
            std::cout << "List is empty" << std::endl;
            return;
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* current = head;

            while (current->next != tail) {
                current = current->next;
            }

            delete tail;
            tail = current;
            tail->next = nullptr;
        }

        size--;
    }

    void removeAtIndex(int index) {
        // Удаление элемента по заданному индексу
        if (isEmpty() || index < 0 || index >= size) {
            std::cout << "Invalid index" << std::endl;
            return;
        }

        if (index == 0) {
            removeFromHead();
        }
        else if (index == size - 1) {
            removeFromTail();
        }
        else {
            Node* current = head;

            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            Node* nodeToRemove = current->next;
            current->next = nodeToRemove->next;
            delete nodeToRemove;

            size--;
        }
    }

    bool isEmpty() const {
        // Проверка, является ли список пустым
        return size == 0;
    }

    friend LinkedList<T> operator+(const LinkedList<T>& list1, const LinkedList<T>& list2) {
        // Перегрузка оператора + для объединения двух списков
        LinkedList<T> result;

        Node* current = list1.head;
        while (current != nullptr) {
            result.addToTail(current->data);
            current = current->next;
        }

        current = list2.head;
        while (current != nullptr) {
            result.addToTail(current->data);
            current = current->next;
        }

        return result;
    }
    friend LinkedList<T> operator-(const LinkedList<T>& list1, const LinkedList<T>& list2) {
        // Перегрузка оператора - для вычитания элементов второго списка из первого списка
        LinkedList<T> result;

        Node* current = list1.head;
        while (current != nullptr) {
            if (!list2.contains(current->data)) {
                result.addToTail(current->data);
            }
            current = current->next;
        }

        return result;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        // Перегрузка оператора присваивания для копирования содержимого другого списка
        if (this == &other) {
            return *this;
        }

        clear();

        Node* current = other.head;
        while (current != nullptr) {
            addToTail(current->data);
            current = current->next;
        }

        return *this;
    }

    bool contains(const T& value) const {
        // Проверка, содержится ли заданное значение в списке
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() {
        // Очистка списка
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }
};
