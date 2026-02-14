// card.h
// Author: Your name

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class CARD {
private:
    char suit;
    std::string numb;
    int card;

public:
    CARD(char ty, std::string num);

    int getCard() const;

    bool operator>(const CARD &other) const;
    bool operator<(const CARD &other) const;
    bool operator==(const CARD &other) const;

    friend std::ostream& operator<<(std::ostream& os, const CARD& c);
};

#endif