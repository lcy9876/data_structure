#include <iostream>
#include <initializer_list>
#include <cstdlib>

template <typename T>
class SingleLinkedList {
private:
    class Node {
    private:
        T data;
        Node *next;
    public:
        Node(T val) : data(val), next(nullptr) {}

        T getData() const { return data; }
        void setData(T val) { data = val; }
        Node* getNext() const { return next; }
        void setNext(Node* node) { next = node; }
    };

    Node* head;
    Node* currentPos;
    int size;

    void emptyListHelper(Node* &node) {
        Node* temp;
        while (node != nullptr) {
            temp = node;
            node = node->getNext();
            delete temp;
        }
    }

public:
    SingleLinkedList() : head(nullptr), currentPos(nullptr), size(0) {}
    SingleLinkedList(std::initializer_list<T> list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            insert(*it);
        }
        // 确保currentPos指向链表的最后一个元素
        if (!isEmpty()) {
            currentPos = head;
            Node* temp = head;
            while (temp->getNext() != nullptr) {
                temp = temp->getNext();
            }
            currentPos = temp;
        }
    }
    ~SingleLinkedList() {
        emptyList();
    }

    void emptyList() {
        emptyListHelper(head);
        head = nullptr;
        currentPos = nullptr;
        size = 0;
    }

    void insert(T val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = newNode;
            currentPos = head;
        } else {
            // 将新节点插入到currentPos之后
            currentPos->setNext(newNode);
            // 更新currentPos为新插入的节点
            currentPos = newNode;
        }
        size++;
    }

    void remove() {
        if (isEmpty() || currentPos == nullptr) {
            // 如果链表为空或当前位置为空，则不进行操作
            return;
        }

        Node* temp = currentPos->getNext();
        if (temp == nullptr) {
            // 如果当前位置是链表的最后一个元素
            if (head == currentPos) {
                // 如果链表只有一个元素
                delete head;
                head = nullptr;
                currentPos = nullptr;
            } else {
                // 如果当前位置不是头节点
                Node* prev = head;
                while (prev->getNext() != currentPos) {
                    prev = prev->getNext();
                }
                prev->setNext(nullptr);
            }
        } else {
            // 如果当前位置不是最后一个元素
            currentPos->setNext(temp->getNext());
            delete temp;
            if (currentPos->getNext() == nullptr) {
                // 如果当前位置变为最后一个元素
                currentPos = prev;
            }
        }
        size--;
    }

    T getCurrentVal() const {
        if (currentPos == nullptr) {
            std::cerr << "Empty current position! Can't get value!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return currentPos->getData();
    }

    void setCurrentVal(T val) {
        if (currentPos == nullptr) {
            std::cerr << "Empty current position! Can't set value!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        currentPos->setData(val);
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void printList() const {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->getData() << " ";
            temp = temp->getNext();
        }
        std::cout << std::endl;
    }

    bool find(const T &val) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->getData() == val) {
                currentPos = temp;
                return true;
            }
            temp = temp->getNext();
        }
        return false;
    }
};

int main() {
    SingleLinkedList<int> a{1, 2, 3, 4, 5};
    int a_get = a.getCurrentVal(); // 应该输出5
    std::cout << a_get << std::endl;

    SingleLinkedList<char> b{'a', 'c', 'e'};
    b.setCurrentVal('g'); // 将当前位置的值设置为 'g'
    b.printList(); // 应该输出 'a c g'

    SingleLinkedList<char> e;
    std::cout << static_cast<int>(b.isEmpty()) << " " << static_cast<int>(e.isEmpty()) << std::endl; // 应该输出 0 1

    SingleLinkedList<double> c1;
    SingleLinkedList<double> c2{1.5, 2.0, 9.0, 4.7};
    SingleLinkedList<double> c3;
    c3 = c2;
    c1.insert(3.0);
    c2.insert(8.8);
    bool f_c3 = c3.find(2.0);
    c3.insert(8.8);
    c1.printList(); // 应该输出 3.0
    c2.printList(); // 应该输出 1.5 2.0 9.0 4.7 8.8
    c3.printList(); // 应该输出 1.5 2.0 8.8 9.0 4.7

    e.remove();
    c1.remove();
    bool f = c2.find(9.0);
    c2.remove(); // 应该删除9.0之后的元素，即4.7
    e.printList(); // 不应该输出任何内容
    c1.printList(); // 不应该输出任何内容
    c2.printList(); // 应该输出 1.5 2.0 9.0 8.8

    return 0;
}