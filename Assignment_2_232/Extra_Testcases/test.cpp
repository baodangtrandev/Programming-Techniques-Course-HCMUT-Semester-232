#include <iostream>

struct Node {
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class SLinkedList {
private:
    Node* head;

public:
    SLinkedList() : head(nullptr) {}

    void insert(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void mergeNode(int start, int end) {
        if (start < 0 || end < 0) {
            return;
        }

        Node* current = head;
        Node* startNode = nullptr;
        Node* endNode = nullptr;
        int index = 0;

        while (current != nullptr) {
            if (index == start) {
                startNode = current;
            }
            if (index == end) {
                endNode = current;
                break;
            }
            current = current->next;
            index++;
        }

        if (startNode == nullptr || endNode == nullptr) {
            return;
        }

        int sum = 0;
        Node* temp = startNode;
        while (temp != endNode->next) {
            sum += temp->value;
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        startNode->value = sum;
        startNode->next = endNode->next;
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node* operator[](int index) {
        if (index < 0) {
            return nullptr;
        }

        Node* current = head;
        int currentIndex = 0;

        while (current != nullptr) {
            if (currentIndex == index) {
                return current;
            }
            current = current->next;
            currentIndex++;
        }

        return nullptr;
    }
};

int main() {
    SLinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);

    std::cout << "Original list: ";
    list.display();

    list.mergeNode(1, 3);

    std::cout << "Merged list: ";
    list.display();

    Node* node = list[2];
    if (node != nullptr) {
        std::cout << "Value at index 2: " << node->value << std::endl;
    } else {
        std::cout << "Invalid index" << std::endl;
    }

    return 0;
}