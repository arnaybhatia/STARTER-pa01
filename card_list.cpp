#include "card_list.h"
#include <iostream>
using std::cout;
using std::endl;

CardList::CardList()
{
    root = nullptr;
}

CardList::~CardList()
{
    clear(root);
}

void CardList::clear(Node *n)
{
    if (!n)
    {
        return;
    }
    clear(n->left);
    clear(n->right);
    delete n;
}

bool CardList::insert(const CARD &value)
{
    if (!root)
    {
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

bool CardList::insert(const CARD &value, Node *n)
{
    if (n->info == value)
    {
        return false;
    }
    if (value < n->info)
    {
        if (n->left == nullptr)
        {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
        return insert(value, n->left);
    }
    else
    {
        if (n->right == nullptr)
        {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
        return insert(value, n->right);
    }
}

CardList::Node *CardList::getNodeFor(const CARD &value, Node *n) const
{
    if (!n)
    {
        return nullptr;
    }
    if (n->info == value)
    {
        return n;
    }
    if (value < n->info)
    {
        return getNodeFor(value, n->left);
    }
    else
    {
        return getNodeFor(value, n->right);
    }
}

bool CardList::contains(const CARD &value) const
{
    Node *n = getNodeFor(value, root);
    if (n)
    {
        return true;
    }
    return false;
}

void CardList::printInOrder() const
{
    printInOrder(root);
}

void CardList::printInOrder(Node *n) const
{
    if (!n)
    {
        return;
    }
    printInOrder(n->left);
    cout << n->info << endl;
    printInOrder(n->right);
}

CardList::Node *CardList::getPredecessorNode(const CARD &value) const
{
    Node *n = getNodeFor(value, root);
    if (!n)
    {
        return nullptr;
    }
    if (n->left)
    {
        Node *thing = n->left;
        while (thing->right)
        {
            thing = thing->right;
        }
        return thing;
    }
    else
    {
        Node *thing = n->parent;
        while (thing)
        {
            if (thing->info < n->info)
            {
                return thing;
            }
            else
            {
                thing = thing->parent;
            }
        }
    }
    return nullptr;
}

CardList::Node *CardList::getSuccessorNode(const CARD &value) const
{
    Node *n = getNodeFor(value, root);
    if (!n)
    {
        return nullptr;
    }
    if (n->right)
    {
        Node *thing = n->right;
        while (thing->left)
        {
            thing = thing->left;
        }
        return thing;
    }
    else
    {
        Node *thing = n->parent;
        while (thing)
        {
            if (thing->info > n->info)
            {
                return thing;
            }
            else
            {
                thing = thing->parent;
            }
        }
    }
    return nullptr;
}

bool CardList::remove(const CARD &value)
{
    Node *n = getNodeFor(value, root);
    if (!n)
    {
        return false;
    }
    if (n == root)
    {
        if (n->left && !n->right)
        {
            root = n->left;
            root->parent = nullptr;
            delete n;
            return true;
        }
        if (!n->left && n->right)
        {
            root = n->right;
            root->parent = nullptr;
            delete n;
            return true;
        }
        if (!n->left && !n->right)
        {
            root = nullptr;
            delete n;
            return true;
        }
    }
    if (!n->left && !n->right)
    {
        if (n->parent->left == n)
        {
            n->parent->left = nullptr;
        }
        else
        {
            n->parent->right = nullptr;
        }
        delete n;
        return true;
    }
    if (n->left && !n->right)
    {
        if (n->parent->left == n)
        {
            n->parent->left = n->left;
        }
        else
        {
            n->parent->right = n->left;
        }
        n->left->parent = n->parent;
        delete n;
        return true;
    }
    if (!n->left && n->right)
    {
        if (n->parent->left == n)
        {
            n->parent->left = n->right;
        }
        else
        {
            n->parent->right = n->right;
        }
        n->right->parent = n->parent;
        delete n;
        return true;
    }
    if (n->left && n->right)
    {
        Node *pred = getPredecessorNode(value);
        CARD predCard = pred->info;
        remove(pred->info);
        n->info = predCard;
    }
    return true;
}

const CARD &CardList::Iterator::operator*() const
{
    return current->info;
}

CardList::Iterator &CardList::Iterator::operator++()
{
    if (current->right)
    {
        current = current->right;
        while (current->left)
        {
            current = current->left;
        }
    }
    else
    {
        Node *thing = current->parent;
        while (thing && thing->right == current)
        {
            current = thing;
            thing = thing->parent;
        }
        current = thing;
    }
    return *this;
}

CardList::Iterator &CardList::Iterator::operator--()
{
    if (current->left)
    {
        current = current->left;
        while (current->right)
        {
            current = current->right;
        }
    }
    else
    {
        Node *thing = current->parent;
        while (thing && thing->left == current)
        {
            current = thing;
            thing = thing->parent;
        }
        current = thing;
    }
    return *this;
}

bool CardList::Iterator::operator==(const Iterator &other) const
{
    return current == other.current;
}

bool CardList::Iterator::operator!=(const Iterator &other) const
{
    return current != other.current;
}

CardList::Iterator CardList::begin()
{
    Node *n = root;
    if (!n)
    {
        return Iterator(nullptr);
    }
    while (n->left)
    {
        n = n->left;
    }
    return Iterator(n);
}

CardList::Iterator CardList::end()
{
    return Iterator(nullptr);
}

CardList::Iterator CardList::rbegin()
{
    Node *n = root;
    if (!n)
    {
        return Iterator(nullptr);
    }
    while (n->right)
    {
        n = n->right;
    }
    return Iterator(n);
}

CardList::Iterator CardList::rend()
{
    return Iterator(nullptr);
}

void playGame(CardList &alice, CardList &bob)
{
    bool thing = true;
    bool turn = true;
    while (thing)
    {
        thing = false;
        if (turn)
        {
            for (auto it = alice.begin(); it != alice.end(); ++it)
            {
                if (bob.contains(*it))
                {
                    cout << "Alice picked matching card " << *it << endl;
                    CARD c = *it;
                    bob.remove(c);
                    alice.remove(c);
                    thing = true;
                    break;
                }
            }
        }
        else
        {
            for (auto it = bob.rbegin(); it != bob.rend(); --it)
            {
                if (alice.contains(*it))
                {
                    cout << "Bob picked matching card " << *it << endl;
                    CARD c = *it;
                    alice.remove(c);
                    bob.remove(c);
                    thing = true;
                    break;
                }
            }
        }
        turn = !turn;
    }

    cout << endl
         << "Alice's cards:" << endl;
    alice.printInOrder();

    cout << endl
         << "Bob's cards:" << endl;
    bob.printInOrder();
}