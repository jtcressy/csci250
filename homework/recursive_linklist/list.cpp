template <class T>
inline List<T>::List()
{
    head = NULL;
    length = 0;
}

template <class T>
inline List<T>::List(T data)
{
    head = new Node;
    head->value = data;
    head->next = NULL;
}

template <class T>
inline Node &tail(Node *node)
{
    if (node->next != NULL)
    {
        return tail(node->next);
    }
    else
    {
        return node;
    }
}

template <class T>
inline void List<T>::add(T data)
{
    if (head == NULL)
    {
        head = new Node;
        head->value = data;
        head->next = NULL;
        length++;
    }
    else
    {
        tail = tail(head);
        Node *node = new Node;
        node->value = data;
        node->next = NULL;
        length++;
    }
}

template <class T>
inline void List<T>::del(int n) {
    if (n == 0) {
        Node *temp = head;
        head = head -> next;
        delete temp;
        length--;
    }
    
}