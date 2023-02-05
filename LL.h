#include <iostream>
template <typename T>
class LL 
{
    //contents of each node
    struct node 
    {
        T data;
        node* prev;
        node* next;
    };
    //iterator class to allow access of each node in main
   public:
    class Iterator 
    {
       public:
        friend class LL;
        Iterator();
        Iterator(node*);
        T operator*() const;
        Iterator operator++(int);
        Iterator operator++();
        Iterator operator--(int);
        Iterator operator--();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;

       private:
        node* current;
    };

    LL();
    LL(const LL<T>&);
    const LL<T>& operator=(const LL<T>&);
    ~LL();
    void headInsert(const T&);
    void tailInsert(const T&);
    void headRemove();
    bool isEmpty() const;
    std::size_t size() const;
    Iterator begin() const;
    Iterator end() const;

   private:
    node * portal;
};

//iterator class implementation
template <typename T>
LL<T>::Iterator::Iterator() 
{
    current = NULL;
}

template <typename T>
LL<T>::Iterator::Iterator(node* ptr) 
{
    Iterator i;
    i.current = ptr;
}

template <typename T>
T LL<T>::Iterator::operator*() const 
{
    return current->data;
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++(int) 
{
   current = current->next;
   return *this;
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++() 
{
    current = current->next;
    return *this;
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--(int) 
{
    current = current->prev;
   return *this;
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--() 
{
    current = current->prev;
    return *this;
}

template <typename T>
bool LL<T>::Iterator::operator==(const Iterator& rhs) const 
{
    return this->current == rhs.current;
}

template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator& rhs) const 
{
    return this->current != rhs.current;
}

//Linked list class implementation
template <typename T>
LL<T>::LL() 
{
    portal = new node;
    portal->prev = portal;
    portal->next = portal;
}

//copy constructor
template <typename T>
LL<T>::LL(const LL<T>& copy) 
{
    //construct portal
    portal = new node;
    portal->prev = portal;
    portal->next = portal;

    //use tailinsert, to one by one build up the LL
    node *tmp = copy.portal->next;
    for (auto i = copy.begin(); i != copy.end(); i++) {
        tailInsert(tmp->data);
        tmp = tmp->next;
   }
}

template <typename T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs) 
{
    //deallocate left hand side (this)
    for(int k = this->size(); k > 0; k--) {
        headRemove();
    }
    delete portal;

    //construct portal
    portal = new node;
    portal->prev = portal;
    portal->next = portal;

    //use tailinsert, to one by one build up the LL
    node *tmp = rhs.portal->next;
    for (auto i = rhs.begin(); i != rhs.end(); i++) {
        tailInsert(tmp->data);
        tmp = tmp->next;
    }
   return *this;
}

//destructor
template <typename T>
LL<T>::~LL()
{
    //use headRemove() to deallocate all nodes
    for(int k = this->size(); k > 0; k--) {
        headRemove();
    }
    //delete portal
    delete this->portal;
}

//head insert
template <typename T>
void LL<T>::headInsert(const T& item) 
{
    //allocate new node to tmp:
    node *tmp = new node;
    tmp->data = item;

    //if list is empty:
    if (portal->next == portal) {
        tmp->next = portal;
        tmp->prev = portal;

        portal->next = tmp;
        portal->prev = tmp;
    }

    //if list not empty:
    tmp->next = portal->next;
    tmp->prev = portal;

    portal->next->prev = tmp;
    portal->next = tmp;
}

//tail insert
template <typename T>
void LL<T>::tailInsert(const T& item) 
{
    //allocate new node to tmp ptr:
    node *tmp = new node;
    tmp->data = item;

    //if list is empty:
    if (portal->next == portal) {
        tmp->next = portal;
        tmp->prev = portal;

        portal->next = tmp;
        portal->prev = tmp;
    } 
    else {
        //if list not empty:
        portal->prev->next = tmp;
        tmp->prev = portal->prev;

        portal->prev = tmp;
        tmp->next = portal;
    }
}

template <typename T>
void LL<T>::headRemove()
{ 
    node *tmp = portal->next;

    //if empty, dont do anything
    if (portal->next == portal) {
        return;
    }
    //if only 1 node:
    else if (tmp->next == portal) {
        portal->prev = portal;
        portal->next = portal;
    }
    //general case:
    else {
        portal->next = tmp->next;
        portal->next->prev = portal;
    
    }

    delete tmp;
} 

template <typename T>
bool LL<T>::isEmpty() const
{
    //if only dummy node in LL, is empty
    if (portal->next == portal) {
        return true;
    }
    return false;
}

template <typename T>
std::size_t LL<T>::size() const
{
    node * tmp = portal->next;
    int k = 0;
    //increments counter until portal is reached
    while (tmp != portal) {
        k++;
        tmp = tmp->next;
    }
    return k;
}

template <typename T>
typename LL<T>::Iterator LL<T>::begin() const 
{
    Iterator i;
    i.current = portal->next;
    return i;
}

template <typename T>
typename LL<T>::Iterator LL<T>::end() const 
{
   Iterator i;
   i.current = portal;
   return i;
}

