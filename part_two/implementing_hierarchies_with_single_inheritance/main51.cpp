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

    bool isEmpty() const { return head == nullptr; }
    void print() const;
};

int main()
{
    Item *item1 = new Item;
    *item1 = 100;
    Item *item2 = new Item(200);

    LinkListElement *element1 = new LinkListElement(item1);

    LinkList list1(element1);

    list1.insertAtFront(item2);
    list1.insertAtFront(new Item(50));
    cout << "List 1: ";
    list1.print();

    while (!(list1.isEmpty()))
    {
        list1.deleteAtFront();
        cout << "List 1 after removing an item: ";
        list1.print();
    }

    LinkList list2;
    list2.insertAtFront(new Item(3000));

    list2.insertAtFront(new Item(600));
    list2.insertAtFront(new Item(475));
    cout << "List 2: ";
    list2.print();

    while (!(list2.isEmpty()))
    {
        list2.deleteAtFront();
        cout << "List 2 after removing an item: ";
        list2.print();
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