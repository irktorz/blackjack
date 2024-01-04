#include <iostream>
#include "card.hpp"

Card::Card() {
    int value = rand() % 10 + 2;
    Card::value_ = value;
}

Card::~Card(){

}

int Card::getValue() {
    return Card::value_;
}

bool Card::isAce() {
    if (Card::value_ == 11) {
        return true;
    }
    else {
        return false;
    }
}
