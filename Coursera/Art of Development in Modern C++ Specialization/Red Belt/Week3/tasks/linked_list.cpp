template<typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node *next = nullptr;
    };

    ~LinkedList() {
        while (head != nullptr)
            PopFront();
    }

    void PushFront(const T &value) {
        if (head == nullptr) {
            head = new Node{value};
            return;
        }
        auto new_head = new Node{value, head};
        head = new_head;
    }

    void InsertAfter(Node *node, const T &value) {
        if (node == nullptr || head == nullptr) {
            PushFront(value);
            return;
        }
        auto new_node = new Node{value, node->next};
        node->next = new_node;
    }

    void RemoveAfter(Node *node) {
        if (node == nullptr) {
            PopFront();
            return;
        }
        if (node->next == nullptr)
            return;
        auto next_node = node->next;
        node->next = next_node->next;
        delete next_node;
    }

    void PopFront() {
        if (head == nullptr)
            return;
        auto front_node = head;
        head = head->next;
        delete front_node;
    }

    Node *GetHead() { return head; }

    const Node *GetHead() const { return head; }

private:
    Node *head = nullptr;
};
