#include <iostream>

using namespace std;

using Item = int;

class LinkList;

class LinkListElement
{
private:
    void *data = nullptr;
    LinkListElement *next = nullptr;

    void *getData() const { return data; }
    LinkListElement *getNext() const { return next; }
    void setNext(LinkListElement *e) { next = e; }

public:
    friend class LinkList;
    LinkListElement() = default;
    LinkListElement(Item *i) : data(i), next(nullptr) {}
    ~LinkListElement()
    {
        delete static_cast<Item *>(data);
        next = nullptr;
    }
};

class LinkList
{
private:
    LinkListElement *head = nullptr, *tail = nullptr, *current = nullptr;

public:
    LinkList() = default;
    LinkList(LinkListElement *e) { head = tail = current = e; }
    void insertAtFront(Item *);
    LinkListElement *removeAtFront();
    void deleteAtFront() { delete removeAtFront(); }
    bool isEmpty() const { return head == nullptr; }
    void print() const;
    ~LinkList()
    {
        while (!isEmpty())
            deleteAtFront();
    }
};

void LinkList::insertAtFront(Item *theItem)
{
    LinkListElement *newHead = new LinkListElement(theItem);
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

void LinkList::print() const
{
    if (!head)
        cout << "<EMPTY>\n";

    LinkListElement *traverse = head;
    while (traverse)
    {
        Item output = *(static_cast<Item *>(traverse->getData()));
        cout << output << " ";
        traverse = traverse->getNext();
    }
    cout << "\n";
}

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
