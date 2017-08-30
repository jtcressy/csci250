template <class T>
class List {
public:
    List();
    List(T);
    struct Node {
        T value;
        Node* next;
    }
    void add(T);
    T get(int n); //get node at index n
    void del(int n); //delete node at index n
    int index(T); //search
    T sum();
    T operator [](int idx) const {
        return get(idx);
    }
    T& operator [](int idx) {
        return get(idx);
    }
private:
    Node *head;
    int length;
    Node& tail(Node*);
    Node& del(Node* next, int n); //helper function
}
#include "list.cpp"