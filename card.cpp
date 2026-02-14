// card.cpp
// Author: Your name
// Implementation of the classes defined in card.h
#include "card.h"
#include <string>
CARD::CARD(char ty, std::string num) : suit(ty), numb(num)
{
    card = 0;
    if (ty == 'd')
    {
        card += 13;
    }
    else if (ty == 's')
    {
        card += 26;
    }
    else if (ty == 'h')
    {
        card += 39;
    }

    if (num == "a")
    {
        card += 1;
    }
    else if (num == "j")
    {
        card += 11;
    }
    else if (num == "q")
    {
        card += 12;
    }
    else if (num == "k")
    {
        card += 13;
    }
    else if (num.length() == 2)
    {
        card += 10;
    }
    else
    {
        card += num[0] - '0';
    }
};

int CARD::getCard() const
{
    return card;
};
bool CARD::operator>(const CARD &other) const
{
    if (card > other.getCard())
    {
        return true;
    }
    return false;
};
bool CARD::operator<(const CARD &other) const
{
    if (card < other.getCard())
    {
        return true;
    }
    return false;
}
bool CARD::operator==(const CARD &other) const
{
    if (card == other.getCard())
    {
        return true;
    }
    return false;
}
std::ostream &operator<<(std::ostream &os, const CARD &c)
{
    os << c.suit << " " << c.numb;
    return os;
}