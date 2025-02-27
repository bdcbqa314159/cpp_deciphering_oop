#include <iostream>

using std::cout, std::endl;

using Item = int;

class LinkListElement
{
private:
    void *data = nullptr;
    LinkListElement *next = nullptr;

public:
    LinkListElement() = default;
    LinkListElement(Item *i) : data(i), next(nullptr) {}
    ~LinkListElement()
    {
        delete static_cast<Item *>(data);
        next = nullptr;
    }

    void *getData() const { return data; }
    LinkListElement *getNext() const { return next; }
    void setNext(LinkListElement *e) { next = e; }
};

class LinkList
{
private:
    LinkListElement *head = nullptr, *tail = nullptr, *current = nullptr;

public:
    LinkList() = default;
    LinkList(LinkListElement *);
    ~LinkList();

    void insertAtFront(Item *);
    LinkListElement *removeAtFront();
    void deleteAtFront();

    void insertBeforeItem(Item *, Item *);
    LinkListElement *removeSpecificItem(Item *);
    void deleteSpecificItem(Item *);

    void insertAtEnd(Item *);
    LinkListElement *removeAtEnd();
    void deleteAtEnd();

    bool isEmpty() const { return head == nullptr; }
    void print() const;
};

class Queue : protected LinkList
{
public:
    virtual ~Queue() = default;
    void enqueue(Item *i) { insertAtEnd(i); }
    Item *dequeue();
    bool isEmpty() const { return LinkList::isEmpty(); }
    void print() const { LinkList::print(); }
};

class PriorityQueue : public Queue
{
public:
    void PriorityEnqueue(Item *i1, Item *i2) { insertBeforeItem(i1, i2); }
};

int main()
{
    Queue q1;

    q1.enqueue(new Item(50));
    q1.enqueue(new Item(67));
    q1.enqueue(new Item(80));
    q1.print();

    while (!(q1.isEmpty()))
    {
        Item *temp = q1.dequeue();
        delete temp;
        q1.print();
    }

    PriorityQueue q2;

    Item *item = new Item(167);
    q2.enqueue(new Item(67));
    q2.enqueue(item);
    q2.enqueue(new Item(180));
    q2.PriorityEnqueue(new Item(100), item); // add new item before existing one

    q2.print();

    while (!(q2.isEmpty()))
    {
        Item *temp = q2.dequeue();
        delete temp;
        q2.print();
    }

    return 0;
}

LinkList::LinkList(LinkListElement *element)
{
    head = tail = current = element;
}

void LinkList::insertAtFront(Item *item)
{
    LinkListElement *newHead = new LinkListElement(item);
    newHead->setNext(head);
    head = newHead;
}

LinkListElement *LinkList::removeAtFront()
{
    LinkListElement *remove = head;
    head = head->getNext();
    current = head;
    return remove;
}

void LinkList::deleteAtFront()
{
    LinkListElement *deallocate;
    deallocate = removeAtFront();
    delete deallocate;
}

void LinkList::insertBeforeItem(Item *newItem, Item *existing)
{
    LinkListElement *temp = nullptr, *toAdd = nullptr;

    current = head;

    if (*(static_cast<Item *>(current->getData())) == *existing)
        insertAtFront(newItem);
    else
    {
        while (*(static_cast<Item *>(current->getData())) != *existing)
        {
            temp = current;
            current = current->getNext();
        }

        toAdd = new LinkListElement(newItem);
        temp->setNext(toAdd);
        toAdd->setNext(current);
    }
}

// LinkListElement *LinkList::removeSpecificItem(Item *item)
// {
// }

// void LinkList::deleteSpecificItem(Item *item)
// {
// }

void LinkList::insertAtEnd(Item *item)
{
    if (!head)
    {
        head = new LinkListElement(item);
        tail = head;
    }

    else
    {
        tail->setNext(new LinkListElement(item));
        tail = tail->getNext();
    }
}

// LinkListElement *LinkList::removeAtEnd()
// {
// }

// void LinkList::deleteAtEnd()
// {
// }

void LinkList::print() const
{
    if (!head)
        cout << "<EMPTY>";

    LinkListElement *traverse = head;

    while (traverse)
    {
        Item output = *(static_cast<Item *>(traverse->getData()));
        cout << output << " ";
        traverse = traverse->getNext();
    }

    cout << "\n";
}

LinkList::~LinkList()
{
    while (!isEmpty())
        deleteAtFront();
}

Item *Queue::dequeue()
{
    LinkListElement *front;
    front = removeAtFront();
    Item *item = new Item(*(static_cast<Item *>(front->getData())));
    delete front;
    return item;
}