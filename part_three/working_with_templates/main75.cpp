#include <iostream>
using std::cout, std::endl;

template <class Type>
class LinkList;

template <class Type>
class LinkListElement
{

private:
    Type *data = nullptr;
    LinkListElement *next = nullptr;

    Type *getData() const { return data; }
    LinkListElement *getNext() const { return next; }
    void setNext(LinkListElement *e) { next = e; }

public:
    friend class LinkList<Type>;
    LinkListElement() = default;
    LinkListElement(Type *i) : data(i), next(nullptr) {}
    ~LinkListElement()
    {
        delete data;
        next = nullptr;
    }
};

template <class Type>
class LinkList
{
private:
    LinkListElement<Type> *head = nullptr, *tail = nullptr, *current = nullptr;

public:
    LinkList() = default;
    LinkList(LinkListElement<Type> *e) { head = tail = current = e; }

    void insertAtFront(Type *);
    LinkListElement<Type> *removeAtFront();
    void deleteAtFront() { delete removeAtFront(); }
    bool isEmpty() const { return head == nullptr; }
    void print() const;
    ~LinkList()
    {
        while (!isEmpty())
            deleteAtFront();
    }
};

template <class Type>
void LinkList<Type>::insertAtFront(Type *theItem)
{
    LinkListElement<Type> *newHead;
    newHead = new LinkListElement<Type>(theItem);
    newHead->setNext(head);
    head = newHead;
}

template <class Type>
LinkListElement<Type> *LinkList<Type>::removeAtFront()
{
    LinkListElement<Type> *remove = head;
    head = head->getNext();
    current = head;
    return remove;
}

template <class Type>
void LinkList<Type>::print() const
{
    if (!head)
        cout << "<EMPTY>\n";

    LinkListElement<Type> *traverse = head;

    while (traverse)
    {
        Type output = *(traverse->getData());
        cout << output << " ";
        traverse = traverse->getNext();
    }

    cout << endl;
}

int main()
{
    LinkList<int> list1;
    list1.insertAtFront(new int(3000));
    list1.insertAtFront(new int(600));
    list1.insertAtFront(new int(475));
    cout << "List 1: ";
    list1.print();

    while (!(list1.isEmpty()))
    {
        list1.deleteAtFront();
        cout << "List 1 after removing an item: ";
        list1.print();
    }

    LinkList<float> list2;
    list2.insertAtFront(new float(30.50));
    list2.insertAtFront(new float(60.89));
    list2.insertAtFront(new float(45.93));
    cout << "List 2: ";
    list2.print();

    return 0;
}