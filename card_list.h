// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include "card.h"

class CardList
{

private:
    struct Node
    {
        CARD info;
        Node *left, *right, *parent;
        Node(CARD v) : info(v), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root;

    Node *getNodeFor(const CARD &value, Node *n) const;
    void clear(Node *n);
    bool insert(const CARD &value, Node *n);
    void printInOrder(Node *n) const;
    Node *getSuccessorNode(const CARD &value) const;
    Node *getPredecessorNode(const CARD &value) const;

public:
    class Iterator
    {
        Node *current;

    public:
        Iterator(Node *n) : current(n) {}
        const CARD &operator*() const;
        Iterator &operator++();
        Iterator &operator--();
        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;
    };

    CardList();
    ~CardList();

    bool insert(const CARD &value);
    bool remove(const CARD &value);
    bool contains(const CARD &value) const;
    void printInOrder() const;

    Iterator begin();
    Iterator end();
    Iterator rbegin();
    Iterator rend();
};

void playGame(CardList &alice, CardList &bob);

#endif