#include <iostream>
#include "dealer.hpp"

Dealer::Dealer() {
    int aces = 0;
    Card card_one = Card();
    Dealer::hand_.push_back(card_one.getValue());
    if (card_one.getValue() == 11) {
        aces++;
    }

    Card card_two = Card();
    Dealer::hand_.push_back(card_two.getValue());
    if (card_two.getValue() == 11) {
        aces++;
    }

    Dealer::getTotal();

    Dealer::aces_ = aces;
}

Dealer::~Dealer() {}

void Dealer::show() {
    std::cout << "Dealer's hand: ";
    for (int i = 0; i < Dealer::hand_.size(); i++) {
        std::cout << hand_.at(i) << ' ';
    }
    std::cout << std::endl << std::endl;
}

void Dealer::show_2() {
    std::cout << "Dealer's hand: X " << Dealer::hand_.at(1) << std::endl;
}

int Dealer::getTotal() {
    int total = 0;
    for (int i = 0; i < hand_.size(); i++) {
        total = total + hand_.at(i);
    }

    while (total > 21) {
        if (Dealer::aces_ > 0) {
            total = total - 10;
            Dealer::aces_--;

            for (int i = 0; i < Dealer::hand_.size(); i++) {
                if (Dealer::hand_[i] == 11) {
                    Dealer::hand_[i] = 1;
                    break;
                }
            }
        }

        else {
            break;
        }
    }

    Dealer::total_ = total;
    return Dealer::total_;
}

void Dealer::check17() {

    while (Dealer::total_ < 17) {
        Card next_card = Card();
        Dealer::hand_.push_back(next_card.getValue());
        if (next_card.isAce()) {
            Dealer::aces_++;
        }
        Dealer::getTotal();
        Dealer::show();
    }
}

int Dealer::addScore() {
    Dealer::score_++;
    return Dealer::score_;
}

int Dealer::getScore() {
    return Dealer::score_;
}