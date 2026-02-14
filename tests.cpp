#include <iostream>
#include "card.h"
#include "card_list.h"
using namespace std;

int main()
{
    cout << "Testing insert..." << endl;

    CardList lst1;
    if (lst1.insert(CARD('c', "a")))
        cout << "PASS: insert empty" << endl;
    else
        cout << "FAIL" << endl;

    if (!lst1.insert(CARD('c', "a")))
        cout << "PASS: insert duplicate" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst2;
    lst2.insert(CARD('d', "5"));
    if (lst2.insert(CARD('c', "a")))
        cout << "PASS: insert left" << endl;
    else
        cout << "FAIL" << endl;

    if (lst2.insert(CARD('h', "10")))
        cout << "PASS: insert right" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst3;
    lst3.insert(CARD('d', "5"));
    lst3.insert(CARD('c', "3"));
    if (lst3.insert(CARD('s', "k")))
        cout << "PASS: insert deep" << endl;
    else
        cout << "FAIL" << endl;

    cout << "Testing contains..." << endl;

    CardList lst4;
    if (!lst4.contains(CARD('c', "a")))
        cout << "PASS: contains empty" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst5;
    lst5.insert(CARD('d', "5"));
    if (lst5.contains(CARD('d', "5")))
        cout << "PASS: contains single yes" << endl;
    else
        cout << "FAIL" << endl;

    if (!lst5.contains(CARD('h', "10")))
        cout << "PASS: contains single no" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst6;
    lst6.insert(CARD('d', "5"));
    lst6.insert(CARD('c', "a"));
    if (lst6.contains(CARD('c', "a")))
        cout << "PASS: contains multiple yes" << endl;
    else
        cout << "FAIL" << endl;

    if (!lst6.contains(CARD('s', "k")))
        cout << "PASS: contains multiple no" << endl;
    else
        cout << "FAIL" << endl;

    cout << "Testing remove..." << endl;

    CardList lst7;
    if (!lst7.remove(CARD('c', "a")))
        cout << "PASS: remove empty" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst8;
    lst8.insert(CARD('d', "5"));
    lst8.insert(CARD('c', "a"));
    if (lst8.remove(CARD('c', "a")) && !lst8.contains(CARD('c', "a")))
        cout << "PASS: remove leaf" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst9;
    lst9.insert(CARD('d', "5"));
    lst9.insert(CARD('c', "a"));
    lst9.insert(CARD('c', "k"));
    if (lst9.remove(CARD('c', "k")))
        cout << "PASS: remove left child" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst10;
    lst10.insert(CARD('c', "a"));
    lst10.insert(CARD('d', "5"));
    if (lst10.remove(CARD('c', "a")))
        cout << "PASS: remove right child" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst11;
    lst11.insert(CARD('d', "5"));
    lst11.insert(CARD('c', "a"));
    lst11.insert(CARD('h', "10"));
    if (lst11.remove(CARD('d', "5")) && !lst11.contains(CARD('d', "5")))
        cout << "PASS: remove two children" << endl;
    else
        cout << "FAIL" << endl;

    cout << "Testing Iterator..." << endl;

    CardList lst12;
    if (lst12.begin() == lst12.end())
        cout << "PASS: iterator empty" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst13;
    lst13.insert(CARD('d', "5"));
    auto it1 = lst13.begin();
    if (*it1 == CARD('d', "5"))
    {
        ++it1;
        if (it1 == lst13.end())
            cout << "PASS: iterator single forward" << endl;
        else
            cout << "FAIL" << endl;
    }
    else
        cout << "FAIL" << endl;

    auto it2 = lst13.rbegin();
    if (*it2 == CARD('d', "5"))
    {
        --it2;
        if (it2 == lst13.rend())
            cout << "PASS: iterator single reverse" << endl;
        else
            cout << "FAIL" << endl;
    }
    else
        cout << "FAIL" << endl;

    CardList lst14;
    lst14.insert(CARD('d', "5"));
    lst14.insert(CARD('c', "a"));
    lst14.insert(CARD('h', "10"));
    auto it3 = lst14.begin();
    bool thing = (*it3 == CARD('c', "a"));
    ++it3;
    thing = thing && (*it3 == CARD('d', "5"));
    ++it3;
    thing = thing && (*it3 == CARD('h', "10"));
    ++it3;
    thing = thing && (it3 == lst14.end());
    if (thing)
        cout << "PASS: iterator forward seq" << endl;
    else
        cout << "FAIL" << endl;

    auto it4 = lst14.rbegin();
    thing = (*it4 == CARD('h', "10"));
    --it4;
    thing = thing && (*it4 == CARD('d', "5"));
    --it4;
    thing = thing && (*it4 == CARD('c', "a"));
    --it4;
    thing = thing && (it4 == lst14.rend());
    if (thing)
        cout << "PASS: iterator reverse seq" << endl;
    else
        cout << "FAIL" << endl;

    cout << "Testing playGame..." << endl;

    CardList lst15, lst16;
    lst15.insert(CARD('c', "3"));
    lst15.insert(CARD('d', "5"));
    lst16.insert(CARD('c', "3"));
    lst16.insert(CARD('h', "10"));
    playGame(lst15, lst16);
    if (!lst15.contains(CARD('c', "3")) && !lst16.contains(CARD('c', "3")))
        cout << "PASS: playGame common" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst17, lst18;
    lst17.insert(CARD('c', "3"));
    lst18.insert(CARD('h', "10"));
    playGame(lst17, lst18);
    if (lst17.contains(CARD('c', "3")) && lst18.contains(CARD('h', "10")))
        cout << "PASS: playGame no common" << endl;
    else
        cout << "FAIL" << endl;

    CardList lst19, lst20;
    lst20.insert(CARD('h', "10"));
    playGame(lst19, lst20);
    if (lst20.contains(CARD('h', "10")))
        cout << "PASS: playGame one empty" << endl;
    else
        cout << "FAIL" << endl;

    cout << "Done." << endl;
    return 0;
}