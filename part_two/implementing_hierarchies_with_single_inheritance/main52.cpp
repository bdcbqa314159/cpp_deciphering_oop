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

class Stack : private LinkList
{
public:
    Stack() = default;
    ~Stack() = default;
    void push(Item *item)
    {
        insertAtFront(item);
    }

    Item *pop();
    bool isEmpty() { return LinkList::isEmpty(); }
    void print() const { LinkList::print(); }
};

int main()
{
    Stack stack1; // create a Stack
    // Add some items to the stack, using public interface
    stack1.push(new Item(3000));
    stack1.push(new Item(600));
    stack1.push(new Item(475));
    cout << "Stack 1: ";
    stack1.print();

    while (!(stack1.isEmpty()))
    {
        Item *deallocate = stack1.pop();
        delete deallocate;
        cout << "Stack 1 after popping an item: ";
        stack1.print();
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

Item *Stack::pop()
{
    LinkListElement *top;
    top = removeAtFront();

    Item *item = new Item(*(static_cast<Item *>(top->getData())));
    delete top;
    return item;
}